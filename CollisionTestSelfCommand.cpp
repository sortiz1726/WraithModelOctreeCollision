#include "CollisionTestSelfCommand.h"
#include "CollidableGroup.h"
#include "CollisionDispatch.h"
#include "Collidable.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "MathTools.h"
#include "Visualizer.h"
#include "Colors.h"

#ifndef CollisionTestSelfCommand_DEBUG
#define CollisionTestSelfCommand_DEBUG 0
#endif // !CollisionTestSelfCommand_DEBUG

CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup* pCollidableGroup, CollisionDispatchBase* pCollisionDispatch)
	: _pCollidableGroup(pCollidableGroup),
	_pCollisionDispatch(pCollisionDispatch)
{}

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
	delete _pCollisionDispatch;
}

void CollisionTestSelfCommand::execute()
{
	testCollisionGroup(_pCollidableGroup);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Execute helpers
//-----------------------------------------------------------------------------------------------------------------------------
void CollisionTestSelfCommand::testCollisionGroup(CollidableGroup* pCollidableGroup) const
{
	const CollidableGroup::Collection& collection = pCollidableGroup->getColliderCollection();

	for (auto current = collection.begin(); current != collection.end(); current++)
	{
		for (auto afterCurrent = std::next(current); afterCurrent != collection.end(); afterCurrent++)
		{
			Collidable* pCollidable_1 = *current;
			Collidable* pCollidable_2 = *afterCurrent;
			testCollidablesBSphere(pCollidable_1, pCollidable_2);
		}
	}
}

void CollisionTestSelfCommand::testCollidablesBSphere(Collidable* pCollidable_1, Collidable* pCollidable_2) const
{
	const CollisionVolumeBSphere& BSphere_1 = pCollidable_1->getBSphere();
	const CollisionVolumeBSphere& BSphere_2 = pCollidable_2->getBSphere();

	// If collidables's BSphere_1 1 collides with collidable'2 BSphere_1 2 then..
	if (MathTools::Intersect(BSphere_1, BSphere_2))
	{
#if CollisionTestSelfCommand_DEBUG
		Visualizer::ShowCollisionVolume(BSphere_1, Colors::Red);
		Visualizer::ShowCollisionVolume(BSphere_2, Colors::Red);
#endif // CollisionTestSelfCommand_DEBUG

		testCollidablesCollisionVolume(pCollidable_1, pCollidable_2);
	}
	else
	{
#if CollisionTestSelfCommand_DEBUG
		Visualizer::ShowCollisionVolume(BSphere_1);
		Visualizer::ShowCollisionVolume(BSphere_2);
#endif // CollisionTestSelfCommand_DEBUG
	}
}

void CollisionTestSelfCommand::testCollidablesCollisionVolume(Collidable* pCollidable_1, Collidable* pCollidable_2) const
{
	const CollisionVolume& collisionVolume_1 = pCollidable_1->getCollisionVolume();
	const CollisionVolume& collisionVolume_2 = pCollidable_2->getCollisionVolume();

	// If collidables's collision volume 1 collides with collidables's collision volume 2 then..
	if (MathTools::Intersect(collisionVolume_1, collisionVolume_2))
	{
#if CollisionTestSelfCommand_DEBUG
		Visualizer::ShowCollisionVolume(collisionVolume_1, Colors::Red);
		Visualizer::ShowCollisionVolume(collisionVolume_2, Colors::Red);
#endif // CollisionTestSelfCommand_DEBUG

		_pCollisionDispatch->processCallBacks(pCollidable_1, pCollidable_2);
	}
	else
	{
#if CollisionTestSelfCommand_DEBUG
		Visualizer::ShowCollisionVolume(collisionVolume_1);
		Visualizer::ShowCollisionVolume(collisionVolume_2);
#endif // CollisionTestSelfCommand_DEBUG
	}
}