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
    this->maxKeys = m - 1; 
    this->minKeys = (m - 1)/2; 
}

/*
 * deconstructor - iterate through all the 
 */

template <typename T>
BNode<T>::~BNode()
{

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
unsigned BNode<T>::insertChild(BNodeType *x)
{
    this->children->push_back(x);
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

