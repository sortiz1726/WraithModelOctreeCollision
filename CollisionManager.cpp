#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "CollisionTestCommand.h"
#include "CollisionVolumeAABB.h"
#include "Visualizer.h"
#include "Colors.h"

CollisionManager::CollisionTypeID CollisionManager::NextCollisionIDNumber = 0;
const size_t CollisionManager::MAX_GROUP_SIZE = 20;

CollisionManager::CollisionManager()
{
	_collidableGroups.resize(CollisionManager::MAX_GROUP_SIZE, nullptr);

	for (CollidableGroup*& pCollidableGroups : _collidableGroups)
	{
		pCollidableGroups = new CollidableGroup();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Deinitialization
//-----------------------------------------------------------------------------------------------------------------------------
CollisionManager::~CollisionManager()
{
	deinitializeCollisionGroups();
	deinitializeCollisionTestCommands();
}

void CollisionManager::deinitializeCollisionGroups()
{
	for (CollidableGroup* pCollidableGroup : _collidableGroups)
	{
		delete pCollidableGroup;
	}
	_collidableGroups.clear();
}

void CollisionManager::deinitializeCollisionTestCommands()
{
	for (CollisionTestCommand* pCommand : _collisionTestCommands)
	{
		delete pCommand;
	}
	_collisionTestCommands.clear();
}

//-----------------------------------------------------------------------------------------------------------------------------
// Process Collision
//-----------------------------------------------------------------------------------------------------------------------------
void CollisionManager::processCollisions()
{
	// First update all group AABBs before...
	for (CollidableGroup* pCollidableGroup : _collidableGroups)
	{
		pCollidableGroup->updateGroupAABB();
	}

	// Executing the commands to test the collision
	for (CollisionTestCommand* pCommand : _collisionTestCommands)
	{
		pCommand->execute();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setting/Getting Collidable Groups
//-----------------------------------------------------------------------------------------------------------------------------
CollidableGroup* CollisionManager::getCollidableGroup(CollisionTypeID collisionIDIndex) const
{
	return _collidableGroups.at(collisionIDIndex);
}

void CollisionManager::setGroupForTypeID(CollisionTypeID collisionIDIndex)
{
	if (_collidableGroups.at(collisionIDIndex) == nullptr)
	{
		_collidableGroups.at(collisionIDIndex) = new CollidableGroup();
	}
}

// ---> Setting Collidable Groups helper
void CollisionManager::checkAndAdjustForIndex(CollisionTypeID collisionIDIndex)
{
	if (!isValidIndex(collisionIDIndex))
	{
		resizeToFit(collisionIDIndex);
	}
}

bool CollisionManager::isValidIndex(CollisionTypeID collisionIDIndex) const
{
	return (_collidableGroups.size() > static_cast<size_t>(collisionIDIndex));
}

void CollisionManager::resizeToFit(CollisionTypeID collisionIDIndex)
{
	_collidableGroups.resize(collisionIDIndex + 1, nullptr);
}