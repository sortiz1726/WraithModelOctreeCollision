#ifndef _CollisionManager
#define _CollisionManager

#include <vector>
#include <list>

#include "CollisionDispatch.h"
#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"
#include "CollisionTestTerrainCommand.h"

class CollidableGroup;
class CollisionTestCommand;
class Collidable;

class CollisionManager
{
public:
	typedef int CollisionTypeID;
	static const CollisionTypeID ID_UNDEFINED = -1;
private:
	typedef std::vector<CollidableGroup*> GroupCollection;
	typedef std::list<CollisionTestCommand*> StorageList;

public:
	CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
	CollisionManager(CollisionManager&&) = delete;
	CollisionManager& operator=(CollisionManager&&) = delete;
	~CollisionManager();

	/**********************************************************************************************//**
	 * <summary> Sets collision pair test for the current scene</summary>
	 *
	 * <typeparam name="UserClass1"> Type of the user class 1.</typeparam>
	 * <typeparam name="UserClass2"> Type of the user class 2.</typeparam>
	 **************************************************************************************************/
	template<class UserClass1, class UserClass2>
	void setCollisionPair()
	{
		CollidableGroup* collidablegroup1 = _collidableGroups.at(getCollisionTypeID<UserClass1>());
		CollidableGroup* collidablegroup2 = _collidableGroups.at(getCollisionTypeID<UserClass2>());
	
		CollisionDispatch<UserClass1, UserClass2>* pDispatch = new CollisionDispatch<UserClass1, UserClass2>();
	
		_collisionTestCommands.push_back(new CollisionTestPairCommand(collidablegroup1, collidablegroup2, pDispatch));
	}

	/**********************************************************************************************//**
	 * <summary> Sets collision self test for current scene</summary>
	 *
	 * <typeparam name="UserClass"> Type of the user class.</typeparam>
	 **************************************************************************************************/
	template<class UserClass>
	void setCollisionSelf()
	{
		CollidableGroup* collidablegroup = _collidableGroups.at(getCollisionTypeID<UserClass>());
	
		CollisionDispatch<UserClass, UserClass>* pDispatch = new CollisionDispatch<UserClass, UserClass>();
	
		_collisionTestCommands.push_back(new CollisionTestSelfCommand(collidablegroup, pDispatch));
	}

	/**********************************************************************************************//**
	* <summary> Sets collision terrain test for current scene</summary>
	*
	* <typeparam name="UserClass"> Type of the user class.</typeparam>
	**************************************************************************************************/
	template<class UserClass>
	void setCollisionTerrain()
	{
		CollidableGroup* collidablegroup = _collidableGroups.at(getCollisionTypeID<UserClass>());

		_collisionTestCommands.push_back(new CollisionTestTerrainCommand(collidablegroup));
	}

	/**********************************************************************************************//**
	 * <summary> Gets collision type identifier.</summary>
	 *
	 * <typeparam name="UserClass"> Type of the user class.</typeparam>
	 *
	 * <returns> The collision type identifier.</returns>
	 **************************************************************************************************/
	template<class UserClass>
	CollisionTypeID getCollisionTypeID()
	{
		static CollisionTypeID collisionID = CollisionManager::NextCollisionIDNumber++;

		setGroupForTypeID(collisionID);

		//Trace::out("Collision ID = %d\n", collisionID);
		return collisionID;
	}

	/**********************************************************************************************//**
	 * <summary> Gets collidable group.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="id"> The identifier.</param>
	 *
	 * <returns> the collidable group.</returns>
	 **************************************************************************************************/
	CollidableGroup* getCollidableGroup(CollisionTypeID id) const;

	/**********************************************************************************************//**
	 * <summary> Process the registered collisions.</summary>
	 *
	 * <remarks> Called only by the current Scene in Scene::Update(). </remarks>
	 **************************************************************************************************/
	void processCollisions();

private:	
	// Setting Collidable Group
	void setGroupForTypeID(CollisionTypeID);
	// ---> Set Collidable Group helper
	void checkAndAdjustForIndex(CollisionTypeID);
	bool isValidIndex(CollisionTypeID) const;
	void resizeToFit(CollisionTypeID);

	// Deinitializaton
	void deinitializeCollisionGroups();
	void deinitializeCollisionTestCommands();

private:
	static CollisionTypeID NextCollisionIDNumber;

	GroupCollection _collidableGroups;
	StorageList _collisionTestCommands;
	
	static const size_t MAX_GROUP_SIZE;
};
#endif // !_CollisionManager

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------