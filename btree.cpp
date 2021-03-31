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
    
    toSplit->maxKeys = this->m - 1; 

    // insert the middle key of toSplit to the node that was split
    x->keys->push_back(toSplit->keys->at(this->m - 1));

    // have to remove the keys / children from the node that we copied from
    toSplit->removeKey(this->m-1, keyCount + this->m);
    toSplit->removeChild(this->m, childCount + this->m);

    // add the new node to the parent
    x->insertChild(newNode);

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
void BTree<T>::insert(T key) 
{   
    
    this->index+=1; 
    int ind = this->index;

    if(this->root == nullptr) {
        this->root = new BNode<T>(m, compare, printKey); 
    }
    // if the root is full
    else if(this->root->keys->size() == 2 * m - 1){
        BNode<T> *node = new BNode<T>(m, compare, printKey); 
        int pos = node->insertChild(root);
        node->isLeaf = false; 
        splitChild(node, pos); 
        root = node; 
    } 

    BNode<T> *curr = root; // if the root is not full we need to find the right place to insert (only on leaf)

    while(!curr->isLeaf) {

        int keyInd = curr->keys->size() - 1; 
        while(keyInd >= 0 && (compare(key, curr->keys->at(keyInd)->key) < 0)) {
            std::cout << curr->keys->at(keyInd)->key << ", " << key << std::endl;
            keyInd--; 
        }
        // keyInd is place where K is greater than key -> insert key in place after that
        keyInd += 1; 

        // check if the current child is full
        if(curr->children->at(keyInd)->keys->size() == 2 * m - 1){

            // split the child of curr
            splitChild(curr, keyInd);

            // after split figure out where to put the new key
            if(compare(curr->keys->at(keyInd)->key, key)) {
                keyInd++;

            }

            // at this point keyInd points to index where k > keys[keyInd]
        }
        curr = curr->children->at(keyInd);

    }

    curr->insertKey(key, ind); 
}

template <typename T>
void BTree<T>::remove(T key)
{

    BNode<T> *curr = getNode(key);

    // If the key k is in node x and x is a leaf node
    if(curr->children->size() == 0){
        std::cout<< "isLeaf";
        curr->print();
        int i = 0; 
        while ( i < curr->keys->size() && (compare(key, curr->keys->at(i)->key) > 0) ){
            i++;
        }   
        if( i < curr->keys->size() && compare(key, curr->keys->at(i)->key) == 0 ) {
            curr->keys->erase(curr->keys->begin() + i);   
        }
    }
    // If the key k is in node x and x is an internal node
    else {

        	BNode<T> *leftChild = curr->child[i];
			BNode<T> *rightChild = curr->child[i + 1];

            if(leftChild->size() > m){
                
            }


    }




//     a) If the child y that precedes k in node x has at least t keys, then find the predecessor k0 of k in the sub-tree rooted at y. Recursively delete k0, and replace k by k0 in x. (We can find k0 and delete it in a single downward pass.)

//     b) If y has fewer than t keys, then, symmetrically, examine the child z that follows k in node x. If z has at least t keys, then find the successor k0 of k in the subtree rooted at z. Recursively delete k0, and replace k by k0 in x. (We can find k0 and delete it in a single downward pass.)

//      c) Otherwise, if both y and z have only t-1 keys, merge k and all of z into y, so that x loses both k and the pointer to z, and y now contains 2t-1 keys. Then free z and recursively delete k from y.



// 3. If the key k is not present in internal node x, determine the root x.c(i) of the appropriate subtree that must contain k, if k is in the tree at all. If x.c(i) has only t-1 keys, execute step 3a or 3b as necessary to guarantee that we descend to a node containing at least t keys. Then finish by recursing on the appropriate child of x.

//     a) If x.c(i) has only t-1 keys but has an immediate sibling with at least t keys, give x.c(i) an extra key by moving a key from x down into x.c(i), moving a key from x.c(i) ’s immediate left or right sibling up into x, and moving the appropriate child pointer from the sibling into x.c(i).

//     b) If x.c(i) and both of x.c(i)’s immediate siblings have t-1 keys, merge x.c(i) with one sibling, which involves moving a key from x down into the new merged node to become the median key for that node.

}

template <typename T>
void BTree<T>::traverse() { traverse(this->root); }

template <typename T>
void BTree<T>::traverse(BNode<T> *curr)
{
    int ind = 0; 

    while(ind < curr->keys->size()) 
    {
        if(curr->isLeaf == false) {
            // traverse the children in order
            traverse(curr->children->at(ind));
        }
        
        if(curr->isLeaf == true) {
            // traverse the children in order
            std::cout << "isLeaf: " ;
        }

        std::cout << "(";
        printKey(curr->keys->at(ind)->key);
        std::cout << ", " << curr->keys->at(ind)->index << ")" << std::endl;
        ind++; 
    };  

    if(curr->isLeaf == false) {
        // traverse the children in order
        traverse(curr->children->at(ind));
    }

}

template <typename T>
BNode<T>* BTree<T>::getNode(T key)
{
    BNode<T> *curr = root; 

    while(true) {

        int i = 0; 
        while ( i < curr->keys->size() && (compare(key, curr->keys->at(i)->key) > 0) ){
            i++;
        }
        
        if( i < curr->keys->size() && compare(key, curr->keys->at(i)->key) == 0 ) {
            return curr;
        }

        else if(curr->isLeaf) {
            return nullptr; 
        }
        
        else {
            curr = curr->children->at(i);
        }
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



