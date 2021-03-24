#ifndef _BTREE_
#define _BTREE_

#include <iterator> 
#include <ostream> 
#include <iostream> 
#include "node.hpp"

template<typename T>
class BTree
{
    using btree_type = BTree<T>;
    
    private:
        BNode<T> root; 
        int m; /* pre-defined degree of tree */ 
        bool (*compare)(T, T); /* comparative function for tree (as templated) */ 
        void (*printKey)(T); /* Function used to print items in the tree. */
    
    public: 

        BTree( int m ); /* default constructor */
        BTree( int, bool (*)(T, T), void (*)(T) ); /* constructor with defined type */
        /* currently missing copy constructor because not relevant */
        ~BTree( ); /* destructor */ 

        void clear(); /* clears the tree */
        void insert(T); /* inserts a key into the tree */ 
        T remove(T); /* removes a key from tree */ 
        //BNode<T> search(T); /* returns the node associated with key */

    /* ~~~~~~~~ METHODS ~~~~~~~~~~~ */

        /* 
        * default constructor 
        * creates a null root node + sets m
        */

};


#endif 