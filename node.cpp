#include "node.hpp"

/*
 * default constructor - node with no data
 */
template <typename T>
BNode<T>::BNode(bool (*compFunc)(T, T), void (*print)(T))
{
    isLeaf = true;
    size = 0; 
    compare = compFunc; 
    printKey = print; 
    minKey = NULL; 
    maxKey = NULL; 
}