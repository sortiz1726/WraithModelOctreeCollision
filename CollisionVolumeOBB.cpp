#include "CollisionVolumeOBB.h"
#include "VisualizerAttorney.h"
#include "MathTools.h"

void CollisionVolumeOBB::computeData(Model* pModel, const Matrix& worldMatrix)
{
	computeData(pModel->getMinAABB(), pModel->getMaxAABB(), worldMatrix);
}

void CollisionVolumeOBB::computeData(const Vect& minWorldVertex, const Vect& maxWorldVertex, const Matrix& worldMatrix)
{
	setMinMaxLocalVertex(minWorldVertex, maxWorldVertex);
	setWorldMatrix(worldMatrix);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Intersection
//-----------------------------------------------------------------------------------------------------------------------------

bool CollisionVolumeOBB::intersectAccept(const CollisionVolume& collisionVolume) const
{
	return collisionVolume.intersectVisitor(*this);
}

bool CollisionVolumeOBB::intersectVisitor(const CollisionVolumeBSphere& collisionBSphere) const
{
	return MathTools::Intersect(collisionBSphere, *this);
}

bool CollisionVolumeOBB::intersectVisitor(const CollisionVolumeAABB& AABB) const
{
	return MathTools::Intersect(AABB, *this);
}

bool CollisionVolumeOBB::intersectVisitor(const CollisionVolumeOBB& OBB) const
{
	return MathTools::Intersect(OBB, *this);
}

bool CollisionVolumeOBB::intersectVisitor(const CollisionVolumeOctree& Octree) const
{
	return MathTools::Intersect(*this, Octree);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Debugging
//-----------------------------------------------------------------------------------------------------------------------------
void CollisionVolumeOBB::debugDraw(const Vect& color, int depth) const
{
	depth; // is ignored
	VisualizerAttorney::RenderAccess::ShowOBB(*this, color);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setters
//-----------------------------------------------------------------------------------------------------------------------------
void CollisionVolumeOBB::setMinMaxLocalVertex(const Vect& minlocalVertex, const Vect& maxlocalVertex)
{
	_minLocalVertex = minlocalVertex;
	_maxLocalVertex = maxlocalVertex;
	_localHalfDiagonal = 0.5f * (_maxLocalVertex - _minLocalVertex);
}

void CollisionVolumeOBB::setWorldMatrix(const Matrix& worldMatrix)
{
	_worldMatrix = worldMatrix;
	_inverseWorldMatrix = _worldMatrix.getInv();
	_worldCenter = (_minLocalVertex + _localHalfDiagonal) * _worldMatrix;
	_scalingFactorSqaured = _worldMatrix.get(MatrixRowType::ROW_0).magSqr();
}

//-----------------------------------------------------------------------------------------------------------------------------
// Getters
//-----------------------------------------------------------------------------------------------------------------------------
const Matrix& CollisionVolumeOBB::getWorldMatrix() const
{
	return _worldMatrix;
}

const Matrix& CollisionVolumeOBB::getInverseWorldMatrix() const
{
	return _inverseWorldMatrix;
}

const Vect& CollisionVolumeOBB::getMinLocalVertex() const
{
	return _minLocalVertex;
}

const Vect& CollisionVolumeOBB::getMaxLocalVertex() const
{
	return _maxLocalVertex;
}

const Vect& CollisionVolumeOBB::getLocalHalfDiagonal() const
{
	return _localHalfDiagonal;
}

const Vect& CollisionVolumeOBB::getWorldCenter() const
{
	return _worldCenter;
}

float CollisionVolumeOBB::getScalingFactorSquared() const
{
	return _scalingFactorSqaured;
}

int CollisionVolumeOBB::getMaxDepth() const
{
	return 0;
}
