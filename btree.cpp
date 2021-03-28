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
 * Splits the node if full
 * x: node to be split 
 * i: index of x in this->children calling function
 */
template <typename T>
void BTree<T>::splitChild(BNode<T> *x, int i)
{   
    BNode<T> *toSplit = x->children->at(i);
    BNode<T> *newNode = new BNode<T>(m, compare, printKey);
    newNode->isLeaf = toSplit->isLeaf;

    // want to copy the second half of keys of toSplit to the newNode
    int keyCount = 0; 
    for(int i = 0; i < this->m - 1; i++){
        BNodeKey<T> *curr = toSplit->keys->at(i + this->m); 
        newNode->keys->push_back(curr);
        keyCount += 1; 
    }

    // if node is not a leaf then copy m children into the newNode
    int childCount = 0; 
    if(!toSplit->isLeaf) {
        for(int i = 0; i < this->m; i++) {
            BNode<T> *curr = toSplit->keys->at(i + this->m);
            newNode->children->push_back(curr); 
            childCount += 1; 
        }
    }
    
    toSplit->maxKeys = this->m - 1; 

    // insert the middle key of 
    x->insertKey(toSplit->keys->at(this->m - 1));

    // have to remove the keys / children from the node that we copied from
    toSplit->removeKey(this->m, keyCount + this->m);
    toSplit->removeKey(this->m, childCount + this->m);

    // add the new node to the parent
    x->insertChild(newNode);
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
        BNode<T> *node = new BNode<T>(m, compare, printKey); 
        
        int pos = node->insertChild(root);
        node->isLeaf = false; 
        splitChild(node, pos); 
        root = node; 
    } 

    BNode<T> *curr = root; // if the root is not full we need to find the right place to insert (only on leaf)

    while(!curr->isLeaf) {

        int keyInd = 0; 
        auto it = this->keys->begin();
        while(it != this->keys->end() && compare(k, (*it)->key) > 0) {
            it++;
            keyInd += 1
        }

        if(curr->)

    }
    
    curr->insertKey(key, ind); 

}

template <typename T>
T BTree<T>::remove(T key)
{
    return key; 
}

template <typename T> 
void BTree<T>::insertNonFull() 
{

}


/*
template <typename T>
BNode<T> BTree<T>::search(T key)
{

}
*/
