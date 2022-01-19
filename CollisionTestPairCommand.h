#ifndef _CollisionTestPairCommand
#define _CollisionTestPairCommand

#include "CollisionTestCommand.h"

class CollidableGroup;
class CollisionDispatchBase;
class Collidable;

class CollisionTestPairCommand : public CollisionTestCommand
{
public:
	CollisionTestPairCommand() = delete;
	CollisionTestPairCommand(const CollisionTestPairCommand&) = default;
	CollisionTestPairCommand& operator=(const CollisionTestPairCommand&) = default;
	CollisionTestPairCommand(CollisionTestPairCommand&&) = default;
	CollisionTestPairCommand& operator=(CollisionTestPairCommand&&) = default;
	~CollisionTestPairCommand();

	CollisionTestPairCommand(CollidableGroup*, CollidableGroup*, CollisionDispatchBase*);

	// Inherited via CollisionTestCommand
	virtual void execute() override;

private:
	// Execute helpers
	void testCollisionGroups(CollidableGroup*, CollidableGroup*) const;
	void testCollidableAgainstCollisionGroup(Collidable*, CollidableGroup*) const;
	void testCollidablesBSphere(Collidable*, Collidable*) const;
	void testCollidablesCollisionVolume(Collidable*, Collidable*) const;

private:
	CollidableGroup* _pCollidableGroup_1;
	CollidableGroup* _pCollidableGroup_2;
	CollisionDispatchBase* _pCollisionDispatch;

};
#endif // !_CollisionTestPairCommand

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionTestPairCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------