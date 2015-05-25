#include <map>

#include "Shapes.hpp"
#include "Factory.hpp"

int main()
{
	Factory shape_factory;
	
	shape_factory.Add< Point >( "Point" );
	shape_factory.Add< Circle >( "Circle" );
	shape_factory.Add< Rect >( "Rect" );
	shape_factory.Add< Polyline >( "Polyline" );
	shape_factory.Add< Polygon >( "Polygon" );

	XList< Shape * > figures;

	std::mt19937 generator( std::chrono::system_clock::now().time_since_epoch().count() ); // для случайного выбора типа фигуры
	std::uniform_int_distribution< int > distr( 0, 4 );

	std::map< int, std::string > figure_type;
	figure_type[ 0 ] = "Point";
	figure_type[ 1 ] = "Circle";
	figure_type[ 2 ] = "Rect";
	figure_type[ 3 ] = "Polyline";
	figure_type[ 4 ] = "Polygon";

	for( int i = 0; i < 20; ++i )
	{
		figures.PushBack( shape_factory.CreateRandom( figure_type[ distr( generator ) ] ) );
	}

	std::cout << "Total figures created (including subfigures): " << Shape::GetCount() << '\n';

	for( int i = 0; i < 5; ++i )
	{
		std::cout << "Created figures via factory '" << figure_type[ i ] << "': " << shape_factory.GetCounter( figure_type[ i ] ) << '\n';
	}

	std::cout << "\nDetailed information about each figure:\n";

	for( XList_iterator< Shape * > iter = figures.Begin(); iter != figures.End(); ++iter )
	{
		( ( Printable * )( *iter ) )->Print();
		std::cout << '\n';
	}

	// очистка списка фигур
	for( XList_iterator< Shape * > iter = figures.Begin(); iter != figures.End(); ++iter )
	{
		delete ( *iter );
	}
	delete ( *figures.End() );
	figures.Clear();

	std::cout << "Total figures count after erase (including subfigures): " << Shape::GetCount() << '\n';

	return 0;
}