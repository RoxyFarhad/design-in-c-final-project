#include "node.hpp"

/*
 * default constructor - node with no data
 */
template <typename T>
BNode<T>::BNode(int m, int (*compFunc)(T, T), void (*print)(T))
{
    isLeaf = true;
    size = 0; 
    compare = compFunc; 
    printKey = print;  
    this->keys = new std::vector< BNodeKey<T> *>();  
    this->m = m; 
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
    if(this->size == 0) {
       this->keys->push_back(newKey);
       std::cout << "here" << std::endl; 
    } else {
	
       auto it = this->keys->begin(); 
       while(it != this->keys->end()) {
            BNodeKey<T> *bKey = *it;
            std::cout << bKey->index << std::endl;
            it++; 
        }
   }
    this->print(); 
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

    for(auto it = keys->begin(); it != keys->end(); it++) {
        std::cout << "(";
	printKey((*it)->key); 
	std::cout << ", " << (*it)->index << "), ";
    }
  
    std::cout << std::endl;
}

