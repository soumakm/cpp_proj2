

#include <algorithm>
using namespace std;

template <typename Object>
class List
{
  private:    
    // The basic doubly linked list node.
    // Nested inside of List, can be public
    // because the Node is itself private
    struct Node
    {
        Object  data;
        Node   *prev;
        Node   *next;

        Node( const Object & d = Object{ }, Node * p = nullptr, Node * n = nullptr )
          : data{ d }, prev{ p }, next{ n } { }
        
        Node( Object && d, Node * p = nullptr, Node * n = nullptr )
          : data{ std::move( d ) }, prev{ p }, next{ n } { }
    };

  public:
    //nested const_iterator class
    class const_iterator
    {
      public:
  
        // Public constructor for const_iterator.
        const_iterator( ) : current{ nullptr }
          { }

        // Return the object stored at the current position.
        // For const_iterator, this is an accessor with a
        // const reference return type.
        const Object & operator* ( ) const
          { return retrieve( ); }
        
        const_iterator & operator++ ( )
        {
            current = current->next;
            return *this;
        }

        // increment/decrement operators
        const_iterator operator++ ( int )
        {
            const_iterator old = *this;
            ++( *this );
            return old;
        }

        const_iterator & operator-- ( )
        {
            current = current->prev;
            return *this;
        }

        const_iterator operator-- ( int )
        {
            const_iterator old = *this;
            --( *this );
            return old;
        }
        
        // comparison operators    
        bool operator== ( const const_iterator & rhs ) const
          { return current == rhs.current; }

        bool operator!= ( const const_iterator & rhs ) const
          { return !( *this == rhs ); }

      protected:
        Node *current;

        // Protected helper in const_iterator that returns the object
        // stored at the current position. Can be called by all
        // three versions of operator* without any type conversions.
        Object & retrieve( ) const
          { return current->data; }

        // Protected constructor for const_iterator.
        // Expects a pointer that represents the current position.
        const_iterator( Node *p ) :  current{ p }
          { }
        
        friend class List<Object>;
    };

    // nested iterator class
    class iterator : public const_iterator
    {
      public:

        // Public constructor for iterator.
        // Calls the base-class constructor.
        // Must be provided because the private constructor
        // is written; otherwise zero-parameter constructor
        // would be disabled.
        iterator( )
          { }

        Object & operator* ( )
          { return const_iterator::retrieve( ); }

        // Return the object stored at the current position.
        // For iterator, there is an accessor with a
        // const reference return type and a mutator with
        // a reference return type. The accessor is shown first.
        const Object & operator* ( ) const
          { return const_iterator::operator*( ); }
        
        // increment/decrement operators
        iterator & operator++ ( )
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++ ( int )
        {
            iterator old = *this;
            ++( *this );
            return old;
        }

        iterator & operator-- ( )
        {
            this->current = this->current->prev;
            return *this;
        }

        iterator operator-- ( int )
        {
            iterator old = *this;
            --( *this );
            return old;
        }

      protected:
        // Protected constructor for iterator.
        // Expects the current position.
        iterator( Node *p ) : const_iterator{ p }
          { }

        friend class List<Object>;
    };

  public:
    // default zero parameter constructor
    List( )
      { init( ); }
    // copy constructor  
    List( const List & rhs )
    {
        init( );
        for( auto & x : rhs )
            push_back( x );
    }
    // move constructor
    List( List && rhs )
      : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    // num elements with value of val, check
    explicit List(int num, const T& val = T{})
    {
        init( );
        for (int i=0; i< num; i++)
            push_back( val );
    }
    // constructs with elements [start, end), check
    List(const_iterator start, const_iterator end)
    {
        init( );
        while(start != end)
        {
            push_back( *start);
            ++start;
        }    
    }
    // destructor
    ~List( )
    {
        clear( );
        delete head;
        delete tail;
    }

