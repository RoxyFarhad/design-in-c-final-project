#ifndef BTREE_NODE_H
#define BTREE_NODE_H

#include <string>
#include <vector>
#include <ostream> 
#include <iostream> 

template<typename T>
struct BNodeKey {
    T key; /* this is the PK for our db which is why in this struct */ 
    int index;
};

template<typename T>
class BNode
{

    using BNodeType = BNode<T>; 

    public:
        bool isLeaf; 
        int m; /* order of the tree */
        int size; /* refers to the number of keys */
        std::vector< BNodeKey<T> *> *keys; 
        std::vector<BNodeType *> *children; 
        int minKeys;
        int maxKeys;

    private:
        /* pass in these functions because needed for key comparisons */ 
        int (*compare)(T, T);
        void (*printKey)(T);

    public:
        BNode(int m, int (*)(T, T), void (*)(T)); /* constructor */ 
        /* also missing copy constructor because deemed irrelevant */
        ~BNode( ); /* destructor */
        void print( );
        unsigned insertKey(T k, int index); /* inserts the key into node - returns the index of the key in node */
        unsigned insertChild(int i, BNodeType *x); 
        void removeKey(int i, int j); 
        void removeChild(int i, int j);
};

#endif
