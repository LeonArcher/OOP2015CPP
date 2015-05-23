#pragma once

#include <iostream>
#include <string>

#include "Base.h"
#include "XList.hpp"

#define M_PI 3.14159265358979323846


class Shape : virtual public Named
{
public:

	static int GetCount() { return m_count; }

protected:

	static int m_count;
};

int Shape::m_count = 0;


class Point : public Shape, public Printable
{
public:

	Point( float x = 0, float y = 0 ) : m_x( x ), m_y( y ) { ++m_count; }

	virtual void Print( std::ostream & where = std::cout ) const
	{
		where << "Point '" << m_name << "'\nX-coordinate: " << m_x << "\nY-coordinate: " << m_y << '\n';
	}

	float m_x;
	float m_y;
};


float Distance( const Point & p1, const Point & p2 )
{
	return sqrt( ( p1.m_x - p2.m_x ) * ( p1.m_x - p2.m_x ) + ( p1.m_y - p2.m_y ) * ( p1.m_y - p2.m_y ) );
}


class Circle : public Shape, public Printable
{
public:

	Circle( Point & center = Point(), float radius = 1.0f ) : m_center( center ), m_radius( radius ) { ++m_count; }

	virtual void Print( std::ostream & where = std::cout ) const
	{
		where << "Circle '" << m_name << "'\nCenter: (" << m_center.m_x << "; " << m_center.m_y << ")\n";
		where << "Radius: " << m_radius << '\n';
		where << "Square: " << M_PI * m_radius * m_radius << '\n';
	}

private:

	Point m_center;
	float m_radius;
};


class Rect : public Shape, public Printable
{
public:

	Rect( Point & point1 = Point( 0.0f, 0.0f ), Point & point2 = Point( 1.0f, 1.0f ) ) : m_p1( point1 ), m_p2( point2 ) { ++m_count; }

	virtual void Print( std::ostream & where = std::cout ) const
	{
		where << "Rectangle '" << m_name << "'\nCoordinates: ";
		where << '(' << m_p1.m_x << "; " << m_p1.m_y << ") ";
		where << '(' << m_p2.m_x << "; " << m_p1.m_y << ") ";
		where << '(' << m_p2.m_x << "; " << m_p2.m_y << ") ";
		where << '(' << m_p1.m_x << "; " << m_p2.m_y << ")\n";
		where << "Square: " << Distance( Point( m_p1.m_x, m_p2.m_y ), m_p2 ) * Distance( Point( m_p1.m_x, m_p2.m_y ), m_p1 ) << '\n';
	}

private:

	Point m_p1;
	Point m_p2;
};


class Polyline : public Shape, public Printable
{
public:

	Polyline() { ++m_count; };
	Polyline( XList<Point> & coordinates ) : m_coords( coordinates ) { ++m_count; }

	virtual void Print( std::ostream & where = std::cout ) const
	{
		where << "Polyline '" << m_name << "'\nCoordinates: ";
	}

	void AddPoint( const Point & _point ) {	m_coords.PushBack( _point ); }

private:

	XList<Point> m_coords;
};


class Polygon : public Shape, public Printable
{
public:

	Polygon() { ++m_count; };
	Polygon( XList<Point> & coordinates ) : m_coords( coordinates ) { ++m_count; }

	virtual void Print( std::ostream & where = std::cout ) const
	{
	}

	void AddPoint( const Point & _point ) {	m_coords.PushBack( _point ); }

private:

	XList<Point> m_coords;
};