    // copy assignment operator
    List & operator= ( const List & rhs )
    {
        List copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    // move assignment operator
    List & operator= ( List && rhs )
    {    
        std::swap( theSize, rhs.theSize );
        std::swap( head, rhs.head );
        std::swap( tail, rhs.tail );
        
        return *this;
    }
    
    // member functions
    // Return number of elements currently in the list.
    int size( ) const
      { return theSize; }

    // Return true if the list is empty, false otherwise.
    bool empty( ) const
      { return size( ) == 0; }

    void clear( )
    {
        while( !empty( ) )
            pop_front( );
    }
    // reverse the order of the elements, check
    void reverse()
    {

    }
    // front, back, push_front, push_back, pop_front, and pop_back
    // are the basic double-ended queue operations.
    Object & front( )
      { return *begin( ); }

    const Object & front( ) const
      { return *begin( ); }

    Object & back( )
      { return *--end( ); }

    const Object & back( ) const
      { return *--end( ); }

    void push_front( const Object & x )
      { insert( begin( ), x ); }

    void push_back( const Object & x )
      { insert( end( ), x ); }

    void push_front( Object && x )
      { insert( begin( ), std::move( x ) ); }

    void push_back( Object && x )
      { insert( end( ), std::move( x ) ); }

    void pop_front( )
      { erase( begin( ) ); }

    void pop_back( )
      { erase( --end( ) ); }
    // remove all elements with value = val, check
    void remove(const Object & val)
    {
        iterator itr = begin( );
        while(itr != end( ))
        {
            if(*itr == val)
                itr = erase(itr);
            else
                ++itr;
        }

    }  
    // print out all elements. ofc is deliminitor, check
    void print(std::ostream & os, char ofc = ' ') const  
    {
        const_iterator itr = begin();
        while(*itr != end())
        {
            out << *itr << ofc << endl;
            ++itr;
        }
    }
    // Return iterator representing beginning of list.
    // Mutator version is first, then accessor version.
    iterator begin( )
      { return iterator( head->next ); }

    const_iterator begin( ) const
      { return const_iterator( head->next ); }

    // Return iterator representing endmarker of list.
    // Mutator version is first, then accessor version.
    iterator end( )
      { return iterator( tail ); }

    const_iterator end( ) const
      { return const_iterator( tail ); }

    // Insert x before itr.
    iterator insert( iterator itr, const Object & x )
    {
        Node *p = itr.current;
        ++theSize;
        return iterator( p->prev = p->prev->next = new Node{ x, p->prev, p } );
    }

    // Insert x before itr.
    iterator insert( iterator itr, Object && x )
    {
        Node *p = itr.current;
        ++theSize;
        return iterator( p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } );
    }
    
    // Erase item at itr.
    iterator erase( iterator itr )
    {
        Node *p = itr.current;
        iterator retVal( p->next );
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        --theSize;

        return retVal;
    }

    iterator erase( iterator from, iterator to )
    {
        for( iterator itr = from; itr != to; )
            itr = erase( itr );

        return to;
    }

  private:
    int   theSize;
    Node *head;
    Node *tail;

    void init( )
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }

};
// overloading comparison operators, check
    template <typename Object>
        bool operator==(const List<Object> & lhs, const List<Object> & rhs)
        {
            List<Object>::iterator itr_lhs = lhs.begin();
            List<Object>::iterator itr_lhs = lhs.begin();
            if(lhs.size() == rhs.size())
            {
                if(*itr_lhs != *itr_rhs)
                    return false;
                while(itr_lhs != itr_lhs.end())
                {
                    if(*itr_lhs != *itr_rhs)
                        return false;
                    ++itr_lhs;
                    ++itr_rhs;
                }    
                return true;
            } else
                return false;
        }
    //check
    template <typename Object>
        bool operator!=(const List<Object> & lhs, const List<Object> &rhs)
        {
            return !operator==(lhs, rhs);

        }
    // overloading output operator, check
    template <typename Object>
        std::ostream & operator<<(std::ostream &os, const List<Object> &l) 
        {
            l.print(os, ', ');

        }  

