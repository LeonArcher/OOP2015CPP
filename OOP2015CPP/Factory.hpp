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
        FactoryMapIterator it = m_factory.find( id );
        if ( it == m_factory.end() ) {
            m_factory[ id ] = new ShapeCreator<C>();
			m_counter[ id ] = 0;
		}
    }

    Shape * create_random( const std::string & id )
    {
        FactoryMapIterator it = m_factory.find( id );
        if ( it != m_factory.end() ) {
			++m_counter[ id ];
            return it->second->create_random();
		}
        return 0;
    }

	Factory() {}
	~Factory() {}

protected:

    typedef std::map< std::string, ShapeCreatorInterface * > FactoryMap;
	typedef std::map< std::string, ShapeCreatorInterface * >::iterator FactoryMapIterator;
    FactoryMap m_factory;

	std::map< std::string, int > m_counter; // счетчик созданных фабрикой объектов
};