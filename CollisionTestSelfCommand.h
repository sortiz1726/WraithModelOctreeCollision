#ifndef _CollisionTestSelfCommand
#define _CollisionTestSelfCommand

#include "CollisionTestCommand.h"

class CollidableGroup;
class CollisionDispatchBase;
class Collidable;

class CollisionTestSelfCommand : public CollisionTestCommand
{
public:
	CollisionTestSelfCommand() = delete;
	CollisionTestSelfCommand(const CollisionTestSelfCommand&) = default;
	CollisionTestSelfCommand& operator=(const CollisionTestSelfCommand&) = default;
	CollisionTestSelfCommand(CollisionTestSelfCommand&&) = default;
	CollisionTestSelfCommand& operator=(CollisionTestSelfCommand&&) = default;
	// Is it a base class? Should it be virtual?
	~CollisionTestSelfCommand();

	CollisionTestSelfCommand(CollidableGroup*, CollisionDispatchBase*);

	// Inherited via CollisionTestCommand
	virtual void execute() override;

private:
	// Execute helpers
	void testCollisionGroup(CollidableGroup*) const;
	void testCollidablesBSphere(Collidable*, Collidable*) const;
	void testCollidablesCollisionVolume(Collidable*, Collidable*) const;

private:
	CollidableGroup* _pCollidableGroup;
	CollisionDispatchBase* _pCollisionDispatch;

};
#endif // !_CollisionTestSelfCommand

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionTestSelfCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------