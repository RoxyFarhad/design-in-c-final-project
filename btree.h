#ifndef _BTREE_
#define _BTREE_

#include <iterator> 
#include <ostream> 
#include <iostream> 
#include <node.h> 

namespace btree
{
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

            Btree( int m ); /* default constructor */
            Btree( int, bool (*)(T, T), void (*)(T) ); /* constructor with defined type */
            /* currently missing copy constructor because not relevant */
            ~Btree( ); /* destructor */ 

            void clear() /* clears the tree */
            void insert(T); /* inserts a key into the tree */ 
            T remove(T); /* removes a key from tree */ 
            BNode<T> search(T); /* returns the node associated with key */

        /* ~~~~~~~~ METHODS ~~~~~~~~~~~ */

        public:
            /* 
            * default constructor 
            * creates a null root node + sets m
            */
            template <typename T>
            BTree<T>::BTree(int m) 
            {   
                root = NULL; 
                compare = nullptr; 
                printKey = nullptr; 
                m = m; 
            }

            template <typename T>
            BTree<T>::Btree( int t, bool (*compFunc)(T, T), void (*print)(T) )
            {
                m = t;
                compare = compFunc; 
                printKey = print; 
                root = nullptr; 
            }



    }   
}

#endif 