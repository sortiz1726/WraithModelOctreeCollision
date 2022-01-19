#ifndef _CollisionVolume
#define _CollisionVolume

class Matrix;
class Vect;
class Model;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolumeOctree;

/**********************************************************************************************//**
 * <summary> A collision volume base class.</summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/
class CollisionVolume
{
	friend class CollisionVolumeAttorney;

public:
	CollisionVolume() = default;
	CollisionVolume(const CollisionVolume&) = default;
	CollisionVolume& operator=(const CollisionVolume&) = default;
	CollisionVolume(CollisionVolume&&) = default;
	CollisionVolume& operator=(CollisionVolume&&) = default;
	virtual ~CollisionVolume() = default;

	/**********************************************************************************************//**
	 * <summary> Calculates the data.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pModel">	  [in,out] If non-null, the model.</param>
	 * <param name="worldMatrix"> The world matrix.</param>
	 **************************************************************************************************/
	virtual void computeData(Model* pModel, const Matrix& worldMatrix) = 0;

	/**********************************************************************************************//**
	* <summary> Accepts a collision volume to perform intersect test.</summary>
	*
	* <remarks> Uses Visitor Pattern. This is the first step of the process.
	*           Then calls on intersectVisitor(). </remarks>
	*
	* <param name="collisionVolume"> a collision volume.</param>
	**************************************************************************************************/
	virtual bool intersectAccept(const CollisionVolume& collisionVolume) const = 0;

	/**********************************************************************************************//**
	* <summary> Visits a collision volume BSphere to perform intersect test.</summary>
	*
	* <remarks> Uses Visitor Pattern. This is the second step of the process. </remarks>
	*
	* <param name="collisionBSphere"> a collision volume BSphere.</param>
	**************************************************************************************************/
	virtual bool intersectVisitor(const CollisionVolumeBSphere& collisionBSphere) const = 0;

	/**********************************************************************************************//**
	* <summary> Visits a collision volume AABB to perform intersect test.</summary>
	*
	* <remarks> Uses Visitor Pattern. This is the second step of the process. </remarks>
	*
	* <param name="AABB"> a collision volume AABB.</param>
	**************************************************************************************************/
	virtual bool intersectVisitor(const CollisionVolumeAABB& AABB) const = 0;

	/**********************************************************************************************//**
	* <summary> Visits a collision volume OBB to perform intersect test.</summary>
	*
	* <remarks> Uses Visitor Pattern. This is the second step of the process. </remarks>
	*
	* <param name="OBB"> a collision volume OBB.</param>
	**************************************************************************************************/
	virtual bool intersectVisitor(const CollisionVolumeOBB& OBB) const = 0;

	/**********************************************************************************************//**
	* <summary> Visits a collision volume Octree to perform intersect test.</summary>
	*
	* <remarks> Uses Visitor Pattern. This is the second step of the process. </remarks>
	*
	* <param name="Octree"> a collision volume Octree.</param>
	**************************************************************************************************/
	virtual bool intersectVisitor(const CollisionVolumeOctree& Octree) const = 0;

	virtual int getMaxDepth() const = 0;

private:
	/**********************************************************************************************//**
	* <summary> Draws it collision volume.</summary>
	*
	* <remarks> Used for debuggin purposes. 
	*			Depth value is used only for Octree collision value.
	*			All other collision volumes ignore it. </remarks>
	*
	* <param name="color"> the color to render the collision volume.</param>
	* <param name="depth"> the depth to render collision volume.</param>
	**************************************************************************************************/
	virtual void debugDraw(const Vect& color, int depth) const = 0;
};
#endif // !_CollisionVolume

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionVolume Comment Template
//-----------------------------------------------------------------------------------------------------------------------------