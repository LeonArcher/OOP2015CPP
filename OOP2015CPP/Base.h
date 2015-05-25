#pragma once

#include <string>
#include <iostream>

class Named
{
public:
	
	Named(std::string name = "Noname") : m_name( name ) {}
	virtual ~Named() {}

protected:

	std::string m_name;

};

class Printable : virtual public Named
{
public:

	virtual void Print( std::ostream & where = std::cout ) const = 0;

	friend std::ostream & operator << ( std::ostream & stream, const Printable & object )
	{
		object.Print( stream );
		return stream;
	}
};