#ifndef _CollisionVolumeOBB
#define _CollisionVolumeOBB

#include "AzulCore.h"
#include "CollisionVolume.h"

/**********************************************************************************************//**
 * <summary> An OBB Collision volume</summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/
class CollisionVolumeOBB : public CollisionVolume
{
public:
	CollisionVolumeOBB() = default;
	CollisionVolumeOBB(const CollisionVolumeOBB&) = default;
	CollisionVolumeOBB& operator=(const CollisionVolumeOBB&) = default;
	CollisionVolumeOBB(CollisionVolumeOBB&&) = default;
	CollisionVolumeOBB& operator=(CollisionVolumeOBB&&) = default;
	~CollisionVolumeOBB() = default;

	/**********************************************************************************************//**
	 * <summary> Calculates the data for OBB.
	 * 			 In this case the center.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pModel"> the pointer to a model.</param>
	 * <param name="worldMatrix"> The world matrix.</param>
	 **************************************************************************************************/
	virtual void computeData(Model* pModel, const Matrix& worldMatrix) override;

	/**********************************************************************************************//**
	* <summary> Calculates the data for OBB.
	* 			 In this case the center.</summary>
	*
	* <remarks> </remarks>
	*
	* <param name="minWorldVertex"> The min local vertex.</param>
	* <param name="maxWorldVertex"> The max local vertex.</param>
	* <param name="worldMatrix"> The world matrix.</param>
	**************************************************************************************************/
	void computeData(const Vect& minWorldVertex, const Vect& maxWorldVertex, const Matrix& worldMatrix);

	virtual bool intersectAccept(const CollisionVolume& collisionVolume) const override;
	virtual bool intersectVisitor(const CollisionVolumeBSphere& collisionBSphere) const override;
	virtual bool intersectVisitor(const CollisionVolumeAABB& AABB) const override;
	virtual bool intersectVisitor(const CollisionVolumeOBB& OBB) const override;
	virtual bool intersectVisitor(const CollisionVolumeOctree& Octree) const override;

	// Setters

	/**********************************************************************************************//**
	 * <summary> Sets the minimum and maximum vertex in local space.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="minWorldVertex"> The min local vertex.</param>
	 * <param name="maxWorldVertex"> The max local vertex.</param>
	**************************************************************************************************/
	void setMinMaxLocalVertex(const Vect& minlocalVertex, const Vect& maxlocalVertex);

	/**********************************************************************************************//**
	 * <summary> Sets the world matrix.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="worldMatrix"> The world matrix.</param>
	**************************************************************************************************/
	void setWorldMatrix(const Matrix& worldMatrix);

	/**********************************************************************************************//**
	* <summary> Gets the world matrix of OBB.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The world matrix.</returns>
	**************************************************************************************************/
	const Matrix& getWorldMatrix() const;

	/**********************************************************************************************//**
	* <summary> Gets the inverse world matrix of OBB.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The world matrix.</returns>
	**************************************************************************************************/
	const Matrix& getInverseWorldMatrix() const;

	/**********************************************************************************************//**
	* <summary> Gets the minimum vertex in local space.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The minimum vertex.</returns>
	**************************************************************************************************/
	const Vect& getMinLocalVertex() const;

	/**********************************************************************************************//**
	* <summary> Gets the maximum vertex in local space.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The maximum vertex.</returns>
	**************************************************************************************************/
	const Vect& getMaxLocalVertex() const;

	/**********************************************************************************************//**
	* <summary> Gets the half diagonal of OBB in local space.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The half diagonal.</returns>
	**************************************************************************************************/
	const Vect& getLocalHalfDiagonal() const;

	/**********************************************************************************************//**
	* <summary> Gets the center position of OBB in world space.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The center.</returns>
	**************************************************************************************************/
	const Vect& getWorldCenter() const;

	/**********************************************************************************************//**
	* <summary> Gets scaling factor sqaured of OBB.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The scaling factor squared.</returns>
	**************************************************************************************************/
	float getScalingFactorSquared() const;

	virtual int getMaxDepth() const override;

private:
	// Debugging
	virtual void debugDraw(const Vect& color, int depth) const override;

private:
	Matrix _worldMatrix;
	Matrix _inverseWorldMatrix;
	Vect _minLocalVertex;
	Vect _maxLocalVertex;
	Vect _localHalfDiagonal;
	Vect _worldCenter;
	float _scalingFactorSqaured;
};
#endif // !_CollisionVolumeOBB

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionVolumeOBB Comment Template
//-----------------------------------------------------------------------------------------------------------------------------