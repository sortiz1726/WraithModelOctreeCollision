#include "OctreeBuilder.h"
#include "OctreeNode.h"

#include "Matrix.h"
#include "Vect.h"

#include "Triangle.h"
#include "GpuVertTypes.h"

#include "MathTools.h"

#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"

#include <cassert>

OctreeNode* OctreeBuilder::buildOctree(Model* pModel, int depth)
{
	Trace::out("\nOctreeBuilder (buildOctree)\n");
	Trace::out("\tOctree depth: %d\n", depth);
	assert(pModel != nullptr && depth >= 1);
	Trace::out("\tStart Octree Build\n");
	_leafNodeHolder.clear();
	_leafNodeHolder.reserve(maxNumberOfLeafNodes(depth));

	OctreeNode* pRootNode = nullptr;
	buildNode(pRootNode, pModel->getMinAABB(), pModel->getMaxAABB(), depth);
	assert(pRootNode != nullptr);

	filterNodes(pModel);
	pRootNode->recalculateSize();

	Trace::out("\tFinished Octree Build\n");
	return pRootNode;
}

int OctreeBuilder::maxNumberOfLeafNodes(const int depth) const
{
	// Formula for the max number of nodes is f(depth) = 2 ^ (3 * (depth - 1)).
	// Using bitwise left shifts on the number 1 has the same effect. 
	// number of shifts is equal to 3 * (depth - 1)
	return 1 << (3 * (depth - 1));
}

// Step 1: Build nodes
void OctreeBuilder::buildNode(OctreeNode*& pNode, const Vect& minVertex, const Vect& maxVertex, int depth)
{
	if (depth == 0) return;

	pNode = new OctreeNode();

	CollisionVolumeOBB& obb = pNode->getOBB();
	obb.computeData(minVertex, maxVertex, Matrix(IDENTITY));

	for (int i = 0; i < OctreeNode::NUMBER_OF_CHILDREN; ++i)
	{
		OctreeNode*& pChild = pNode->getChildReferenceAt(i);
		Matrix transform = transformOffset(minVertex, maxVertex, i);
		buildNode(pChild, minVertex * transform, maxVertex * transform, depth - 1);
		if (pChild != nullptr)
		{
			pChild->setParent(pNode);
		}
	}

	if (pNode->isLeafNode())
	{
		_leafNodeHolder.push_back(pNode);
	}
}

// -+ Build nodes helper
Matrix OctreeBuilder::transformOffset(const Vect& minVertex, const Vect& maxVertex, int index) const
{
	Vect halfScale = Vect(1.0f, 1.0f, 1.0f) * 0.5f;
	Vect center = (minVertex + maxVertex) * 0.5f;
	Vect offsetToOctant = MathTools::MultiplyComponents((maxVertex - minVertex), computeOffset(index));

	Matrix transform = Matrix(TRANS, -center) * Matrix(SCALE, halfScale) * Matrix(TRANS, center) * Matrix(TRANS, offsetToOctant);

	return transform;
}

Vect OctreeBuilder::computeOffset(const int index) const
{
	Vect offset(0.0f, 0.0f, 0.0f);

	switch (index)
	{
	case 0:
		offset = Vect(0.25f, 0.25f, 0.25f);
		break;
	case 1:
		offset = Vect(-0.25f, 0.25f, 0.25f);
		break;
	case 2:
		offset = Vect(0.25f, -0.25f, 0.25f);
		break;
	case 3:
		offset = Vect(0.25f, 0.25f, -0.25f);
		break;
	case 4:
		offset = Vect(-0.25f, -0.25f, 0.25f);
		break;
	case 5:
		offset = Vect(-0.25f, 0.25f, -0.25f);
		break;
	case 6:
		offset = Vect(0.25f, -0.25f, -0.25f);
		break;
	case 7:
		offset = Vect(-0.25f, -0.25f, -0.25f);
		break;
	default:
		Trace::out("Octree Builder ERROR (computeOffset): Case %d is not valid\n", index);
		assert(false);
		break;
	}

	return offset;
}

// Step 2: Filter nodes
void OctreeBuilder::filterNodes(Model* pModel)
{
	TriangleCollection triangles = getModelTriangles(pModel);

	// Using tier testing with BSpheres and AABB (in the order of fastest collision testing)
	// first before finally testing triangle face with OBB collision volume (which is the slowest)
	CollisionVolumeBSphere proxyOBB_BSphere;
	CollisionVolumeBSphere proxyTriangle_BSphere;

	CollisionVolumeAABB proxyOBB_AABB;
	CollisionVolumeAABB proxyTriangle_AABB;

	for (OctreeNode* pLeafNode : _leafNodeHolder)
	{
		// Convert OBB volume into a close approximation of a BSphere and AABB volume
		proxyOBB_BSphere.computeData(pLeafNode->getOBB());
		proxyOBB_AABB.computeData(pLeafNode->getOBB());
		for (const Triangle& triangle : triangles)
		{
			// Convert Triangle volume into a close approximation of a BSphere volume
			proxyTriangle_BSphere.computeData(triangle);
			if (MathTools::Intersect(proxyOBB_BSphere, proxyTriangle_BSphere))
			{
				// Convert Triangle volume into a close approximation of a AABB volume
				proxyTriangle_AABB.computeData(triangle);
				if (MathTools::Intersect(proxyOBB_AABB, proxyTriangle_AABB))
				{
					// Testing Triangle and OBB collision
					if (MathTools::Intersect(pLeafNode->getOBB(), triangle))
					{
						validateNode(pLeafNode);
						break;
					}
				}
			}
		}
	}
}

// Filter nodes helpers
OctreeBuilder::TriangleCollection OctreeBuilder::getModelTriangles(Model* pModel) const
{
	const int numberOfTriangles = pModel->getTriNum();
	TriangleIndex* pTriangleIndices = pModel->getTriangleList();
	TriangleCollection triangles; triangles.reserve(numberOfTriangles);

	for (int i = 0; i < numberOfTriangles; i++)
	{
		const TriangleIndex& triangleIndex = pTriangleIndices[i];
		triangles.push_back(createTriangle(triangleIndex, pModel->getVectList()));
	}

	return triangles;
}

Triangle OctreeBuilder::createTriangle(const TriangleIndex& triangleIndex, const Vect* const vects) const
{
	return Triangle(vects[triangleIndex.v0], vects[triangleIndex.v1], vects[triangleIndex.v2]);
}

void OctreeBuilder::validateNode(OctreeNode* pNode)
{
	pNode->setIsValid(true);
	OctreeNode* pParent = pNode->getParent();
	if (pParent != nullptr && !pParent->getIsValid())
	{
		validateNode(pParent);
	}
}