#ifndef _OctreeTools
#define _OctreeTools

#include <stack>
#include <queue>

class OctreeNode;

/**********************************************************************************************//**
// namespace: OctreeTools
//
// summary:	A places where are tools to be used by for Octree testing.
 **************************************************************************************************/
namespace OctreeTools
{
	typedef std::stack<const OctreeNode*> NodeStack;

	void AddChildNodesToTest(const OctreeNode* const* pChildren, NodeStack& nodeStack);

	// Octree-Octree Intersection
	typedef std::pair<const OctreeNode*, const OctreeNode*> NodePair;
	typedef std::stack<NodePair> NodePairStack;
	typedef std::queue<NodePair> NodePairQueue;

	bool AreBothLeafNodes(const OctreeNode* pNode_1, const OctreeNode* pNode_2);
	bool ShouldDescendFirstNode(const OctreeNode* pNode_1, const OctreeNode* pNode_2);

	void AddChildNodesToTest(const OctreeNode* const* pChildren, const OctreeNode* pNode, NodePairStack& nodePairStack);

};
#endif // !_OctreeTools

//-----------------------------------------------------------------------------------------------------------------------------
// OctreeTools Comment Template
//-----------------------------------------------------------------------------------------------------------------------------