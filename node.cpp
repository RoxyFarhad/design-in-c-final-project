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
    BNodeKey<T> newKey;
    newKey.key = k; 
    newKey.index = index; 
    int pos = 0; 

    if(this->size == 0) {
        keys.push_back(newKey);
        this->size+=1; 
    } else {
        typename std::vector< BNodeKey<T> >::iterator it = this->keys.begin();
        
        while(it != this->keys.end() && compare(k, (*it).key)) 
        {
            pos++;
            it++; 
        }
        std::cout << pos << std::endl; 

        // add the key
        keys.insert(it, newKey);
    }
    
    this->size+=1; 
    return pos;
}

/*
 * prints all the (key, index) pairs in the node
 */
template <typename T>
void BNode<T>::print()
{
    std::cout << "Node values: ";
    for(auto it = keys.begin(); it != keys.end(); it++) {
        std::cout << "(" << printKey((*it).key) << ", " << (*it).index << "), ";
    }
    std::cout << std::endl;
}

