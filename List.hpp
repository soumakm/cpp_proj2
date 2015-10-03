

         template <typename T>
        // default zero parameter constructor
        List<T>::const_iterator::const_iterator() : current{ nullptr }
          { }

        // operator*() to return element  
        template <typename T>  
        const T & List<T>::const_iterator::operator* ( ) const
          { return retrieve( ); }
        
        // increment/decrement operators
          template <typename T>
        typename List<T>::const_iterator & List<T>::const_iterator::operator++ ( )
        {
            current = current->next;
            return *this;
        }
        template <typename T>
        typename List<T>::const_iterator List<T>::const_iterator::operator++ ( int )
        {
            const_iterator old = *this;
            ++( *this );
            return old;
        }
        template <typename T>
        typename List<T>::const_iterator & List<T>::const_iterator::operator-- ( )
        {
            current = current->prev;
            return *this;
        }
        template <typename T>
        typename List<T>::const_iterator List<T>::const_iterator::operator-- ( int )
        {
            const_iterator old = *this;
            --( *this );
            return old;
        }
        
        // comparison operators    
        template <typename T>
        bool List<T>::const_iterator::operator== ( const const_iterator & rhs ) const
          { return current == rhs.current; }
        template <typename T>  
        bool List<T>::const_iterator::operator!= ( const const_iterator & rhs ) const
          { return !( *this == rhs ); }

        // retrieve the element refers to
        template <typename T>
        T & List<T>::const_iterator::retrieve( ) const
          { return current->data; }

        // protected constructor
        template <typename T>
        List<T>::const_iterator::const_iterator( Node *p ) :  current{ p }
          { }


    // nested iterator class
        template <typename T>
        List<T>::iterator::iterator()
          { }
        template <typename T>
        T & List<T>::iterator::operator* ( )
          { return const_iterator::retrieve( ); }

        template <typename T>  
        const T & List<T>::iterator::operator* ( ) const
          { return const_iterator::operator*( ); }
        
        // increment/decrement operators
        template <typename T>  
        typename List<T>::iterator & List<T>::iterator::operator++ ( )
        {
            this->current = this->current->next;
            return *this;
        }
        template <typename T>
        typename List<T>::iterator List<T>::iterator::operator++ ( int )
        {
            iterator old = *this;
            ++( *this );
            return old;
        }
        template <typename T>
        typename List<T>::iterator & List<T>::iterator::operator-- ( )
        {
            this->current = this->current->prev;
            return *this;
        }
        template <typename T>
        typename List<T>::iterator List<T>::iterator::operator-- ( int )
        {
            iterator old = *this;
            --( *this );
            return old;
        }

        template <typename T>
        List<T>::iterator::iterator( Node *p ) : const_iterator{ p }
          { }

     // default zero parameter constructor
    template <typename T>      
    List<T>::List( )
      { init( ); }
    // copy constructor
    template <typename T>  
    List<T>::List( const List<T> & rhs )
    {
        init( );
        for( auto & x : rhs )
            push_back( x );
    }
    // move constructor
    template <typename T>
    List<T>::List( List<T> && rhs )
      : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    // num elements with value of val, check
    template <typename T>
    List<T>::List(int num, const T& val)
    {
        init( );
        for (int i=0; i< num; i++)
            push_back( val );
    }
    // constructs with elements [start, end), check
    template <typename T>
    List<T>::List(const_iterator start, const_iterator end)
    {
        init( );
        while(start != end)
        {
            push_back( *start);
            ++start;
        }    
    }
    // destructor
    template <typename T>
    List<T>::~List( )
    {
        clear( );
        delete head;
        delete tail;
    }

    // copy assignment operator
    template <typename T>
    const typename cop4530::List<T> & List<T>::operator= ( const List<T> & rhs )
    {
      //  List<T> copy = rhs;
      //  List<T> lhs;
        if (&rhs == this)
            return *this;
      //  std::swap( *this, copy );
        Node *tmp = rhs.head;
        clear();
        for(int i =0; i< rhs.theSize;i++)
        {
            push_back(new Node(*tmp));
            tmp = tmp->next;
        }

        return *this;
    }
    
    // move assignment operator
    template <typename T>
    typename cop4530::List<T> & List<T>::operator= ( List<T> && rhs )
    {    
      //  std::swap( theSize, rhs.theSize );
      //  std::swap( head, rhs.head );
      //  std::swap( tail, rhs.tail );
        theSize = rhs.theSize;
        head = rhs.head;
        tail = rhs.tail;
        
        return *this;
    }
    
    // member functions
    // Return number of elements currently in the list.
    template <typename T>
    int List<T>::size( ) const
      { return theSize; }

    // Return true if the list is empty, false otherwise.
    template <typename T>  
    bool List<T>::empty( ) const
      { return size( ) == 0; }

    template <typename T>  
    void List<T>::clear( )
    {
        while( !empty( ) )
            pop_front( );
    }
    // reverse the order of the elements, check
    template <typename T>
    void List<T>::reverse()
    {
     /*   Node *next;
        Node *prev = nullptr;
        Node *tmp = head;
        while (tmp != nullptr)
        {
            next  = tmp->next;  
            tmp->next = prev;   
            prev = tmp;
            tmp = next;
        }
        head = prev;*/
    }
    // front, back, push_front, push_back, pop_front, and pop_back
    // are the basic double-ended queue operations.
    template <typename T>
    T & List<T>::front( )
      { return *begin( ); }
    template <typename T>  
    const T & List<T>::front( ) const
      { return *begin( ); }
    template <typename T>  
    T & List<T>::back( )
      { return *--end( ); }
    template <typename T>  
    const T & List<T>::back( ) const
      { return *--end( ); }
    template <typename T>
    void List<T>::push_front( const T & x )
      { insert( begin( ), x ); }
    template <typename T>
    void List<T>::push_back( const T & x )
      { insert( end( ), x ); }
    template <typename T>
    void List<T>::push_front( T && x )
      { insert( begin( ), std::move( x ) ); }
    template <typename T>
    void List<T>::push_back( T && x )
      { insert( end(), std::move( x ) ); }
    template <typename T>
    void List<T>::pop_front()
      { erase( begin() ); }
    template <typename T>
    void List<T>::pop_back()
      { erase( --end() ); }
    // remove all elements with value = val, check
    template <typename T>  
    void List<T>::remove(const T & val)
    {
        iterator itr = begin();
        while(itr != end( ))
        {
            if(*itr == val)
                itr = erase(itr);
            else
                ++itr;
        }

    }  
    // print out all elements. ofc is deliminitor, check
    template <typename T>
    void List<T>::print(std::ostream & os, char ofc ) const  
    {
        const_iterator itr = begin();
        while(itr != end())
        {
            os << *itr << ofc << std::endl;
            ++itr;
        }
    }
    // Return iterator representing beginning of list.
    // Mutator version is first, then accessor version.
    template <typename T>
    typename List<T>::iterator List<T>::begin()
      { return iterator( head->next ); }
    template <typename T>
    typename List<T>::const_iterator List<T>::begin() const
      { return const_iterator( head->next ); }

    // Return iterator representing endmarker of list.
    // Mutator version is first, then accessor version.
    template <typename T>  
    typename List<T>::iterator List<T>::end()
      { return iterator( tail ); }
    template <typename T>
    typename List<T>::const_iterator List<T>::end() const
      { return const_iterator( tail ); }

    // Insert x before itr.
    template <typename T>
    typename List<T>::iterator List<T>::insert( iterator itr, const T & x )
    {
        Node *p = itr.current;
        ++theSize;
        return iterator( p->prev = p->prev->next = new Node{ x, p->prev, p } );
    }

    // Insert x before itr.
    template <typename T>
    typename List<T>::iterator List<T>::insert( iterator itr, T && x )
    {
        Node *p = itr.current;
        ++theSize;
        return iterator( p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } );
    }
    
    // Erase item at itr.
    template <typename T>
    typename List<T>::iterator List<T>::erase( iterator itr )
    {
        Node *p = itr.current;
        iterator retVal( p->next );
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        --theSize;

        return retVal;
    }
    template <typename T>
    typename List<T>::iterator List<T>::erase( iterator from, iterator to )
    {
        for( iterator itr = from; itr != to; )
            itr = erase( itr );

        return to;
    }
    template <typename T>
    void List<T>::init( )
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }

// overloading comparison operators, check
    template <typename T>
        bool operator==(const List<T> & lhs, const List<T> & rhs)
        {
            typename List<T>::const_iterator itr_lhs = lhs.begin();
            typename List<T>::const_iterator itr_rhs = rhs.begin();
            if(lhs.size() == rhs.size())
            {
                if(*itr_lhs != *itr_rhs)
                    return false;
                while(itr_lhs != lhs.end())
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
    template <typename T>
        bool operator!=(const List<T> & lhs, const List<T> &rhs)
        {
            return !operator==(lhs, rhs);

        }
    // overloading output operator, check
    template <typename T>
        std::ostream & operator<<(std::ostream &os, const List<T> &l) 
        {
            l.print(os, ',');
            return os;
        }  
