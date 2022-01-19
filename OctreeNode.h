#ifndef _OctreeNode
#define _OctreeNode

#include "CollisionVolumeOBB.h"

/**********************************************************************************************//**
 * <summary> Octree Node contains a Collision OBB along with 8 child Octree Nodes and a parent.
 *			 Part of the CollisionVolumeOctree which hold a pointer to a root Octree Node. </summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/
class OctreeNode
{
public:
	static const int NUMBER_OF_CHILDREN = 8;

public:
	OctreeNode();
	OctreeNode(const OctreeNode&);
	OctreeNode& operator=(const OctreeNode&);
	OctreeNode(OctreeNode&&) = delete;
	OctreeNode& operator=(OctreeNode&&) = delete;
	~OctreeNode();

	bool isLeafNode() const;

	const OctreeNode* getChildAt(int index) const;
	OctreeNode* getChildAt(int index);
	OctreeNode*& getChildReferenceAt(int index);
	const OctreeNode* const* getChildren() const;

	const CollisionVolumeOBB& getOBB() const;
	CollisionVolumeOBB& getOBB();

	void setParent(OctreeNode* pParent);
	OctreeNode* getParent() const;

	void offsetSize(int offset);
	void setSize(int size);
	int getSize() const;

	void setIsValid(bool isValid);
	bool getIsValid() const;

	void recalculateSize();

private:
	OctreeNode* _pParent;
	CollisionVolumeOBB _obb;
	OctreeNode* _children[NUMBER_OF_CHILDREN];
	int _size;

	// Used a quick way to choose which nodes are 
	// valid for rendering (used for protyping purposes)
	bool _isValid;


	void copyOBBData(const OctreeNode& octreeNode);
};
#endif // !_OctreeNode

//-----------------------------------------------------------------------------------------------------------------------------
// OctreeNode Comment Template
//-----------------------------------------------------------------------------------------------------------------------------