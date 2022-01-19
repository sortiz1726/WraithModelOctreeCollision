#ifndef _OctreeBuilder
#define _OctreeBuilder

#include <list>
#include <vector>

class OctreeNode;
class Model;
class Matrix;
class Vect;
class Triangle;
struct TriangleIndex;

/**********************************************************************************************//**
* <summary> Octree builder builds Octree Model (all the octree nodes)
*			 based on model and depth requested </summary>
*
* <remarks> Used only by OctreeManager. </remarks>
**************************************************************************************************/
class OctreeBuilder
{
	typedef std::vector<OctreeNode*> OctreeNodeCollection;
	typedef OctreeNodeCollection::iterator OctreeNodeIterator;

	typedef std::vector<Triangle> TriangleCollection;

public:
	OctreeBuilder() = default;
	OctreeBuilder(const OctreeBuilder&) = delete;
	OctreeBuilder& operator=(const OctreeBuilder&) = delete;
	OctreeBuilder(OctreeBuilder&&) = delete;
	OctreeBuilder& operator=(OctreeBuilder&&) = delete;
	~OctreeBuilder() = default;

	OctreeNode* buildOctree(Model* pModel, int depth);

private:
	int maxNumberOfLeafNodes(const int depth) const;

	void buildNode(OctreeNode*& pNode, const Vect& minVertex, const Vect& maxVertex, int depth);
	Matrix transformOffset(const Vect& minVertex, const Vect& maxVertex, int index) const;
	Vect computeOffset(const int index) const;

	void filterNodes(Model*);
	TriangleCollection getModelTriangles(Model*) const;
	Triangle createTriangle(const TriangleIndex&, const Vect* const vects) const;

	void validateNode(OctreeNode* pNode);

private:
	OctreeNodeCollection _leafNodeHolder;
};
#endif // !_OctreeBuilder

//-----------------------------------------------------------------------------------------------------------------------------
// OctreeBuilder Comment Template
//-----------------------------------------------------------------------------------------------------------------------------