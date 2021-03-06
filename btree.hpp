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

        bool isHeightBalanced(); /* return height of tree */
        BNodeKey<T>* search(T); /* returns the node associated with key */
        void traverse(); /* traverses the tree */
        std::vector<BNodeKey<T>*> searchRange(T lowKey, T highKey); /* finds values in a range */
        void deletiona(T k);
        void deletion(BNode<T> *curr, T k); 
        int findIndex(BNode<T> *curr, T key);
        BNode<T>* getNode(T key);

    
    private:

        void splitChild(BNode<T> *x, int i); 
        void traverse(BNode<T> *curr); /* traverses the tree */
        void removeFromLeaf(BNode<T> *curr, int idx);
        void removeFromNonLeaf(BNode<T> *curr, int idx);
        T getPredecessor(BNode<T> *curr, int idx);
        T getSuccessor(BNode<T> *curr, int idx);
        void fill(BNode<T> *curr, int idx);
        void borrowFromPrev(BNode<T> *curr, int idx);
        void borrowFromNext(BNode<T> *curr, int idx);
        void merge(BNode<T> *curr, int idx);
        char fixChildSize(BNode<T> *parent, T index);
        T deleteNode(BNode<T> *curr, T key);
        // char merge(BNode<T> *curr, T predKey, T succKey);
        int height(BNode<T> *curr); /* calculate height of tree from root */
        bool isHeightBalanced(BNode<T> *curr); /* return height of tree */
};



#endif 