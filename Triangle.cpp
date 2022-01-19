#include "Triangle.h"
#include "Matrix.h"

Triangle::Triangle(const Vect& vertex0, const Vect& vertex1, const Vect& vertex2)
	: _vertex0(vertex0), _vertex1(vertex1), _vertex2(vertex2)
{}

Triangle::Triangle(Vect && vertex0, Vect && vertex1, Vect && vertex2)
	: _vertex0(vertex0), _vertex1(vertex1), _vertex2(vertex2)
{}

Vect Triangle::computeNormal() const
{
	Vect normal = getEdge01().cross(getEdge12());
	normal[w] = 0.0f;
	return normal;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Vertices
//-----------------------------------------------------------------------------------------------------------------------------
void Triangle::setVertex0(const Vect& vertex0)
{
	_vertex0 = vertex0;
}

void Triangle::setVertex1(const Vect& vertex1)
{
	_vertex1 = vertex1;
}

void Triangle::setVertex2(const Vect& vertex2)
{
	_vertex2 = vertex2;
}

const Vect& Triangle::getVertex0() const
{
	return _vertex0;
}

const Vect& Triangle::getVertex1() const
{
	return _vertex1;
}

const Vect& Triangle::getVertex2() const
{
	return _vertex2;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Edges
//-----------------------------------------------------------------------------------------------------------------------------
Vect Triangle::getEdge01() const
{
	return _vertex1 - _vertex0;
}

Vect Triangle::getEdge12() const
{
	return _vertex2 - _vertex1;
}

Vect Triangle::getEdge20() const
{
	return _vertex0 - _vertex2;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Vector and Matrix computation
//-----------------------------------------------------------------------------------------------------------------------------

Triangle& Triangle::operator*=(const Matrix& matrix)
{
	this->_vertex0 *= matrix;
	this->_vertex1 *= matrix;
	this->_vertex2 *= matrix;

	return *this;
}

Triangle& Triangle::operator-=(const Vect& vect)
{
	return Triangle::operator+=(-vect);
}

Triangle& Triangle::operator+=(const Vect& vect)
{
	this->_vertex0 += vect;
	this->_vertex1 += vect;
	this->_vertex2 += vect;

	return *this;
}
