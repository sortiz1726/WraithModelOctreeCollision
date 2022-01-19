#ifndef _OctreeModelManager
#define _OctreeModelManager

#include <map>

class OctreeNode;
class OctreeBuilder;
class Model;

/**********************************************************************************************//**
 * <summary> Manager for Octree Models.
 * 			 For loading Octree Models and accessing them within Collidable when requesting the use
 *			 of Octree for collision volume.
 * 			 </summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/
class OctreeModelManager
{
private:
	typedef Model* MapKey;
	typedef std::map<MapKey, OctreeNode*> OctreeModelMap;
	typedef OctreeModelMap::iterator OctreeModelIterator;
	typedef OctreeModelMap::value_type OctreeModelMapValue;

private:
	static OctreeModelManager* pInstance;

	OctreeModelManager();
	OctreeModelManager(const OctreeModelManager&) = delete;
	OctreeModelManager& operator=(const OctreeModelManager&) = delete;
	OctreeModelManager(OctreeModelManager&&) = delete;
	OctreeModelManager& operator=(OctreeModelManager&&) = delete;
	~OctreeModelManager();

	// Getting Model Manager
	static OctreeModelManager& GetInstance();

	OctreeNode* privGetOctreeModel(Model*, int maxDepth);
	OctreeNode* tryToGetOctreeModel(Model*, int maxDepth);

	void clearMap();

public:
	static OctreeNode* GetOctreeModel(Model* pModel, int maxDepth)
	{
		return GetInstance().privGetOctreeModel(pModel, maxDepth);
	}

	// Termination
	static void Delete();

private:
	OctreeModelMap _octreeModelMap;
	OctreeBuilder* _pOctreeBuilder;

};
#endif // !_OctreeModelManager

//-----------------------------------------------------------------------------------------------------------------------------
// OctreeModelManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------