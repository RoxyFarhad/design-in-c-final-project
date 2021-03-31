#ifndef _BTREE_
#define _BTREE_

#include <iterator> 
#include <ostream> 
#include <iostream> 
#include "node.cpp"

//TODO : Build iterator to search / print items for checking methods

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
    
    public: 

        BTree( int m ); /* default constructor */
        BTree( int, int (*)(T, T), void (*)(T) ); /* constructor with defined type */
        /* currently missing copy constructor because not relevant */
        ~BTree( ); /* destructor */ 

        void clear(); /* clears the tree */
        void insert(T); /* inserts a key into the tree */ 
        void remove(T); /* removes a key from tree */ 
        BNodeKey<T>* search(T); /* returns the key associated with node */
        void traverse(); /* traverses the tree */
        std::vector<BNodeKey<T>*> searchRange(T lowKey, T highKey); /* finds values in a range */
        BNode<T>* getNode(T); /* returns the node associated with the key */
    private:
        void splitChild(BNode<T> *x, int i); 
        void traverse(BNode<T> *curr); /* traverses the tree */
        void deleteNode(BNode<T> *node, T key);


};



#endif 