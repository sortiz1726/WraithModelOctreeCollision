#ifndef _CollisionVolumeOctree
#define _CollisionVolumeOctree

#include <vector>
#include "CollisionVolume.h"
#include "CollisionVolumeOBB.h"
#include "Matrix.h"

class OctreeNode;

class CollisionVolumeOctree : public CollisionVolume
{
	typedef std::vector<OctreeNode*> OctreeNodeCollection;

public:
	CollisionVolumeOctree() = delete;
	CollisionVolumeOctree(const CollisionVolumeOctree&) = default;
	CollisionVolumeOctree& operator=(const CollisionVolumeOctree&) = default;
	CollisionVolumeOctree(CollisionVolumeOctree&&) = default;
	CollisionVolumeOctree& operator=(CollisionVolumeOctree&&) = default;
	~CollisionVolumeOctree();

	CollisionVolumeOctree(Model* pModel, int maxDepth);

	// Inherited via CollisionVolume
	virtual void computeData(Model* pModel, const Matrix& worldMatrix) override;

	virtual bool intersectAccept(const CollisionVolume& collisionVolume) const override;
	virtual bool intersectVisitor(const CollisionVolumeBSphere& collisionBSphere) const override;
	virtual bool intersectVisitor(const CollisionVolumeAABB& AABB) const override;
	virtual bool intersectVisitor(const CollisionVolumeOBB& OBB) const override;
	virtual bool intersectVisitor(const CollisionVolumeOctree&) const override;

	virtual void debugDraw(const Vect& color, int depth) const override;
	void debugDraw(int depth, const Vect& color) const;

	const OctreeNode* getRoot() const;

	virtual int getMaxDepth() const override;

private:
	OctreeNodeCollection getAllNodes() const;
	void addNodes(OctreeNode* pNode, OctreeNodeCollection& nodes) const;

	void drawAt(int depth, const Vect& color, const OctreeNode* pNode) const;

private:
	OctreeNode* _pRoot;
	int _maxDepth;
};
#endif // !_CollisionVolumeOctree

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionVolumeOctree Comment Template
//-----------------------------------------------------------------------------------------------------------------------------