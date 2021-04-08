#include "node.hpp"

/*
 * default constructor - node with no data
 */
template <typename T>
BNode<T>::BNode(int m, int (*compFunc)(T, T), void (*print)(T))
{
    isLeaf = true;
    compare = compFunc; 
    printKey = print;  
    this->keys = new std::vector< BNodeKey<T> *>();  
    this->children = new std::vector<BNodeType *>(); 
    this->m = m; 
}

/*
 * deconstructor - iterate through all the 
 */

template <typename T>
BNode<T>::~BNode()
{
    // int i = 0; 
    // for(int i = 0; i < this->keys->size(); i++){
    //     delete this->keys->at(i); 
    // }
    // for(int i = 0; i < this->children->size(); i++){
    //     delete this->children->at(i); 
    // }
    // delete this; 
}

/*
 * adds a key to the node 
 */
template <typename T>
unsigned BNode<T>::insertKey(T k, int index)
{
   
    BNodeKey<T> *newKey = new BNodeKey<T>(); 
    newKey->key = k; 
    newKey->index = index; 
    int pos = 0; 
    if(this->keys->size() == 0) {
       this->keys->push_back(newKey);
    } else {
	
        auto it = this->keys->begin(); 
        while(it != this->keys->end() && (compare(k, (*it)->key) > 0) ) {
            it++; 
            pos++; 
        }
        if(pos == this->keys->size()) {
            this->keys->push_back(newKey);
        } else {
            this->keys->insert(it, newKey);
        }
    }
    return pos;
}

template <typename T> 
unsigned BNode<T>::insertChild(int i, BNodeType *x)
{
    // get the iterator to insert
    if(i == this->children->size()){
        this->children->push_back(x); 
    }
    else {
        auto it = this->children->begin(); 
        int ind = 0; 
        while(ind < i){
            ind++; 
            it++; 
        }
        this->children->insert(it, x);
    }
    return this->children->size() - 1; 
}

/* 
 * removes the 
 */
template <typename T> 
void BNode<T>::removeChild(int i, int j)
{
    this->children->erase(this->children->begin() + i, this->children->begin() + j);
    this->size -= 1; 
}

/* 
 * removes the keys between two positions
 */
template <typename T> 
void BNode<T>::removeKey(int i, int j)
{
    this->keys->erase(this->keys->begin() + i, this->keys->begin() + j);
}
/*
 * prints all the (key, index) pairs in the node in order
 */
template <typename T>
void BNode<T>::print()
{
    std::cout << "Node values: ";

    for(auto it = keys->begin(); it != keys->end(); it++) {
        std::cout << "(";
	printKey((*it)->key); 
	std::cout << ", " << (*it)->index << "), ";
    }
  
    std::cout << std::endl;
}

