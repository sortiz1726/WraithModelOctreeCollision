#include "OctreeTools.h"
#include "OctreeNode.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Octree-Single Volume Intersection
//-----------------------------------------------------------------------------------------------------------------------------
void OctreeTools::AddChildNodesToTest(const OctreeNode* const* pChildren, NodeStack& nodeStack)
{
	for (int i = 0; i < OctreeNode::NUMBER_OF_CHILDREN; i++)
	{
		const OctreeNode* pChild = pChildren[i];
		if (pChild != nullptr)
		{
			nodeStack.push(pChild);
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Octree-Octree Intersections
//-----------------------------------------------------------------------------------------------------------------------------
bool OctreeTools::AreBothLeafNodes(const OctreeNode* pNode_1, const OctreeNode* pNode_2)
{
	return pNode_1->isLeafNode() && pNode_2->isLeafNode();
}

bool OctreeTools::ShouldDescendFirstNode(const OctreeNode* pNode_1, const OctreeNode* pNode_2)
{
	// Basically choosing the larger size when possible 
	// - if second node is a leaf node we choose we return true so we traverse down the first node
	// - if first node contains more nodes than the second than we return true so travers the first node 
	return pNode_2->isLeafNode() || (!pNode_1->isLeafNode() && pNode_1->getSize() >= pNode_2->getSize());
}

void OctreeTools::AddChildNodesToTest(const OctreeNode* const* pChildren, const OctreeNode* pNode, NodePairStack& nodePairStack)
{
	for (int i = 0; i < OctreeNode::NUMBER_OF_CHILDREN; i++)
	{
		const OctreeNode* pChild = pChildren[i];
		if (pChild != nullptr)
		{
			nodePairStack.push(std::make_pair(pChild, pNode));
		}
	}
}
