#ifndef BTREE_NODE_H
#define BTREE_NODE_H

#include <string>
#include <vector>

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
        int size; /* refers to the number of keys */
        T minKey; /* smallest value in node */
        T maxKey; /* largest value in node */
        std::vector< BNodeKey<T> > keys; 
        std::vector<BNodeType> children; 

    private:
        /* pass in these functions because needed for key comparisons */ 
        bool (*compare)(T, T);
        void (*printKey)(T);

    public:
        BNode(bool (*)(T, T), void (*)(T)); /* constructor */ 
        /* also missing copy constructor because deemed irrelevant */
        ~BNode( ); /* destructor */
        void print( );
    
    // private:

    //     void addKeyToNode(T); 
        
    /* ~~~~ Methods ~~~~~ */ 

};

#endif