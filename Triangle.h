#ifndef _Triangle
#define _Triangle

#include "Vect.h"

/**********************************************************************************************//**
 * <summary> Triangle class holding 3 vertices that define a triangle. Used for intersection
 *			 testing against OBB in filtering nodes in Octree Builder. </summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/
class Triangle
{
public:
	Triangle() = default;
	Triangle(const Triangle&) = default;
	Triangle& operator=(const Triangle&) = default;
	Triangle(Triangle&&) = default;
	Triangle& operator=(Triangle&&) = default;
	~Triangle() = default;

	Triangle(const Vect& vertex0, const Vect& vertex1, const Vect& vertex2);
	Triangle(Vect&& vertex0, Vect&& vertex1, Vect&& vertex2);

	Vect computeNormal() const;

	void setVertex0(const Vect& vertex0);
	void setVertex1(const Vect& vertex1);
	void setVertex2(const Vect& vertex2);

	const Vect& getVertex0() const;
	const Vect& getVertex1() const;
	const Vect& getVertex2() const;

	Vect getEdge01() const;
	Vect getEdge12() const;
	Vect getEdge20() const;

	Triangle& operator*=(const Matrix&);
	Triangle& operator-=(const Vect&);
	Triangle& operator+=(const Vect&);

private:
	Vect _vertex0;
	Vect _vertex1;
	Vect _vertex2;

};
#endif // !_Triangle

//-----------------------------------------------------------------------------------------------------------------------------
// Triangle Comment Template
//-----------------------------------------------------------------------------------------------------------------------------