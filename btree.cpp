#include "btree.hpp"

template <typename T>
BTree<T>::BTree(int m) 
{   
    root = nullptr; 
    compare = nullptr; 
    printKey = nullptr; 
    this->m = m; 
    index = 0; 
}

template <typename T>   
BTree<T>::BTree( int t, int (*compFunc)(T, T), void (*print)(T) )
{
    m = t;
    compare = compFunc; 
    printKey = print; 
    root = nullptr;
    index = 0; 
}

template <typename T>
BTree<T>::~BTree() {
    // have to go through all the nodes and delete them
}

template <typename T>
void BTree<T>::clear()
{

}

/*
 * Inserting a node into a tree
 */
template <typename T> 
void BTree<T>::insert(T key) 
{   
    
    int ind = this->index + 1; 
    this->index+=1; 
    if(this->root == nullptr) {
        root = (BNode<T>*)(&(this->compare), &(this->printKey));
        root->insertKey(key, ind);
        root->print();
    }
}

template <typename T>
T BTree<T>::remove(T key)
{
    return key; 
}

/*
template <typename T>
BNode<T> BTree<T>::search(T key)
{

}
*/