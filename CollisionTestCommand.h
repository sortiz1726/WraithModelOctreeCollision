#ifndef _CollisionTestCommand
#define _CollisionTestCommand

class CollisionTestCommand
{
public:
	CollisionTestCommand() = default;
	CollisionTestCommand(const CollisionTestCommand&) = default;
	CollisionTestCommand& operator=(const CollisionTestCommand&) = default;
	CollisionTestCommand(CollisionTestCommand&&) = default;
	CollisionTestCommand& operator=(CollisionTestCommand&&) = default;
	virtual ~CollisionTestCommand() = default;

	virtual void execute() = 0;
};
#endif // !_CollisionTestCommand

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionTestCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------