#pragma once

#include <iostream>
#include <string>

#include <random>
#include <chrono>

#include "Base.h"
#include "XList.hpp"

#define M_PI 3.14159265358979323846


class Shape : virtual public Named
{
public:

	Shape() { ++m_count; }
	Shape( Shape & other ) { ++m_count; }
	virtual ~Shape() { --m_count; }

	static int GetCount() { return m_count; }

	// этой функции тут быть не должно, но без нее вызывается функция RandomizeParameters, несмотря на обращение к Print через Printable*
	virtual void Print( std::ostream & where = std::cout ) const = 0;

	virtual void RandomizeParameters() = 0; // инициализируем все параметры случайными числами (допустимыми величинами)

protected:

	static int m_count;

	static std::mt19937 m_generator; // ГПСЧ Вихрь Мерсенна
};

int Shape::m_count = 0;
std::mt19937 Shape::m_generator = std::mt19937( std::chrono::system_clock::now().time_since_epoch().count() ); // начальная рандомизация генератора


class Point : public Shape, public Printable
{
public:

	Point( float x = 0, float y = 0 ) : m_x( x ), m_y( y ) {}

	virtual void Print( std::ostream & where = std::cout ) const
	{
		where << "Point '" << m_name << "'\nX-coordinate: " << m_x << "\nY-coordinate: " << m_y << '\n';
	}

	virtual void RandomizeParameters()
	{
		std::uniform_real_distribution< float > distr( -1e10, 1e10 ); // интервал равномерного распределения координат точки
		m_x = distr( m_generator );
		m_y = distr( m_generator );
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

	Circle( Point & center = Point(), float radius = 1.0f ) : m_center( center ), m_radius( radius ) {}

	virtual void RandomizeParameters()
	{
		std::uniform_real_distribution< float > distr( 1e-10, 1e10 ); // интервал равномерного распределения радиуса круга
		m_radius = distr( m_generator );

		m_center.RandomizeParameters();
	}

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

	Rect( Point & point1 = Point( 0.0f, 0.0f ), Point & point2 = Point( 1.0f, 1.0f ) ) : m_p1( point1 ), m_p2( point2 ) {}

	virtual void Print( std::ostream & where = std::cout ) const
	{
		where << "Rectangle '" << m_name << "'\nCoordinates: ";
		where << '(' << m_p1.m_x << "; " << m_p1.m_y << ") ";
		where << '(' << m_p2.m_x << "; " << m_p1.m_y << ") ";
		where << '(' << m_p2.m_x << "; " << m_p2.m_y << ") ";
		where << '(' << m_p1.m_x << "; " << m_p2.m_y << ")\n";
		where << "Square: " << Distance( Point( m_p1.m_x, m_p2.m_y ), m_p2 ) * Distance( Point( m_p1.m_x, m_p2.m_y ), m_p1 ) << '\n';
	}

	virtual void RandomizeParameters()
	{
		m_p1.RandomizeParameters();
		m_p2.RandomizeParameters();

		// исключаем расположение точек на одной прямой, параллельной одной из осей координат
		while( m_p1.m_x == m_p2.m_x || m_p1.m_y == m_p2.m_y )
			m_p2.RandomizeParameters();
	}

private:

	Point m_p1;
	Point m_p2;
};


class Polyline : public Shape, public Printable
{
public:

	Polyline() {}
	Polyline( XList<Point> & coordinates ) : m_coords( coordinates ) {}

	virtual void Print( std::ostream & where = std::cout ) const
	{
		where << "Polyline '" << m_name << "'\nCoordinates: ";
		
		float length = 0;

		for( XList_iterator<Point> iter = m_coords.Begin(); iter != m_coords.End(); ++iter )
		{
			where << '(' << ( *iter ).m_x << "; " << ( *iter ).m_y << ") ";
			length += Distance( *iter, *( iter + 1 ) );
		}
		where << '(' << ( *m_coords.End() ).m_x << "; " << ( *m_coords.End() ).m_y << ")\n";

		where << "Length: " << length << '\n';
	}

	virtual void RandomizeParameters()
	{
		m_coords.Clear();

		std::uniform_int_distribution< int > distr( 1, 100 );
		int segment_count = distr( m_generator );
		Point p;

		p.RandomizeParameters();
		this->AddPoint( p );

		for( int i = 0; i < segment_count; ++i )
		{
			p.RandomizeParameters();

			while( p.m_x == ( *m_coords.End() ).m_x && p.m_y == ( *m_coords.End() ).m_y )
				p.RandomizeParameters();

			this->AddPoint( p );
		}
	}

	void AddPoint( const Point & _point ) {	m_coords.PushBack( _point ); }

private:

	XList<Point> m_coords;
};


class Polygon : public Shape, public Printable
{
public:

	Polygon() {}
	Polygon( XList<Point> & coordinates ) : m_coords( coordinates ) {}

	virtual void Print( std::ostream & where = std::cout ) const
	{
		where << "Polygon '" << m_name << "'\nCoordinates: ";
		
		float perimeter = 0;

		for( XList_iterator<Point> iter = m_coords.Begin(); iter != m_coords.End(); ++iter )
		{
			where << '(' << ( *iter ).m_x << "; " << ( *iter ).m_y << ") ";
			perimeter += Distance( *iter, *( iter + 1 ) );
		}
		where << '(' << ( *m_coords.End() ).m_x << "; " << ( *m_coords.End() ).m_y << ")\n";

		where << "Perimeter: " << perimeter << '\n';
	}

	virtual void RandomizeParameters()
	{
		m_coords.Clear();

		std::uniform_int_distribution< int > distr( 3, 100 );
		int edge_count = distr( m_generator );
		Point p0, p;

		p0.RandomizeParameters();
		this->AddPoint( p0 );

		// при заполнении массива вершин многоугольника возможность пересечений не учитывается
		for( int i = 1; i < edge_count; ++i )
		{
			p.RandomizeParameters();

			while( p.m_x == ( *m_coords.End() ).m_x && p.m_y == ( *m_coords.End() ).m_y )
				p.RandomizeParameters();

			this->AddPoint( p );
		}
	}

	void AddPoint( const Point & _point ) {	m_coords.PushBack( _point ); }

private:

	XList<Point> m_coords;
};