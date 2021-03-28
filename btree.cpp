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
    this->m = t;
    this->compare = compFunc; 
    this->printKey = print; 
    this->root = nullptr;
    this->index = 0; 
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
    
    this->index+=1; 
    int ind = this->index;
    if(this->root == nullptr) {
        this->root = new BNode<T>(m, compare, printKey);  
	this->root->insertKey(key, ind);
    }
    // if the root is full
    else if(this->root->size == 2 * m - 1){
   	
    } 
    else {	
	    root->insertKey(key, ind); 
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
