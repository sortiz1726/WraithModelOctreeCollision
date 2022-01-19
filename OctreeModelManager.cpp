#include "OctreeModelManager.h"
#include "OctreeNode.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "Triangle.h"
#include "GpuVertTypes.h"
#include "MathTools.h"
#include "OctreeBuilder.h"
#include <cassert>

OctreeModelManager* OctreeModelManager::pInstance = nullptr;

OctreeModelManager& OctreeModelManager::GetInstance()
{
	if (OctreeModelManager::pInstance == nullptr)
	{
		OctreeModelManager::pInstance = new OctreeModelManager();
	}
	assert(OctreeModelManager::pInstance != nullptr);
	return *OctreeModelManager::pInstance;
}

OctreeModelManager::OctreeModelManager()
	: _pOctreeBuilder(new OctreeBuilder())
{}

OctreeNode* OctreeModelManager::privGetOctreeModel(Model* pModel, int maxDepth)
{
	OctreeNode* pRoot = tryToGetOctreeModel(pModel, maxDepth);
	OctreeNode* pRoot_Copy = new OctreeNode(*pRoot);
	return pRoot_Copy;
}

OctreeNode* OctreeModelManager::tryToGetOctreeModel(Model* pModel, int maxDepth)
{
	OctreeModelIterator octreeNodeIt = _octreeModelMap.find(pModel);

	if (octreeNodeIt == _octreeModelMap.end())
	{
		OctreeNode* pNode = _pOctreeBuilder->buildOctree(pModel, maxDepth);
		octreeNodeIt = _octreeModelMap.insert(std::make_pair(pModel, pNode)).first;
	}

	return octreeNodeIt->second;
}

void OctreeModelManager::Delete()
{
	delete OctreeModelManager::pInstance;
	OctreeModelManager::pInstance = nullptr;
}

OctreeModelManager::~OctreeModelManager()
{
	delete _pOctreeBuilder;
	clearMap();
}

void OctreeModelManager::clearMap()
{
	for (OctreeModelMapValue& pOctreeNode : _octreeModelMap)
	{
		delete pOctreeNode.second;
	}
	_octreeModelMap.clear();
}
