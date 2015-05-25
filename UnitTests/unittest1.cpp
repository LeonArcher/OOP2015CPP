#include "stdafx.h"
#include "CppUnitTest.h"

#include "../OOP2015CPP/XList.hpp"
#include "../OOP2015CPP/Factory.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(XListTest)
		{
			XList<int> test_list;

			Assert::AreEqual( test_list.IsEmpty(), true );
			
			for( int i = 0; i < 100; ++i ) {
				test_list.PushBack(i);
			}

			Assert::AreEqual( test_list.IsEmpty(), false );

			XList_iterator<int> iter = test_list.Begin();
			for( int i = 0; i < 100; ++i ) {
				Assert::AreEqual( *iter, i );
				++iter;
			}

			Assert::AreEqual( test_list.GetFirst(), 0 );
			Assert::AreEqual( test_list.GetLast(), 99 );
			Assert::AreEqual( test_list.GetLength(), 100 );

			for( int i = 0; i < 10; ++i ) {
				test_list.PopFront();
				test_list.PopBack();
			}

			iter = test_list.Begin();
			for( int i = 10; i < 90; ++i ) {
				Assert::AreEqual( *iter, i );
				++iter;
			}

			Assert::AreEqual( test_list.GetFirst(), 10 );
			Assert::AreEqual( test_list.GetLast(), 89 );
			Assert::AreEqual( test_list.GetLength(), 80 );

			test_list.Clear();
			
			Assert::AreEqual( test_list.GetLength(), 0 );
			Assert::AreEqual( test_list.IsEmpty(), true );

			for( int i = 0; i < 10; ++i ) {
				test_list.PushFront( i + 10 );
				test_list.PushBack( i + 5 );
			}

			Assert::AreEqual( test_list.IsEmpty(), false );

			iter = test_list.Begin();
			for( int i = 19; i > 9; --i ) {
				Assert::AreEqual( *iter, i );
				++iter;
			}

			iter = test_list.End();
			for( int i = 14; i > 4; --i ) {
				Assert::AreEqual( *iter, i );
				--iter;
			}

			Assert::AreEqual( test_list.GetFirst(), 19 );
			Assert::AreEqual( test_list.GetLast(), 14 );
			Assert::AreEqual( test_list.GetLength(), 20 );

			XList<int> test_list2( test_list );

			Assert::AreEqual( test_list2.IsEmpty(), false );

			iter = test_list2.Begin();
			for( int i = 19; i > 9; --i ) {
				Assert::AreEqual( *iter, i );
				++iter;
			}

			iter = test_list2.End();
			for( int i = 14; i > 4; --i ) {
				Assert::AreEqual( *iter, i );
				--iter;
			}

			Assert::AreEqual( test_list2.GetFirst(), 19 );
			Assert::AreEqual( test_list2.GetLast(), 14 );
			Assert::AreEqual( test_list2.GetLength(), 20 );

			test_list.Clear();
			
			Assert::AreEqual( test_list.GetLength(), 0 );
			Assert::AreEqual( test_list.IsEmpty(), true );

			test_list2.Clear();

			Assert::AreEqual( test_list2.GetLength(), 0 );
			Assert::AreEqual( test_list2.IsEmpty(), true );
		}

		TEST_METHOD(FactoryCreateDeleteTest)
		{
			// создаем одну точку, проверяем все счетчики до и после

			Assert::AreEqual( Shape::GetCount(), 0 );

			Factory shape_factory;
			
			shape_factory.Add< Point >( "Point" );
			shape_factory.Add< Circle >( "Circle" );
			shape_factory.Add< Rect >( "Rect" );
			shape_factory.Add< Polyline >( "Polyline" );
			shape_factory.Add< Polygon >( "Polygon" );

			Shape * ptr = shape_factory.CreateRandom( "Point" );

			Assert::AreEqual( Shape::GetCount(), 1 );
			Assert::AreEqual( shape_factory.GetCounter( "Point" ), 1 );

			delete ptr;

			Assert::AreEqual( Shape::GetCount(), 0 );

			// создаем массив случайных окружностей, проверяем счетчики

			XList< Shape * > arr;

			arr.PushBack( shape_factory.CreateRandom( "Circle" ) );
			arr.PushBack( shape_factory.CreateRandom( "Circle" ) );
			arr.PushBack( shape_factory.CreateRandom( "Circle" ) );
			arr.PushBack( shape_factory.CreateRandom( "Circle" ) );

			Assert::AreEqual( Shape::GetCount(), 8 ); // 4 фигуры - окружности, 4 фигуры - центры окружностей
			Assert::AreEqual( shape_factory.GetCounter( "Circle" ), 4 );

			for( int i = 0; i < 4; ++i ) {
				delete *( arr.Begin() );
				arr.PopFront();
			}

			Assert::AreEqual( arr.IsEmpty(), true );
			Assert::AreEqual( Shape::GetCount(), 0 );

			// создаем ломаную из случайного набора точек, проверяем счетчики

			ptr = shape_factory.CreateRandom( "Polyline" );

			Assert::AreEqual( shape_factory.GetCounter( "Polyline" ), 1 );

			delete ptr;

			Assert::AreEqual( Shape::GetCount(), 0 );
		}

	};
}