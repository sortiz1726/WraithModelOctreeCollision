#ifndef _Collidable
#define _Collidable

#include "RegistrationStates.h"
#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionRegisterCommand;
class CollisionDeregisterCommand;

class Collidable
{
	friend class CollidableAttorney;
public:
	/**********************************************************************************************//**
	 * <summary> Values that represent volume types.</summary>
	 *	\ingroup COLLISION
	 * 
	 * <remarks> To be used in GameObject::setColliderModel(). Currently there is
	 *   Collidable::VolumeType::BSPHERE, 
	 *	 Collidable::VolumeType::AABB, 
	 *   and Collidable::VolumeType::OBB </remarks>
	 **************************************************************************************************/
	enum class VolumeType
	{
		BSPHERE,
		AABB,
		OBB
	};
	
	/**********************************************************************************************//**
	* <summary> Values that represent volume hierarchy htypes.</summary>
	*	\ingroup COLLISION
	*
	 * <remarks> To be used in GameObject::setColliderModel(). Currently there is
	 *   Collidable::VolumeHierarchyType::OCTREE </remarks>
	**************************************************************************************************/
	enum class VolumeHierarchyType
	{
		OCTREE
	};

public:
	Collidable();
	Collidable(const Collidable&) = default;
	Collidable& operator=(const Collidable&) = default;
	Collidable(Collidable&&) = default;
	Collidable& operator=(Collidable&&) = default;
	virtual ~Collidable();

	/**********************************************************************************************//**
	* <summary> Gets the current collsion volume being used.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The collsion volume.</returns>
	**************************************************************************************************/
	const CollisionVolume& getCollisionVolume() const;

	/**********************************************************************************************//**
	* <summary> Gets the default BSphere.</summary>
	*
	* <remarks> </remarks>
	*
	* <returns> The BSphere.</returns>
	**************************************************************************************************/
	const CollisionVolumeBSphere& getBSphere() const;

	/**********************************************************************************************//**
	* <summary> Terrain collision callback for this object.</summary>
	* \ingroup COLLISION
	*
	* <remarks> To be implemented by user in object derived from GameObject (NOT directly derived from Collidable).
	* 			 Called ONLY by current active scene.
	* 			 </remarks>
	* 
	**************************************************************************************************/
	virtual void terrainCollision();

protected:
	// Collsion Volumes

	/**********************************************************************************************//**
	 * <summary> Sets collider model and Collision Volume type.</summary>
	 * \ingroup COLLISION
	 * <remarks> MUST be set if collisions are to be used. </remarks>
	 *
	* <param name="pColliderModel"> pointer to a collider model.</param>
	 * <param name="volumeType"> collision volume type to be used.</param>
	 **************************************************************************************************/
	void setColliderModel(Model* pColliderModel, VolumeType volumeType);

	/**********************************************************************************************//**
	* <summary> Sets collider model and Collision Volume Hierarchy type.</summary>
	* \ingroup COLLISION
	* <remarks> MUST be set if collisions are to be used. </remarks>
	*
	* <param name="pColliderModel"> pointer to a collider model.</param>
	* <param name="volumeType"> collision volume type to be used.</param>
	* <param name="maxDepth"> The maximum depth of volume hierarchy.</param>
	**************************************************************************************************/
	void setColliderModel(Model* pColliderModel, VolumeHierarchyType volumeHierarchyType, int maxDepth);

	/**********************************************************************************************//**
	 * <summary> Updates the collision data described by world matrix.</summary>
	 * \ingroup COLLISION
	 * <remarks> Must be called whenever the world matrix has changed. </remarks>
	 *
	 * <param name="world"> The world.</param>
	 **************************************************************************************************/
	void updateCollisionData(const Matrix& world);

	// Registration/Deregistration

	/**********************************************************************************************//**
	 * <summary> Sets collidable group.</summary>
	 * \ingroup COLLISION
	 * <remarks> Must be called when the GameObject enters the scene for the first time
	 * 			 and will use collisions. </remarks>
	 *
	 * <typeparam name="UserClass"> Type of the user class.</typeparam>
	 **************************************************************************************************/
	template<class UserClass>
	void setCollidableGroup()
	{
		{
			CollisionManager& collisionManager = SceneAttorney::RegistrationAccess::GetCollisionManager();
			_myCollisionTypeID = collisionManager.getCollisionTypeID<UserClass>();
		}
	}

	/**********************************************************************************************//**
	 * <summary> Submit collision registration to current scene.</summary>
	 * \ingroup COLLISION
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void submitCollisionRegistration();

	/**********************************************************************************************//**
	 * <summary> Submit collision deregistration.</summary>
	 * \ingroup COLLISION
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void submitCollisionDeregistration();

	/**********************************************************************************************//**
	 * <summary> Query if this object is registered for collisions.</summary>
	 * \ingroup COLLISION
	 * <remarks> </remarks>
	 *
	 * <returns> True if registered for collisions, false if not.</returns>
	 **************************************************************************************************/
	bool isRegisteredForCollisions() const;

private:
	// Registration/Deregistration

	/**********************************************************************************************//**
	 * <summary> Registers to the current scene.</summary>
	 *
	 * <remarks> DELAYED called with a command. NOT called by the user. </remarks>
	 **************************************************************************************************/
	void registerToScene();

	/**********************************************************************************************//**
	 * <summary> Deregisters from the current scene.</summary>
	 *
	 * <remarks> DELAYED called with a command. NOT called by the user. </remarks>
	 **************************************************************************************************/
	void deregisterFromScene();

private:
	// Collision Volume Properites
	CollisionVolume* _pCollisionVolume;
	CollisionVolumeBSphere* _pBSphere;
	Model* _pColliderModel;

	// De/Registration Properties
	CollisionManager::CollisionTypeID _myCollisionTypeID;

	CollidableGroup::StorageReference _deleteReference;

	CollisionRegisterCommand* _pCollisionRegisterCommand;
	CollisionDeregisterCommand* _pCollisionDeregisterCommand;

	RegistrationState _currentRegistrationState;
};

#endif // !_Collidable

//-----------------------------------------------------------------------------------------------------------------------------
// Collidable Comment Template
//-----------------------------------------------------------------------------------------------------------------------------