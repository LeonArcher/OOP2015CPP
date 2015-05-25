#pragma once

#include <map>

#include "Shapes.hpp"


// паттерн "‘абрика объектов" (упрощенный вариант)

class ShapeCreatorInterface
{
public:

    virtual Shape * CreateRandom() const = 0;
};



template <class C>
class ShapeCreator : public ShapeCreatorInterface
{
public:

    virtual Shape * CreateRandom() const
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
		Add< Point >( "Point" );
		Add< Circle >( "Circle" );
		Add< Rect >( "Rect" );
		Add< Polyline >( "Polyline" );
		Add< Polygon >( "Polygon" );
	}

	template < class C >
    void Add( const std::string & id )
    {
        FactoryMapIterator it = m_factory.find( id );
        if ( it == m_factory.end() ) {
            m_factory[ id ] = new ShapeCreator<C>();
			m_counter[ id ] = 0;
		}
    }

    Shape * CreateRandom( const std::string & id )
    {
        FactoryMapIterator it = m_factory.find( id );
        if ( it != m_factory.end() ) {
			++m_counter[ id ];
            return it->second->CreateRandom();
		}
        return 0;
    }

	int GetCounter( const std::string & id ) { return m_counter[ id ]; }

	Factory() {}
	~Factory() {}

protected:

    typedef std::map< std::string, ShapeCreatorInterface * > FactoryMap;
	typedef std::map< std::string, ShapeCreatorInterface * >::iterator FactoryMapIterator;
    FactoryMap m_factory;

	std::map< std::string, int > m_counter; // счетчик созданных фабрикой объектов
};