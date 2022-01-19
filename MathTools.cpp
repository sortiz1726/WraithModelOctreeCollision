#include "MathTools.h"
#include "CollisionVolume.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "CollisionVolumeOctree.h"

#include "OctreeNode.h"
#include "OctreeTools.h"

#include "Triangle.h"
#include "Colors.h"
#include "Visualizer.h"
#include <stack>
#include <list>
#include <array>
#include <set>

#ifndef MathTools_DEBUG
#define	MathTools_DEBUG 0
#endif // !MathTools_DEBUG

#ifndef MathTools_Octree_DEBUG
#define	MathTools_Octree_DEBUG 1
#endif // !MathTools_Octree_DEBUG

void drawTriangleTMP(const Triangle& triangle)
{
	Vect lineColor = Colors::AliceBlue;
	Vect pointColor = Colors::Red;

	Visualizer::ShowPointAt(triangle.getVertex0(), pointColor);
	Visualizer::ShowPointAt(triangle.getVertex1(), pointColor);
	Visualizer::ShowPointAt(triangle.getVertex2(), pointColor);

	Visualizer::ShowLineSegment(triangle.getVertex0(), triangle.getVertex1(), lineColor);
	Visualizer::ShowLineSegment(triangle.getVertex1(), triangle.getVertex2(), lineColor);
	Visualizer::ShowLineSegment(triangle.getVertex2(), triangle.getVertex0(), lineColor);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Intersection Testing
//-----------------------------------------------------------------------------------------------------------------------------
bool MathTools::Intersect(const CollisionVolume& collisionVolume_1, const CollisionVolume& collisionVolume_2)
{
	return collisionVolume_1.intersectAccept(collisionVolume_2);
}

// BSpheres
bool MathTools::Intersect(const CollisionVolumeBSphere& BSphere_A, const CollisionVolumeBSphere& BSphere_B)
{
	float centerDistanceSquared = (BSphere_A.getCenter() - BSphere_B.getCenter()).magSqr();

	float radiusSum = BSphere_A.getRadius() + BSphere_B.getRadius();
	float radiusSumSquared = radiusSum * radiusSum;

	return centerDistanceSquared < radiusSumSquared;
}

bool MathTools::Intersect(const CollisionVolumeBSphere& BSphere, const CollisionVolumeAABB& AABB)
{
	const Vect& BSphereCenter = BSphere.getCenter();
	Vect clampedCenter = MathTools::Clamp(BSphereCenter, AABB.getMinWorldVertex(), AABB.getMaxWorldVertex());

#if MathTools_DEBUG
	Visualizer::ShowPointAt(clampedCenter, Colors::Green);
#endif // MathTools_DEBUG

	float distanceSquare = (clampedCenter - BSphereCenter).magSqr();
	float radiusSqaured = BSphere.getRadius() * BSphere.getRadius();

	return distanceSquare < radiusSqaured;
}

bool MathTools::Intersect(const CollisionVolumeBSphere& BSphere, const CollisionVolumeOBB& OBB)
{
	const Vect& BSphereCenter = BSphere.getCenter();
	Vect clampedCenter = MathTools::Clamp(BSphereCenter * OBB.getInverseWorldMatrix(),
		OBB.getMinLocalVertex(), OBB.getMaxLocalVertex());

	clampedCenter *= OBB.getWorldMatrix();

#if MathTools_DEBUG
	Visualizer::ShowPointAt(clampedCenter, Colors::Green);
#endif // MathTools_DEBUG

	float distanceSquare = (clampedCenter - BSphereCenter).magSqr();
	float radiusSqaured = BSphere.getRadius() * BSphere.getRadius();

	return distanceSquare < radiusSqaured;
}

bool MathTools::Intersect(const CollisionVolumeBSphere& BSphere, const CollisionVolumeOctree& Octree)
{
	return MathTools::Intersect(static_cast<const CollisionVolume&>(BSphere), Octree);
}

// AABBs
bool MathTools::Intersect(const CollisionVolumeAABB& AABB_1, const CollisionVolumeAABB& AABB_2)
{
	Interval axis_1 = { AABB_1.getMinWorldVertex()[x], AABB_1.getMaxWorldVertex()[x] };
	Interval axis_2 = { AABB_2.getMinWorldVertex()[x], AABB_2.getMaxWorldVertex()[x] };
	bool doesXAxisOverlap = MathTools::DoIntervalsOverlap(axis_1, axis_2);

	axis_1 = { AABB_1.getMinWorldVertex()[y], AABB_1.getMaxWorldVertex()[y] };
	axis_2 = { AABB_2.getMinWorldVertex()[y], AABB_2.getMaxWorldVertex()[y] };
	bool doesYAxisOverlap = MathTools::DoIntervalsOverlap(axis_1, axis_2);

	axis_1 = { AABB_1.getMinWorldVertex()[z], AABB_1.getMaxWorldVertex()[z] };
	axis_2 = { AABB_2.getMinWorldVertex()[z], AABB_2.getMaxWorldVertex()[z] };
	bool doesZAxisOverlap = MathTools::DoIntervalsOverlap(axis_1, axis_2);

	return doesXAxisOverlap && doesYAxisOverlap && doesZAxisOverlap;
}

bool MathTools::Intersect(const CollisionVolumeAABB& AABB, const CollisionVolumeOBB& OBB)
{
	const int numberOfAxes = 15;
	Vect axes[numberOfAxes];
	MathTools::OutputAxesToTest(AABB, OBB, axes);

	bool doesIntersects = true;

	for (int i = 0; i < numberOfAxes && doesIntersects; i++)
	{
		const Vect& axis = axes[i];
		if (axis.magSqr() > FLT_EPSILON)
		{
			doesIntersects = MathTools::DoesOverlapsOnAxis(AABB, OBB, axis);
		}
	}

	return doesIntersects;
}

bool MathTools::Intersect(const CollisionVolumeAABB& AABB, const CollisionVolumeOctree& Octree)
{
	return MathTools::Intersect(static_cast<const CollisionVolume&>(AABB), Octree);
}

// OBBs
bool MathTools::Intersect(const CollisionVolumeOBB& OBB_1, const CollisionVolumeOBB& OBB_2)
{
	const int numberOfAxes = 15;
	Vect axes[numberOfAxes];
	MathTools::OutputAxesToTest(OBB_1, OBB_2, axes);

	bool doesIntersects = true;

	for (int i = 0; i < numberOfAxes && doesIntersects; i++)
	{
		const Vect& axis = axes[i];
		if (axis.magSqr() > FLT_EPSILON)
		{
			doesIntersects = MathTools::DoesOverlapsOnAxis(OBB_1, OBB_2, axis);
		}
	}

	return doesIntersects;
}

bool MathTools::Intersect(const CollisionVolumeOBB& OBB, const CollisionVolumeOctree& Octree)
{
	return MathTools::Intersect(static_cast<const CollisionVolume&>(OBB), Octree);
}

// Octrees
bool MathTools::Intersect(const CollisionVolumeOctree& Octree_1, const CollisionVolumeOctree& Octree_2)
{
#if MathTools_Octree_DEBUG
	std::set<const OctreeNode*> nodesThatCollide;
#endif // MathTools_Octree_DEBUG

	OctreeTools::NodePairStack nodePairsToTest;

	// Add first node pair (Root node of Octree 1 and of Octree 2) to test
	nodePairsToTest.push(std::make_pair(Octree_1.getRoot(), Octree_2.getRoot()));

	while (!nodePairsToTest.empty())
	{
		// Get get node pair to test and...
		const OctreeTools::NodePair& nodePair = nodePairsToTest.top();
		nodePairsToTest.pop();

		// Get node 1 and node 2
		const OctreeNode* pNode_1 = nodePair.first;
		const OctreeNode* pNode_2 = nodePair.second;

		// If both nodes's OBB intersect then...
		if (MathTools::Intersect(pNode_1->getOBB(), pNode_2->getOBB()))
		{
#if MathTools_Octree_DEBUG
			nodesThatCollide.insert(pNode_1);
			nodesThatCollide.insert(pNode_2);
#endif // MathTools_Octree_DEBUG

			// If both are leaf nodes then...
			if (OctreeTools::AreBothLeafNodes(pNode_1, pNode_2))
			{
#if MathTools_Octree_DEBUG
				// Render out collision volumes that collided using the color red
				for (const OctreeNode* pCollidedNodes : nodesThatCollide)
				{
					Visualizer::ShowCollisionVolume(pCollidedNodes->getOBB(), Colors::Red);
				}
#endif // MathTools_Octree_DEBUG

				// An intersection has occured
				return true;
			}
			// Else if descend the first node then...
			else if (OctreeTools::ShouldDescendFirstNode(pNode_1, pNode_2))
			{
				// We add all node 1's child nodes to test against node 2.
				OctreeTools::AddChildNodesToTest(pNode_1->getChildren(), pNode_2, nodePairsToTest);
			}
			// Else...
			else
			{
				// We add all node 2's child nodes to test against node 1.
				OctreeTools::AddChildNodesToTest(pNode_2->getChildren(), pNode_1, nodePairsToTest);
			}
		}
	}

#if MathTools_Octree_DEBUG
	// Render out collision volumes that had collided during testing using the color blue
	for (auto& pCollidedNodes : nodesThatCollide)
	{
		Visualizer::ShowCollisionVolume(pCollidedNodes->getOBB(), Colors::Blue);
	}
#endif // MathTools_Octree_DEBUG

	// Otherwise no intestections has occured
	return false;
}

bool MathTools::Intersect(const CollisionVolume& collisionVolume, const CollisionVolumeOctree& Octree)
{
#if MathTools_Octree_DEBUG
	// Create list for rendering collision volumes for debugging
	std::list<const OctreeNode*> nodesThatCollide;
#endif // MathTools_Octree_DEBUG

	OctreeTools::NodeStack nodesToTest;
	nodesToTest.push(Octree.getRoot());

	while (!nodesToTest.empty())
	{
		const OctreeNode* pNode = nodesToTest.top();
		nodesToTest.pop();

		if (MathTools::Intersect(collisionVolume, pNode->getOBB()))
		{
#if MathTools_Octree_DEBUG
			nodesThatCollide.push_back(pNode);
#endif // MathTools_Octree_DEBUG

			if (pNode->isLeafNode())
			{
#if MathTools_Octree_DEBUG
				// Render out collision volumes that collided using the color red
				for (const OctreeNode* pCollideNode : nodesThatCollide)
				{
					Visualizer::ShowCollisionVolume(pCollideNode->getOBB(), Colors::Red);
				}
#endif // MathTools_Octree_DEBUG

				return true;
			}
			else
			{
				OctreeTools::AddChildNodesToTest(pNode->getChildren(), nodesToTest);
			}
		}
	}

#if MathTools_Octree_DEBUG
	// Render out collision volumes that had collided during testing using the color blue
	for (auto& pCollideNode : nodesThatCollide)
	{
		Visualizer::ShowCollisionVolume(pCollideNode->getOBB(), Colors::Blue);
	}
#endif // MathTools_Octree_DEBUG

	return false;
}

// Points
bool MathTools::Intersect(const CollisionVolumeAABB& AABB, const Vect& point)
{
	const Vect& min = AABB.getMinWorldVertex();
	const Vect& max = AABB.getMaxWorldVertex();

	return MathTools::IsInRange(point, min, max);
}

bool MathTools::Intersect(const CollisionVolumeOBB& OBB, const Vect& point)
{
	const Vect& min = OBB.getMinLocalVertex();
	const Vect& max = OBB.getMaxLocalVertex();

	return MathTools::IsInRange(point * OBB.getWorldMatrix().getInv(), min, max);
}

// nodeOBB intersection helpers
void MathTools::OutputAxesToTest(const CollisionVolumeOBB& OBB_1, const CollisionVolumeOBB& OBB_2, Vect* axes)
{
	int axisX_1 = 0, axisY_1 = 1, axisZ_1 = 2;
	int axisX_2 = 3, axisY_2 = 4, axisZ_2 = 5;

	axes[axisX_1] = OBB_1.getWorldMatrix().get(ROW_0);
	axes[axisY_1] = OBB_1.getWorldMatrix().get(ROW_1);
	axes[axisZ_1] = OBB_1.getWorldMatrix().get(ROW_2);

	axes[axisX_2] = OBB_2.getWorldMatrix().get(ROW_0);
	axes[axisY_2] = OBB_2.getWorldMatrix().get(ROW_1);
	axes[axisZ_2] = OBB_2.getWorldMatrix().get(ROW_2);

	axes[6] = axes[axisX_1].cross(axes[axisX_2]); axes[6][w] = 0;
	axes[7] = axes[axisX_1].cross(axes[axisY_2]); axes[7][w] = 0;
	axes[8] = axes[axisX_1].cross(axes[axisZ_2]); axes[8][w] = 0;

	axes[9] = axes[axisY_1].cross(axes[axisX_2]); axes[9][w] = 0;
	axes[10] = axes[axisY_1].cross(axes[axisY_2]); axes[10][w] = 0;
	axes[11] = axes[axisY_1].cross(axes[axisZ_2]); axes[11][w] = 0;

	axes[12] = axes[axisZ_1].cross(axes[axisX_2]); axes[12][w] = 0;
	axes[13] = axes[axisZ_1].cross(axes[axisY_2]); axes[13][w] = 0;
	axes[14] = axes[axisZ_1].cross(axes[axisZ_2]); axes[14][w] = 0;
}

void MathTools::OutputAxesToTest(const CollisionVolumeAABB& AABB, const CollisionVolumeOBB& OBB, Vect* axes)
{
	int axisX_1 = 0, axisY_1 = 1, axisZ_1 = 2;
	int axisX_2 = 3, axisY_2 = 4, axisZ_2 = 5;

	axes[axisX_1] = AABB.getWorldMatrix().get(ROW_0);
	axes[axisY_1] = AABB.getWorldMatrix().get(ROW_1);
	axes[axisZ_1] = AABB.getWorldMatrix().get(ROW_2);

	axes[axisX_2] = OBB.getWorldMatrix().get(ROW_0);
	axes[axisY_2] = OBB.getWorldMatrix().get(ROW_1);
	axes[axisZ_2] = OBB.getWorldMatrix().get(ROW_2);

	axes[6] = axes[axisX_1].cross(axes[axisX_2]); axes[6][w] = 0;
	axes[7] = axes[axisX_1].cross(axes[axisY_2]); axes[7][w] = 0;
	axes[8] = axes[axisX_1].cross(axes[axisZ_2]); axes[8][w] = 0;

	axes[9] = axes[axisY_1].cross(axes[axisX_2]); axes[9][w] = 0;
	axes[10] = axes[axisY_1].cross(axes[axisY_2]); axes[10][w] = 0;
	axes[11] = axes[axisY_1].cross(axes[axisZ_2]); axes[11][w] = 0;

	axes[12] = axes[axisZ_1].cross(axes[axisX_2]); axes[12][w] = 0;
	axes[13] = axes[axisZ_1].cross(axes[axisY_2]); axes[13][w] = 0;
	axes[14] = axes[axisZ_1].cross(axes[axisZ_2]); axes[14][w] = 0;
}

bool MathTools::DoesOverlapsOnAxis(const CollisionVolumeOBB& OBB_1, const CollisionVolumeOBB& OBB_2, const Vect& axis)
{
	float d = abs(MathTools::ProjectionLength(OBB_2.getWorldCenter() - OBB_1.getWorldCenter(), axis));
	float p1 = getMaxBoxProjectionLength(OBB_1, axis);
	float p2 = getMaxBoxProjectionLength(OBB_2, axis);

#if MathTools_DEBUG

	Vect center = (OBB_2.getWorldCenter() + OBB_1.getWorldCenter()) * 0.5f;

	Vect a = MathTools::Projection(OBB_1.getWorldCenter() - center, axis);
	Vect b = MathTools::Projection(OBB_2.getWorldCenter() - center, axis);
	Visualizer::ShowPointAt(center + a, Colors::Orange);
	Visualizer::ShowPointAt(center + b, Colors::Red);

	Vect obb1CenterOnAxis = center + a;
	Vect obb2CenterOnAxis = center + b;
	Visualizer::ShowLineSegment(obb1CenterOnAxis + axis.getNorm() * p1, obb1CenterOnAxis - axis.getNorm() * p1, Colors::Blue);
	Visualizer::ShowLineSegment(obb2CenterOnAxis + axis.getNorm() * p2, obb2CenterOnAxis - axis.getNorm() * p2, Colors::Green);

#endif // MathTools_DEBUG

	return d <= p1 + p2;
}

bool MathTools::DoesOverlapsOnAxis(const CollisionVolumeAABB& AABB, const CollisionVolumeOBB& OBB, const Vect& axis)
{
	float d = abs(MathTools::ProjectionLength(AABB.getWorldCenter() - OBB.getWorldCenter(), axis));
	float p1 = getMaxBoxProjectionLength(AABB, axis);
	float p2 = getMaxBoxProjectionLength(OBB, axis);

#if MathTools_DEBUG

	Vect center = (AABB.getWorldCenter() + OBB.getWorldCenter()) * 0.5f;

	Vect a = MathTools::Projection(AABB.getWorldCenter() - center, axis);
	Vect b = MathTools::Projection(OBB.getWorldCenter() - center, axis);
	Visualizer::ShowPointAt(center + a, Colors::Orange);
	Visualizer::ShowPointAt(center + b, Colors::Red);

	Vect obb1CenterOnAxis = center + a;
	Vect obb2CenterOnAxis = center + b;
	Visualizer::ShowLineSegment(obb1CenterOnAxis + axis.getNorm() * p1, obb1CenterOnAxis - axis.getNorm() * p1, Colors::Blue);
	Visualizer::ShowLineSegment(obb2CenterOnAxis + axis.getNorm() * p2, obb2CenterOnAxis - axis.getNorm() * p2, Colors::Green);

#endif // MathTools_DEBUG

	return d <= p1 + p2;
}

float MathTools::getMaxBoxProjectionLength(const CollisionVolumeOBB& OBB, const Vect& axis)
{
	Vect zero = Vect(0.0f, 0.0f, 0.0f);
	Matrix inverseWorld = OBB.getInverseWorldMatrix(); inverseWorld.set(ROW_3, zero);
	Vect axisLocalSpace = axis * inverseWorld;

	float maxProjectionLength = 0.0f;

	maxProjectionLength += std::abs((axisLocalSpace[x] * OBB.getLocalHalfDiagonal()[x]));
	maxProjectionLength += std::abs((axisLocalSpace[y] * OBB.getLocalHalfDiagonal()[y]));
	maxProjectionLength += std::abs((axisLocalSpace[z] * OBB.getLocalHalfDiagonal()[z]));
	maxProjectionLength /= axis.mag();
	maxProjectionLength *= OBB.getScalingFactorSquared();

	return maxProjectionLength;
}

float MathTools::getMaxBoxProjectionLength(const CollisionVolumeAABB& AABB, const Vect& axis)
{
	Vect zero = Vect(0.0f, 0.0f, 0.0f);
	Matrix inverseWorld = AABB.getInverseWorldMatrix(); inverseWorld.set(ROW_3, zero);
	Vect axisLocalSpace = axis * inverseWorld;

	float maxProjectionLength = 0.0f;

	maxProjectionLength += std::abs((axisLocalSpace[x] * AABB.getLocalHalfDiagonal()[x]));
	maxProjectionLength += std::abs((axisLocalSpace[y] * AABB.getLocalHalfDiagonal()[y]));
	maxProjectionLength += std::abs((axisLocalSpace[z] * AABB.getLocalHalfDiagonal()[z]));
	maxProjectionLength /= axis.mag();
	maxProjectionLength *= AABB.getScalingFactorSquared();

	return maxProjectionLength;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Box Triangle Intersections
//-----------------------------------------------------------------------------------------------------------------------------

bool MathTools::Intersect(const CollisionVolumeOBB& OBB, const Triangle& triangle)
{
	Triangle adjustTriangle = MathTools::AdjustTriangle(OBB, triangle);

	const int numberOfAxes = 13;
	Vect axes[numberOfAxes];
	MathTools::OutputAxesToTest(OBB, adjustTriangle, axes);

	bool doesIntersects = true;

	for (int i = 0; i < numberOfAxes && doesIntersects; i++)
	{
		const Vect& axis = axes[i];
		if (axis.magSqr() > FLT_EPSILON)
		{
			doesIntersects = MathTools::DoesOverlapsOnAxis(OBB, adjustTriangle, axis);
		}
	}

	return doesIntersects;
}

Triangle MathTools::AdjustTriangle(const CollisionVolumeOBB& OBB, const Triangle& triangle)
{
	Triangle adjustedTriangle = triangle;

	adjustedTriangle *= OBB.getInverseWorldMatrix();
	adjustedTriangle -= (OBB.getMaxLocalVertex() + OBB.getMinLocalVertex()) * 0.5f;

	return adjustedTriangle;
}

void MathTools::OutputAxesToTest(const CollisionVolumeOBB&, const Triangle& triangle, Vect* axes)
{
	int i = 0;

	Vect xNormal = Vect(1.0f, 0.0f, 0.0f, 0.0f);
	Vect yNormal = Vect(0.0f, 1.0f, 0.0f, 0.0f);
	Vect zNormal = Vect(0.0f, 0.0f, 1.0f, 0.0f);
	Vect triangeNormal = triangle.computeNormal();

	axes[i] = xNormal.cross(triangle.getEdge01()).getNorm(); axes[i][w] = 0; i++;
	axes[i] = xNormal.cross(triangle.getEdge12()).getNorm(); axes[i][w] = 0; i++;
	axes[i] = xNormal.cross(triangle.getEdge20()).getNorm(); axes[i][w] = 0; i++;
	axes[i] = yNormal.cross(triangle.getEdge01()).getNorm(); axes[i][w] = 0; i++;
	axes[i] = yNormal.cross(triangle.getEdge12()).getNorm(); axes[i][w] = 0; i++;
	axes[i] = yNormal.cross(triangle.getEdge20()).getNorm(); axes[i][w] = 0; i++;
	axes[i] = zNormal.cross(triangle.getEdge01()).getNorm(); axes[i][w] = 0; i++;
	axes[i] = zNormal.cross(triangle.getEdge12()).getNorm(); axes[i][w] = 0; i++;
	axes[i] = zNormal.cross(triangle.getEdge20()).getNorm(); axes[i][w] = 0; i++;

	axes[i] = xNormal; axes[i][w] = 0; i++;
	axes[i] = yNormal; axes[i][w] = 0; i++;
	axes[i] = zNormal; axes[i][w] = 0; i++;

	axes[i] = triangeNormal.getNorm(); axes[i][w] = 0; i++;
}

bool MathTools::DoesOverlapsOnAxis(const CollisionVolumeOBB& OBB, const Triangle& triangle, const Vect& axis)
{
	float r = MathTools::getMaxBoxProjectionLength(OBB, axis);

	std::array<float, 3> triangleProjection = { 0.0f, 0.0f, 0.0f };
	int i = 0;

	triangleProjection[i] = MathTools::ProjectionLength(triangle.getVertex0(), axis); ++i;
	triangleProjection[i] = MathTools::ProjectionLength(triangle.getVertex1(), axis); ++i;
	triangleProjection[i] = MathTools::ProjectionLength(triangle.getVertex2(), axis); ++i;

	float max = (*std::max_element(triangleProjection.begin(), triangleProjection.end()));
	float min = (*std::min_element(triangleProjection.begin(), triangleProjection.end()));

	return !(std::max(-max, min) > r);
}

//-----------------------------------------------------------------------------------------------------------------------------
// World Matrix Decomposition
//-----------------------------------------------------------------------------------------------------------------------------

// ---> Scale
Matrix MathTools::ExtractScaleMatrix(const Matrix& matrix)
{
	Vect scale = ExtractScaleXYZ(matrix);
	return Matrix(SCALE, scale);
}

Vect MathTools::ExtractScaleXYZ(const Matrix& matrix)
{
	float scaleX = ExtractScaleX(matrix);
	float scaleY = ExtractScaleY(matrix);
	float scaleZ = ExtractScaleZ(matrix);

	return Vect(scaleX, scaleY, scaleZ);
}

float MathTools::ExtractScaleX(const Matrix& matrix)
{
	return matrix.get(MatrixRowType::ROW_0).mag();
}

float MathTools::ExtractScaleY(const Matrix& matrix)
{
	return matrix.get(MatrixRowType::ROW_1).mag();
}

float MathTools::ExtractScaleZ(const Matrix& matrix)
{
	return matrix.get(MatrixRowType::ROW_2).mag();
}

// ---> Translation
Matrix MathTools::ExtractTranslationMatrix(const Matrix& matrix)
{
	return Matrix(TRANS, ExtractTranslationXYZ(matrix));
}

Vect MathTools::ExtractTranslationXYZ(const Matrix& matrix)
{
	return matrix.get(MatrixRowType::ROW_3);
}

Matrix MathTools::RotationFromTowards(const Vect& current, const Vect& target)
{
	Vect rotationAxis = current.cross(target);
	float rotationAngle = acosf(current.dot(target) / (current.mag() * target.mag()));
	return Matrix(ROT_AXIS_ANGLE, rotationAxis, rotationAngle);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Vect functions
//-----------------------------------------------------------------------------------------------------------------------------

Vect MathTools::MultiplyComponents(const Vect& vect_1, const Vect& vect_2)
{
	return Vect(vect_1[x] * vect_2[x],
		vect_1[y] * vect_2[y],
		vect_1[z] * vect_2[z]);
}

Vect MathTools::Min(const Vect& vect_1, const Vect& vect_2)
{
	return Vect(std::min(vect_1[x], vect_2[x]),
		std::min(vect_1[y], vect_2[y]),
		std::min(vect_1[z], vect_2[z]));
}

Vect MathTools::Max(const Vect& vect_1, const Vect& vect_2)
{
	return Vect(std::max(vect_1[x], vect_2[x]),
		std::max(vect_1[y], vect_2[y]),
		std::max(vect_1[z], vect_2[z]));
}

Vect MathTools::Clamp(const Vect& value, const Vect& min, const Vect& max)
{
	return Vect(MathTools::Clamp(value[x], min[x], max[x]),
		MathTools::Clamp(value[y], min[y], max[y]),
		MathTools::Clamp(value[z], min[z], max[z]));
}

Vect MathTools::Projection(const Vect& vect_1, const Vect& vect_2)
{
	return ((vect_1.dot(vect_2)) / (vect_2.dot(vect_2))) * vect_2;
}

float MathTools::ProjectionLength(const Vect& vect_1, const Vect& vect_2)
{
	return vect_1.dot(vect_2) / vect_2.mag();
}

float MathTools::power(float base, int exponent)
{
	if (exponent < 0)
	{
		base = 1.0f / base;
		exponent *= -1;
	}

	float answer = 1.0f;

	for (int i = 0; i < exponent; i++)
	{
		answer *= base;
	}

	return answer;
}

bool MathTools::IsInRange(const Vect& vect, const Vect& vect_1, const Vect& vect_2)
{
	return IsInRange(vect[x], vect_1[x], vect_2[x])
		&& IsInRange(vect[y], vect_1[y], vect_2[y])
		&& IsInRange(vect[z], vect_1[z], vect_2[z]);
}

bool MathTools::IsInRange(float number, float number_1, float number_2)
{
	float start, end;
	if (number_1 > number_2)
	{
		end = number_1;
		start = number_2;
	}
	else
	{
		end = number_2;
		start = number_1;
	}

	return number >= start && number <= end;
}

bool MathTools::IsLessThan(const Vect& vect_1, const Vect& vect_2)
{
	bool islessThanX = vect_1[x] <= vect_2[x];
	bool islessThanY = vect_1[y] <= vect_2[y];
	bool islessThanZ = vect_1[z] <= vect_2[z];
	return islessThanX && islessThanY && islessThanZ;
}

bool MathTools::IsGreaterThan(const Vect& vect_1, const Vect& vect_2)
{
	bool ismoreThanX = vect_1[x] >= vect_2[x];
	bool ismoreThanY = vect_1[y] >= vect_2[y];
	bool ismoreThanZ = vect_1[z] >= vect_2[z];
	return ismoreThanX && ismoreThanY && ismoreThanZ;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Others
//-----------------------------------------------------------------------------------------------------------------------------
bool MathTools::DoIntervalsOverlap(const Interval& interval_1, const Interval& interval_2)
{
	return !(interval_1._end < interval_2._start || interval_2._end < interval_1._start);
}