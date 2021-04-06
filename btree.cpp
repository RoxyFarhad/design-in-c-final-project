#include "btree.hpp"
#include <math.h> 
#include <algorithm>
#include <cmath>

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
    // delete this; 
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
            BNode<T> *curr = toSplit->children->at(i + this->m);
            newNode->children->push_back(curr); 
            childCount += 1; 
        }
    }

    // insert the middle key of toSplit to the node that was split
    BNodeKey<T> *bKey = toSplit->keys->at(this->m - 1); 

    // 
    auto it = x->keys->begin();
    int childInd = 0; 
    while(it < x->keys->end() && compare(bKey->key, (*it)->key) > 0) 
    {
        it++;
        childInd++; 
    }

    x->keys->insert(it, bKey);
    // have to remove the keys / children from the node that we copied from
    toSplit->removeKey(this->m-1, keyCount + this->m);
    toSplit->removeChild(this->m, childCount + this->m);

    // add the new node to the parent
    x->insertChild(childInd+1, newNode);
    
    // std::cout << "x: ";
    // x->print();
    // std::cout << "\n";
    // std::cout << "toSplit: ";
    // toSplit->print();
    // std::cout << "\n";
    // std::cout << "newNode: ";
    // newNode->print(); 
    // std::cout << "\n";

}

/*
 * Inserting a node into a tree
 */
template <typename T> 
int BTree<T>::insert(T key) 
{   
    this->index+=1; 
    int ind = this->index;

    if(this->root == nullptr) {
        this->root = new BNode<T>(m, compare, printKey); 
    }
    // if the root is full
    else if(this->root->keys->size() == 2 * m - 1){
        BNode<T> *node = new BNode<T>(m, compare, printKey); 
        int pos = node->insertChild(0, root);
        node->isLeaf = false; 
        splitChild(node, pos); 
        root = node; 
    } 

    BNode<T> *curr = root; // if the root is not full we need to find the right place to insert (only on leaf)

    while(!curr->isLeaf) {
        int keyInd = curr->keys->size() - 1;  
        
        while(keyInd >= 0 && (compare(key, curr->keys->at(keyInd)->key) < 0)) {
            // std::cout << curr->keys->at(keyInd)->key << ", " << key << std::endl;
            keyInd--; 
        }
        
        // keyInd is place where K is greater than key -> insert key in place after that
        keyInd += 1; 

        // check if the current child is full
        if(curr->children->at(keyInd)->keys->size() == 2 * m - 1){

            splitChild(curr, keyInd);

            if(compare(curr->keys->at(keyInd)->key, key) < 0){
                keyInd++; 
            }
            // at this point keyInd points to index where k > keys[keyInd]
        }
        curr = curr->children->at(keyInd); 
    }
    curr->insertKey(key, ind); 
    return ind; 
}

template <typename T>
T BTree<T>::remove(T key)
{
    return key; 
}

template <typename T>
int BTree<T>::height(BNode<T> *curr)
{
    if(curr->isLeaf == true) 
    {
        return 0;
    }
    int leftHt = height(curr->children->at(0));
    int rightHt = height(curr->children->at(curr->children->size()-1));
    int curHt = std::max(leftHt, rightHt) + 1;
    return curHt;
}

template <typename T>
bool BTree<T>::isHeightBalanced()
{
    return isHeightBalanced(this->root);

}

template <typename T>
bool BTree<T>::isHeightBalanced(BNode<T> *curr)
{   
    if(curr->isLeaf == true)
    {
        return true;
    }
    int leftHt = height(curr->children->at(0));
    int rightHt = height(curr->children->at(curr->children->size()-1));
    if(std::abs(leftHt - rightHt) > 1)
    {
        return false;
    }
    return isHeightBalanced(curr->children->at(0)) && isHeightBalanced(curr->children->at(curr->children->size()-1));


}

template <typename T>
void BTree<T>::traverse() 
{ 
    traverse(this->root); 
}

template <typename T>
void BTree<T>::traverse(BNode<T> *curr)
{
    int ind = 0; 
    while(ind < curr->keys->size()) 
    {
        
        if(curr->isLeaf == false) {
            // all non leaf nodes except root must have at least m/2 children
            if(curr != root) {
            assert(curr->children->size() >= m / 2);
            }

            // a non leafnode with n-1 keys must have n number of children
            assert(curr->children->size() == curr->keys->size() + 1);

            // traverse the children in order
            traverse(curr->children->at(ind));
        }
        ind++;

        // all nodes except root must have between ceil(m/2)-1 and 2m keys (?)
        if(curr != root) {
            // std::cout << "# of keys: " << curr->keys->size() << std::endl;
            assert(curr->keys->size() >= ceil(m/2)-1 && curr->keys->size() <= 2 * m); 
        };

        // the root has between 1 and 2m-1 keys
        assert(root->keys->size() >= 1 && root->keys->size() <= 2 * m - 1);

        // if root node is non leaf node, then is must have at least 2 children
        if(root->isLeaf == false){
            assert(root->children->size() >= 2);
        };

        // all key values are in ascending order
        if(curr->keys->size() > 1){
                int last = curr->keys->at(0)->key;
                for(int i = 1; i<curr->keys->size(); i++)
                    // std::cout << curr->keys->at(i)->key << std::endl;
                    assert(last <= curr->keys->at(i)->key);
        };

        
    };  

    if(curr->isLeaf == false) {
        // traverse the last child
        traverse(curr->children->at(ind));
        
    }
}


template <typename T>
BNodeKey<T>* BTree<T>::search(T key)
{
    BNode<T> *curr = root; 

    while(true) {

        int i = 0; 
        while ( i < curr->keys->size() && (compare(key, curr->keys->at(i)->key) > 0) ){
            i++;
        }
        
        if( i < curr->keys->size() && compare(key, curr->keys->at(i)->key) == 0 ) {
            // found the key
            return curr->keys->at(i);
        }

        else if(curr->isLeaf) {
            return nullptr; 
        }
        
        else {
            curr = curr->children->at(i);
        }
    }
}




