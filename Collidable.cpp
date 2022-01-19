#include "Collidable.h"
#include "SceneAttorney.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "CollisionRegisterCommand.h"
#include "CollisionDeregisterCommand.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "CollisionVolumeOctree.h"

Collidable::Collidable()
	: _pCollisionVolume(nullptr), _pBSphere(new CollisionVolumeBSphere()), _pColliderModel(nullptr),
	_myCollisionTypeID(CollisionManager::ID_UNDEFINED),
	_pCollisionRegisterCommand(new CollisionRegisterCommand(this)),
	_pCollisionDeregisterCommand(new CollisionDeregisterCommand(this)),
	_currentRegistrationState(RegistrationState::CURRENTLY_DEREGISTERED)
{}

Collidable::~Collidable()
{
	delete _pCollisionVolume;
	delete _pBSphere;
	delete _pCollisionRegisterCommand;
	delete _pCollisionDeregisterCommand;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Collsion Volumes
//-----------------------------------------------------------------------------------------------------------------------------
const CollisionVolume& Collidable::getCollisionVolume() const
{
	return *_pCollisionVolume;
}

void Collidable::setColliderModel(Model* pColliderModel, VolumeType volumeType)
{
	_pColliderModel = pColliderModel;
	delete _pCollisionVolume;
	switch (volumeType)
	{
	case Collidable::VolumeType::BSPHERE:
		_pCollisionVolume = new CollisionVolumeBSphere();
		break;
	case Collidable::VolumeType::AABB:
		_pCollisionVolume = new CollisionVolumeAABB();
		break;
	case Collidable::VolumeType::OBB:
		_pCollisionVolume = new CollisionVolumeOBB();
		break;
	default:
		break;
	}
}

void Collidable::setColliderModel(Model* pColliderModel, VolumeHierarchyType volumeHierarchyType, int maxDepth)
{
	_pColliderModel = pColliderModel;
	delete _pCollisionVolume;
	switch (volumeHierarchyType)
	{
	case Collidable::VolumeHierarchyType::OCTREE:
		_pCollisionVolume = new CollisionVolumeOctree(pColliderModel, maxDepth);
		break;
	default:
		break;
	}
}

void Collidable::updateCollisionData(const Matrix& world)
{
	_pCollisionVolume->computeData(_pColliderModel, world);
	_pBSphere->computeData(_pColliderModel, world);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Registration/Deregistration
//-----------------------------------------------------------------------------------------------------------------------------
void Collidable::submitCollisionRegistration()
{
	assert(_currentRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), _pCollisionRegisterCommand);
	_currentRegistrationState = RegistrationState::PENDING_REGISTRATION;
}

void Collidable::registerToScene()
{
	assert(_currentRegistrationState == RegistrationState::PENDING_REGISTRATION);
	CollisionManager& collisionManager = SceneAttorney::RegistrationAccess::GetCollisionManager();
	collisionManager.getCollidableGroup(_myCollisionTypeID)->registerEntity(this, _deleteReference);
	_currentRegistrationState = RegistrationState::CURRENTLY_REGISTERED;
}

void Collidable::submitCollisionDeregistration()
{
	assert(_currentRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), _pCollisionDeregisterCommand);
	_currentRegistrationState = RegistrationState::PENDING_DEREGISTRATION;
}

bool Collidable::isRegisteredForCollisions() const
{
	return _currentRegistrationState == RegistrationState::CURRENTLY_REGISTERED;
}

const CollisionVolumeBSphere& Collidable::getBSphere() const
{
	return *_pBSphere;
}

void Collidable::terrainCollision()
{}

void Collidable::deregisterFromScene()
{
	assert(_currentRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	CollisionManager& collisionManager = SceneAttorney::RegistrationAccess::GetCollisionManager();
	collisionManager.getCollidableGroup(_myCollisionTypeID)->deregisterEntity(_deleteReference);
	_currentRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}