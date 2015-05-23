#pragma once

#include <map>

#include "Shapes.hpp"


// паттерн "‘абрика объектов" (упрощенный вариант)

class ShapeCreatorInterface
{
public:

    virtual Shape * create_random() const = 0;
};



template <class C>
class ShapeCreator : public ShapeCreatorInterface
{
public:

    virtual Shape * create_random() const
	{
		Shape * new_shape = new C();
		new_shape->RandomizeParameters();
		return new_shape;
	}
};



class Factory
{
public:

	// функци€ дл€ тестового задани€; по-хорошему, конкретные типы объектов добавл€ютс€ в фабрику извне
	void Init()
	{
		add< Point >( "Point" );
		add< Circle >( "Circle" );
		add< Rect >( "Rect" );
		add< Polyline >( "Polyline" );
		add< Polygon >( "Polygon" );
	}

	template < class C >
    void add( const std::string & id )
    {
        typename FactoryMap::iterator it = _factory.find( id );
        if ( it == _factory.end() )
            _factory[ id ] = new ShapeCreator<C>();
    }

    Shape * create_random( const std::string & id )
    {
        typename FactoryMap::iterator it = _factory.find( id );
        if ( it != _factory.end() )
            return it->second->create_random();
        return 0;
    }

	Factory() {}
    ~Factory();

protected:

    typedef std::map< std::string, ShapeCreatorInterface * > FactoryMap;
    FactoryMap _factory;
};