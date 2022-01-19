#include "CollisionVolumeOctree.h"
#include "Visualizer.h"
#include "OctreeModelManager.h"
#include "OctreeNode.h"
#include "MathTools.h"
#include <cassert>

CollisionVolumeOctree::CollisionVolumeOctree(Model* pModel, int maxDepth)
	: _pRoot(nullptr), _maxDepth(maxDepth)
{
	assert(pModel != nullptr && maxDepth >= 1);
	_pRoot = OctreeModelManager::GetOctreeModel(pModel, maxDepth);
}

CollisionVolumeOctree::~CollisionVolumeOctree()
{
	delete _pRoot;
}

// Get Nodes
CollisionVolumeOctree::OctreeNodeCollection CollisionVolumeOctree::getAllNodes() const
{
	OctreeNodeCollection allNodes; allNodes.reserve(_pRoot->getSize() + 1);
	addNodes(_pRoot, allNodes);
	return allNodes;
}

void CollisionVolumeOctree::addNodes(OctreeNode* pNode, OctreeNodeCollection& nodes) const
{
	if (pNode == nullptr) return;

	nodes.push_back(pNode);
	for (int i = 0; i < OctreeNode::NUMBER_OF_CHILDREN; i++)
	{
		addNodes(pNode->getChildAt(i), nodes);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Compute data
//-----------------------------------------------------------------------------------------------------------------------------
void CollisionVolumeOctree::computeData(Model*, const Matrix& worldMatrix)
{
	OctreeNodeCollection nodesToUpdate; nodesToUpdate.reserve(getRoot()->getSize() + 1);
	nodesToUpdate.push_back(_pRoot);

	while (!nodesToUpdate.empty())
	{
		OctreeNode* pNode = nodesToUpdate.back(); 
		nodesToUpdate.pop_back();

		pNode->getOBB().setWorldMatrix(worldMatrix);

		for (int i = 0; i < OctreeNode::NUMBER_OF_CHILDREN; i++)
		{
			OctreeNode* pChild = pNode->getChildAt(i);
			if (pChild != nullptr && pChild->getIsValid())
			{
				nodesToUpdate.push_back(pChild);
			}
		}
	}

}

//-----------------------------------------------------------------------------------------------------------------------------
// Intersect
//-----------------------------------------------------------------------------------------------------------------------------
bool CollisionVolumeOctree::intersectAccept(const CollisionVolume& collisionVolume) const
{
	return collisionVolume.intersectVisitor(*this);
}

bool CollisionVolumeOctree::intersectVisitor(const CollisionVolumeBSphere& BSphere) const
{
	return MathTools::Intersect(BSphere, *this);
}

bool CollisionVolumeOctree::intersectVisitor(const CollisionVolumeAABB& AABB) const
{
	return MathTools::Intersect(AABB, *this);
}

bool CollisionVolumeOctree::intersectVisitor(const CollisionVolumeOBB& OBB) const
{
	return MathTools::Intersect(OBB, *this);
}

bool CollisionVolumeOctree::intersectVisitor(const CollisionVolumeOctree& Octree) const
{
	return MathTools::Intersect(*this, Octree);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Draw
//-----------------------------------------------------------------------------------------------------------------------------
void CollisionVolumeOctree::debugDraw(const Vect& color, int depth) const
{
	drawAt(depth, color, _pRoot);
}

void CollisionVolumeOctree::debugDraw(int depth, const Vect& color) const
{
	drawAt(depth, color, _pRoot);
}

void CollisionVolumeOctree::drawAt(int depth, const Vect& color, const OctreeNode* pNode) const
{
	if (pNode == nullptr) return;

	if (depth == 0)
	{
		if (pNode->getIsValid())
		{
			Visualizer::ShowCollisionVolume(pNode->getOBB(), color);
		}
	}
	else
	{
		for (int i = 0; i < OctreeNode::NUMBER_OF_CHILDREN; i++)
		{
			drawAt(depth - 1, color, pNode->getChildAt(i));
		}
	}
}

const OctreeNode* CollisionVolumeOctree::getRoot() const
{
	return _pRoot;
}

int CollisionVolumeOctree::getMaxDepth() const
{
	return _maxDepth - 1;
}
