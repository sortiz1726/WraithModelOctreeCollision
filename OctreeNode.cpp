#include "OctreeNode.h"
#include <cassert>

OctreeNode::OctreeNode()
	: _pParent(nullptr),
	_children(),
	_isValid(false),
	_size(0)
{
	for (auto& pChild : _children)
	{
		pChild = nullptr;
	}
}

OctreeNode::OctreeNode(const OctreeNode& octreeNode)
	: OctreeNode()
{
	if (&octreeNode == this) return;

	copyOBBData(octreeNode);
	_isValid = octreeNode._isValid;
	_size = octreeNode._size;

	if (octreeNode.isLeafNode()) return;

	for (int i = 0; i < 8; i++)
	{
		OctreeNode*& pMyChild = _children[i];
		const OctreeNode& otherChild = *octreeNode._children[i];

		if (otherChild._isValid)
		{
			pMyChild = new OctreeNode(otherChild);
			pMyChild->_pParent = this;
		}
	}
}

OctreeNode& OctreeNode::operator=(const OctreeNode& octreeNode)
{
	if (&octreeNode == this) return *this;

	copyOBBData(octreeNode);
	_isValid = octreeNode._isValid;
	_size = octreeNode._size;

	if (octreeNode.isLeafNode()) return *this;

	for (int i = 0; i < 8; i++)
	{
		OctreeNode*& pMyChild = _children[i];
		const OctreeNode& otherChild = *octreeNode._children[i];

		if (otherChild._isValid)
		{
			pMyChild = new OctreeNode(otherChild);
			pMyChild->_pParent = this;
		}
	}

	return *this;
}

const OctreeNode* OctreeNode::getChildAt(int index) const
{
	assert(index >= 0 && index < OctreeNode::NUMBER_OF_CHILDREN);
	return _children[index];
}

OctreeNode* OctreeNode::getChildAt(int index)
{
	assert(index >= 0 && index < OctreeNode::NUMBER_OF_CHILDREN);
	return _children[index];
}

OctreeNode*& OctreeNode::getChildReferenceAt(int index)
{
	return _children[index];
}

const OctreeNode* const* OctreeNode::getChildren() const
{
	return _children;
}

const CollisionVolumeOBB& OctreeNode::getOBB() const
{
	return _obb;
}

CollisionVolumeOBB& OctreeNode::getOBB()
{
	return _obb;
}

void OctreeNode::setParent(OctreeNode* pParent)
{
	_pParent = pParent;
}

OctreeNode* OctreeNode::getParent() const
{
	return _pParent;
}

void OctreeNode::offsetSize(int offset)
{
	_size += offset;
}

void OctreeNode::setSize(int size)
{
	_size = size;
}

int OctreeNode::getSize() const
{
	return _size;
}

bool OctreeNode::getIsValid() const
{
	return _isValid;
}

void OctreeNode::recalculateSize()
{
	setSize(0);
	for (OctreeNode* pChild : _children)
	{
		if (pChild != nullptr && pChild->getIsValid())
		{
			pChild->recalculateSize();
			offsetSize(pChild->getSize() + 1);
		}
	}
}

void OctreeNode::setIsValid(bool isValid)
{
	_isValid = isValid;
}

void OctreeNode::copyOBBData(const OctreeNode& octreeNode)
{
	_obb.setMinMaxLocalVertex(octreeNode._obb.getMinLocalVertex(), octreeNode._obb.getMaxLocalVertex());
}

OctreeNode::~OctreeNode()
{
	for (auto& pChild : _children)
	{
		delete pChild;
	}
}

bool OctreeNode::isLeafNode() const
{
	for (auto& pChild : _children)
	{
		if (pChild != nullptr) return false;
	}
	return true;
}