#ifndef _BTREE_
#define _BTREE_

#include <iterator> 
#include <ostream> 
#include <iostream> 
#include "node.cpp"


template<typename T>
class BTree
{
    using btree_type = BTree<T>;
    
    private:
        BNode<T> *root; 
        int m; /* pre-defined degree of tree */ 
        int (*compare)(T, T); /* comparative function for tree (as templated) */ 
        void (*printKey)(T); /* Function used to print items in the tree. */
        int index; 
        int elemCount; 
    
    public: 

        BTree( int m ); /* default constructor */
        BTree( int, int (*)(T, T), void (*)(T) ); /* constructor with defined type */
        /* currently missing copy constructor because not relevant */
        ~BTree( ); /* destructor */ 

        void clear(); /* clears the tree */
        int insert(T); /* inserts a key into the tree */ 
        T remove(T); /* removes a key from tree */ 
        int size(); /* returns the size of the tree */
        bool empty(); /* returns bool if the tree is empty or not */

        BNodeKey<T>* search(T); /* returns the node associated with key */
        void traverse(); /* traverses the tree */
        bool isHeightBalanced(); /* return height of tree */

        
    private:
        void splitChild(BNode<T> *x, int i); 
        void traverse(BNode<T> *curr); /* traverses the tree */
        int height(BNode<T> *curr); /* calculate height of tree from root */
        bool isHeightBalanced(BNode<T> *curr); /* return height of tree */
};



#endif 