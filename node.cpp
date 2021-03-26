#include "node.hpp"

/*
 * default constructor - node with no data
 */
template <typename T>
BNode<T>::BNode(int (*compFunc)(T, T), void (*print)(T))
{
    isLeaf = true;
    size = 0; 
    compare = compFunc; 
    printKey = print; 
    minKey = NULL; 
    maxKey = NULL; 
}

/*
 * adds a key to the node 
 */
template <typename T>
unsigned BNode<T>::insertKey(T k, int index)
{
    int pos = 0; 
    typename std::vector< BNodeKey<T> >::iterator it = this->keys.begin();
    while(it != this->keys.end() && compare(k, (*it).key)) 
    {
        pos++;
        it++; 
    }

    BNodeKey<T> newKey;
    newKey.key = k; 
    newKey.index = index; 

    // add the key
    keys.insert(it, newKey);
    this->size+=1; 
    return pos;

}

