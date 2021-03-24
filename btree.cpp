#include "btree.hpp"

template <typename T>
BTree<T>::BTree(int m) 
{   
    root = NULL; 
    compare = nullptr; 
    printKey = nullptr; 
    this->m = m; 
}

template <typename T>   
BTree<T>::BTree( int t, bool (*compFunc)(T, T), void (*print)(T) )
{
    m = t;
    compare = compFunc; 
    printKey = print; 
    root = NULL; 
}

template <typename T>
void BTree<T>::clear()
{

}

template <typename T> 
void BTree<T>::insert(T key) 
{   

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