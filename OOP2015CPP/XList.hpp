#pragma once

#include <cassert>

template< typename T >
struct Element
{
	Element * next;
	Element * prev;
	T val;
};


// итератор списка - для удобного перебора всех элементов списка

template < class T >
class XList_iterator
{
public:

	XList_iterator( Element< T > * elem ) : m_node_ptr( elem )
	{
	}

	T & operator * ()
	{
		return m_node_ptr->val;
	}

	void operator ++ ()
	{
		assert( m_node_ptr != nullptr );
		m_node_ptr = m_node_ptr->next;
	}

	XList_iterator operator ++ ( int )
	{
		XList_iterator iter( *this );
		++( *this );
		return iter;
	}

	void operator -- ()
	{
		assert( m_node_ptr != nullptr );
		m_node_ptr = m_node_ptr->prev;
	}

	XList_iterator operator -- ( int )
	{
		XList_iterator iter( *this );
		--( *this );
		return iter;
	}

	XList_iterator operator+( int offset )
    {
		XList_iterator iter( *this );
		for( int i = 0; i < offset; ++i )
			++iter;
        return iter; 
    }

	bool operator == ( XList_iterator const& i )
	{
		return m_node_ptr == i.m_node_ptr;
	}

	bool operator != ( XList_iterator const& i )
	{
		return !( *this == i );
	}

private:

	Element< T > * m_node_ptr;
};



template< typename T >
class XList
{
public:

	XList_iterator< T > Begin() const { return XList_iterator< T >( m_head ); }
	XList_iterator< T > End() const { return XList_iterator< T >( m_end ); }

	void PushBack( const T & elem )
	{
		Element< T > * tmp = new Element< T >();

		tmp->val = elem;
		tmp->prev = m_end;
		tmp->next = nullptr;

		if( m_end != nullptr )
			m_end->next = tmp;
		else
			m_head = tmp;
		
		m_end = tmp;
	}

	void PushFront( const T & elem )
	{
		Element< T > * tmp = new Element< T >();

		tmp->val = elem;
		tmp->prev = nullptr;
		tmp->next = m_head;

		if( m_head != nullptr )
			m_head->prev = tmp;
		else
			m_end = tmp;
		
		m_head = tmp;
	}

	void PopBack()
	{
		assert( m_end != nullptr ); // для скорости работы не проверяем список на пустоту в release-версии
		Element< T > * tmp = m_end->prev;
		if( tmp != nullptr )
			tmp->next = nullptr;
		else
			m_head = nullptr;

		delete m_end;
		m_end = tmp;
	}

	void PopFront()
	{
		assert( m_end != nullptr );
		Element< T > * tmp = m_head->next;
		if(tmp != nullptr)
			tmp->prev = nullptr;
		else
			m_end = nullptr;

		delete m_head;
		m_head = tmp;
	}

	bool IsEmpty()
	{
		return ( m_head == nullptr && m_end == nullptr );
	}

	int GetLength()
	{
		if( this->IsEmpty() )
			return 0;

		int length = 1;

		for( Element< T > * tmp = m_head; tmp != m_end; tmp = tmp->next )
		{
			++length;
		}

		return length;
	}

	void Clear()
	{
		Element< T > * tmp;
		while( m_head != m_end )
		{
			tmp = m_head->next;
			delete m_head;
			m_head = tmp;
		}
		delete m_head;
		
		m_head = nullptr;
		m_end = nullptr;
	}

	T & GetFirst() // неконстантная передача, чтобы была возможность изменять содержимое (но лучше для получения элементов использовать итераторы на начало/конец)
	{
		assert( m_head != nullptr );
		return m_head->val;
	}

	T & GetLast()
	{
		assert( m_end != nullptr );
		return m_end->val;
	}

	XList()
	{
		m_head = nullptr;
		m_end = nullptr;
	}

	XList( XList & other )
	{
		m_head = nullptr;
		m_end = nullptr;

		for( XList_iterator< T > iter = other.Begin(); iter != other.End(); ++iter )
			this->PushBack( *iter );

		this->PushBack( *( other.End() ) );
	}

	~XList() { Clear(); }

private:

	Element< T > * m_head;
	Element< T > * m_end;
};