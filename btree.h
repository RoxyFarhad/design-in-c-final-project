#ifndef BTREE_H
#define BTREE_H

#include <sys/types.h>
#include <iterator>
#include <iostream>
#include <ostream> 
#include <string> 

namespace btree 
{

    template< typename Key, typename Data >
    class BTree 
    {

        // typedefs for easier reference later
        typedef Btree<Key, Data> btree_type; 
        
        typedef Iterator<Key, Data> iterator; 
        typedef typename iterator::const_iteartor const_iterator;
        typedef std::reverse_iterator< const_iterator> const_reverse_iterator; 
        typedef std::reverse_iterator< iterator > iterator; 

        /*
            public methods
        */
        public:
            Btree( ); // constructor
            Btree( const btree_type &x ); // copy constructor 
            ~Btree(); // destructor 

            // iterator method headers
            iterator begin(); 
            const_iterator begin() const; 
            iterator end(); 
            const_iterator end() const; 
            reverse_iterator rbegin(); 
            const_reverse_iterator rbegin() const; 
            reverse_iterator rend(); 
            const_reverse_iterator rend() const; 

            // functionality 
            void clear();
            void assign( const btree_type &x );

        // ~~~~~ METHODS ~~~~~

        // default constructor
        template< typename Key, typename Data >
        BTree< Key, Data>::Btree(): root(nullptr) {}
        
        // copy constructor
        template< typename Key, typename Data > 
        BTree< Key, Data >::Btree(const btree_type &x)
        { 
            // create a method to copy the tree using an iterator
        }

        // destructor 
        template<typename Key, typename Data > 
        Btree< Key, Data >::~Btree()
        {
            // create a method to delete the tree from memory
        }

        template<typename Key, typename Data > 
        typename Btree<Key, Data>::iterator
        Btree<Key, Data>::begin()
        {
            // returns the leftmost node
        }

        template<typename Key, typename Data > 
        typename Btree<Key, Data>::const_iterator
        Btree<Key, Data>::begin()
        {
            // returns the (const) leftmost node
        }

        

    }

}

#endif