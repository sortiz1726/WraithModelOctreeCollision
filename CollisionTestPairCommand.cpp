#include "CollisionTestPairCommand.h"
#include "CollidableGroup.h"
#include "CollisionDispatch.h"
#include "Collidable.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "MathTools.h"
#include "Visualizer.h"
#include "Colors.h"

#ifndef CollisionTestPairCommand_DEBUG
#define CollisionTestPairCommand_DEBUG 0
#endif // !CollisionTestPairCommand_DEBUG

CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup* pCollidableGroup1, CollidableGroup* pCollidableGroup2, CollisionDispatchBase* pCollisionDispatch)
	: _pCollidableGroup_1(pCollidableGroup1),
	_pCollidableGroup_2(pCollidableGroup2),
	_pCollisionDispatch(pCollisionDispatch)
{}

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	delete _pCollisionDispatch;
}

void CollisionTestPairCommand::execute()
{
	testCollisionGroups(_pCollidableGroup_1, _pCollidableGroup_2);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Execute helpers
//-----------------------------------------------------------------------------------------------------------------------------

void CollisionTestPairCommand::testCollisionGroups(CollidableGroup* pCollidableGroup_1, CollidableGroup* pCollidableGroup_2) const
{
	if (pCollidableGroup_1->isEmpty() || pCollidableGroup_2->isEmpty()) return;

	const CollisionVolumeAABB& groupAABB_1 = pCollidableGroup_1->getGroupAABB();
	const CollisionVolumeAABB& groupAABB_2 = pCollidableGroup_2->getGroupAABB();

	// If group AABB 1 collides with group AABB 2 then...
	if (MathTools::Intersect(groupAABB_1, groupAABB_2))
	{
#if CollisionTestPairCommand_DEBUG
		Visualizer::ShowCollisionVolume(groupAABB_1, Colors::Red);
		Visualizer::ShowCollisionVolume(groupAABB_2, Colors::Red);
#endif // CollisionTestPairCommand_DEBUG

		const CollidableGroup::Collection& collection_1 = _pCollidableGroup_1->getColliderCollection();
		for (Collidable* pCollidable_1 : collection_1)
		{
			testCollidableAgainstCollisionGroup(pCollidable_1, pCollidableGroup_2);
		}
	}
	else
	{
#if CollisionTestPairCommand_DEBUG
		Visualizer::ShowCollisionVolume(groupAABB_1);
		Visualizer::ShowCollisionVolume(groupAABB_2);
#endif // CollisionTestPairCommand_DEBUG
	}
}

void CollisionTestPairCommand::testCollidableAgainstCollisionGroup(Collidable* pCollidable_1, CollidableGroup* pCollidableGroup_2) const
{
	const CollisionVolumeBSphere& BSphere_1 = pCollidable_1->getBSphere();
	const CollisionVolumeAABB& groupAABB_2 = pCollidableGroup_2->getGroupAABB();

	// If collidable's BSphere_1 1 collides with group AABB 2 then...
	if (MathTools::Intersect(BSphere_1, groupAABB_2))
	{
#if CollisionTestPairCommand_DEBUG
		Visualizer::ShowCollisionVolume(BSphere_1, Colors::Red);
		Visualizer::ShowCollisionVolume(groupAABB_2, Colors::Red);
#endif // CollisionTestPairCommand_DEBUG

		const CollidableGroup::Collection& collection_2 = _pCollidableGroup_2->getColliderCollection();
		for (Collidable* pCollidable_2 : collection_2)
		{
			testCollidablesBSphere(pCollidable_1, pCollidable_2);
		}
	}
	else
	{
#if CollisionTestPairCommand_DEBUG
		Visualizer::ShowCollisionVolume(BSphere_1);
		Visualizer::ShowCollisionVolume(groupAABB_2);
#endif // CollisionTestPairCommand_DEBUG
	}
}

void CollisionTestPairCommand::testCollidablesBSphere(Collidable* pCollidable_1, Collidable* pCollidable_2) const
{
	const CollisionVolumeBSphere& BSphere_1 = pCollidable_1->getBSphere();
	const CollisionVolumeBSphere& BSphere_2 = pCollidable_2->getBSphere();

	// If collidables's BSphere_1 1 collides with collidable'2 BSphere_1 2 then..
	if (MathTools::Intersect(BSphere_1, BSphere_2))
	{
#if CollisionTestPairCommand_DEBUG
		Visualizer::ShowCollisionVolume(BSphere_1, Colors::Red);
		Visualizer::ShowCollisionVolume(BSphere_2, Colors::Red);
#endif // CollisionTestPairCommand_DEBUG

		testCollidablesCollisionVolume(pCollidable_1, pCollidable_2);
	}
	else
	{
#if CollisionTestPairCommand_DEBUG
		Visualizer::ShowCollisionVolume(BSphere_1);
		Visualizer::ShowCollisionVolume(BSphere_2);
#endif // CollisionTestPairCommand_DEBUG
	}
}

void CollisionTestPairCommand::testCollidablesCollisionVolume(Collidable* pCollidable_1, Collidable* pCollidable_2) const
{
	const CollisionVolume& collisionVolume_1 = pCollidable_1->getCollisionVolume();
	const CollisionVolume& collisionVolume_2 = pCollidable_2->getCollisionVolume();

	// If collidables's collision volume 1 collides with collidables's collision volume 2 then..
	if (MathTools::Intersect(collisionVolume_1, collisionVolume_2))
	{
#if CollisionTestPairCommand_DEBUG
		Visualizer::ShowCollisionVolume(collisionVolume_1, Colors::Red);
		Visualizer::ShowCollisionVolume(collisionVolume_2, Colors::Red);
#endif // CollisionTestPairCommand_DEBUG

		_pCollisionDispatch->processCallBacks(pCollidable_1, pCollidable_2);
	}
	else
	{
#if CollisionTestPairCommand_DEBUG
		Visualizer::ShowCollisionVolume(collisionVolume_1, Colors::Green);
		Visualizer::ShowCollisionVolume(collisionVolume_2, Colors::Green);
#endif // CollisionTestPairCommand_DEBUG
	}
}