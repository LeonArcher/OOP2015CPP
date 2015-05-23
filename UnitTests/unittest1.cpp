#include "stdafx.h"
#include "CppUnitTest.h"

#include "../OOP2015CPP/XList.hpp"

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

	};
}