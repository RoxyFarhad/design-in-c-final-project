#include "btree.hpp"
#include <math.h> 

#define NEW_ROOT 2
#define MODIFIED_NOT_ROOT 1
#define NOT_MODIFIED 0

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
T BTree<T>::findIndex(BNode<T> *curr, T key)
{
    unsigned keyInd = 0;
    while (keyInd < curr->keys->size() && (compare(key, curr->keys->at(keyInd)->key) > 0) ){
        keyInd++;
    } 
    std::cout << "Index found: " << keyInd << std::endl;
    return keyInd;

}

template <typename T>
T BTree<T>::remove(T key)
{

    std::cout << key;
    BNode<T> *curr = getNode(key);
    
    while (true) {
        std::cout << "hello";
        T i = findIndex(curr, key);
        std::cout << "hello";
        if(i < curr->keys->size() && !(compare(key, curr->keys->at(i)->key) || compare(curr->keys->at(i)->key, key))){
            std::cout << i;
            T ret = curr->keys->at(i)->key;
            std::cout << "RET key" << ret << std::endl;

            // If the key k is in node x and x is a leaf node
            if(curr->children->size() == 0){
                std::cout << "Is Leaf node";
                deleteNode(curr, i);
            } 
            // If the key k is in node x and x is an internal node
            else {
                int predKey = i;
                int succKey = i+1;
                BNode<T> *child = curr->children->at(predKey); 
                BNode<T> *sibling = curr->children->at(succKey);
                
                std::cout << "predKey: " << predKey << std::endl;
                std::cout << "succKey: " << succKey << std::endl;

                //If the child that precedes key has more than the minimum degree
                if(child->keys->size() >= m){
                    std::cout <<"pred!" <<std::endl;
                    curr->print();
                    while(child->children->size()>0){
                        fixChildSize(child, child->keys->size());
                        child = child->children->at(child->keys->size());
                    }
                    curr->keys->at(predKey)->key = deleteNode(child, child->keys->size()-1);


                }
                else if (sibling->keys->size() >= m){
                    std::cout <<"succ!" <<std::endl;
                    curr->print();
                    sibling->print();
                    while(sibling->children->size()>0){
                        fixChildSize(sibling, 0);
                        sibling = sibling->children->at(0);
                    }
                    curr->keys->at(predKey)->key = deleteNode(sibling, 0);
                } 
                else {
                    std::cout << "Remove: key in external node, child that preceds key have less than minimum degree" << std::endl;
                    curr->print();
                    merge(curr, predKey, succKey);
                    std::cout << "Competed merge, back in remove()" <<std::endl;
                    curr = child;
                    std::cout<< "Update current node" << std::endl;
                    curr->print();
                    continue;

                }
            }
            return ret;
        }
        else {

            if(curr->children->size()==0){
                std::cout << "key not found" << std::endl;
                break;
            }
            std::cout<< "Adjusting the current node, and moving down the tree"<<std::endl;
            char result = fixChildSize(curr, i);
            std::cout << result << "RESULT" << std::endl;
            if (result == NEW_ROOT){
                curr = root;
            } else {
                curr = curr->children->at(findIndex(curr, key));
            }
			
        }    
    }
}

template <typename T>
T BTree<T>::deleteNode(BNode<T> *curr, T key)
{
    T ret = curr->keys->at(key)->key;
    T size = curr->keys->size()-1;
    std::cout << size ;
    std::cout << key;
    T index = key;

    std::cout<< "CURR: " << std::endl;
    curr->print();
    while (key < curr->keys->size()-1){

        std::cout << "***********Children of curr" << std::endl;
        for(int i = 0; i < curr->children->size(); i++){
            curr->children->at(i)->print();
        }
        std::cout << "*******************" <<std::endl;
        
        curr->keys->at(key) = curr->keys->at(key+1);
        key++;
    } 

    while(index < curr->children->size()){
        if (curr->children->size() > 0 && index+2 <= curr->keys->size()-1){
            curr->children->at(index+1) = curr->children->at(index+2);
        }
        index++;
    }
   

    curr->removeKey(size, size+1);


    std::cout << "****************Final Children of curr" << std::endl;
    for(int i = 0; i < curr->children->size(); i++){
        curr->children->at(i)->print();
    }
     std::cout << "*******************" <<std::endl;


    return ret;
}

template <typename T>
char BTree<T>::fixChildSize(BNode<T> *parent, T index)
{
    BNode<T> *child = parent->children->at(index);

    if(child->keys->size() < m){

        if( index != 0 && parent->children->at(index-1)->keys->size() >= m){
            std::cout << "LC" << std::endl;
            BNode<T> *leftchild = parent->children->at(index-1);
            leftchild->print();
            child->children->at(0) = leftchild->children->at(leftchild->keys->size());
            parent->keys->at(index-1)->key = deleteNode(leftchild, leftchild->keys->size()-1);
            std::cout << "Parent print" << std::endl;
            parent->print();
            std::cout << "Child print" << std::endl;
            child->print();
            std::cout << "Left Child" <<std::endl;
            
        } 
        else if (index != parent->keys->size() && parent->children->at(index+1)->keys->size() >= m){
            std::cout << "RC" << std::endl;
            BNode<T> *rightchild = parent->children->at(index+1);
            child->insertKey(index, index);
            child->children->at(child->keys->size()) = rightchild->children->at(0);
            rightchild->children->at(0) = rightchild->children->at(1);
            parent->keys->at(index)->key = deleteNode(rightchild, 0);
            std::cout << "Parent print" << std::endl;
            parent->print();
            std::cout << "Child print" << std::endl;
            child->print();
        }
        else if (index != 0){
            std::cout << "LC merge" << std::endl;
            std::cout << "Parent print" << std::endl;
            parent->print();
            std::cout << "Child print" << std::endl;
            child->print();
            return merge(parent, index-1, index);
        }
        else {
            std::cout << "RC merge" << std::endl;
            std::cout << "Parent print" << std::endl;
            parent->print();
            std::cout << "Child print" << std::endl;
            child->print();
            return merge(parent, index, index+1);
        }
        return MODIFIED_NOT_ROOT;

    } 
    return NOT_MODIFIED;
}


template <typename T>
char BTree<T>::merge(BNode<T> *curr, T predKey, T succKey)
{
    std::cout << "In merge()" << std::endl;
    BNode<T> *child = curr->children->at(predKey); 
    BNode<T> *sibling = curr->children->at(succKey);


    // Copy key from parent to left child
    T r = deleteNode(curr, predKey);
    child->insertKey(r, r);
    T size = child->keys->size();


    // Copy keys from sibling to child node
    for(int i = 0; i < sibling->keys->size(); i++ ){
        child->insertKey(sibling->keys->at(i)->key, sibling->keys->at(i)->index);
    }

    if (sibling->children->size() != 0){
        for(int i = 0; i < sibling->children->size(); i++){
            child->insertChild(size+i, sibling->children->at(i));
        }
            
    }
   
    // Removing child
    curr->removeChild(succKey, succKey+1);

    std::cout << "ROOT:";
    root->print();
    if (curr->keys->size() == 0) {
		root = child;
        return NEW_ROOT;
    }
    return MODIFIED_NOT_ROOT;
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
            
            curr->print();
            
            // a non leafnode with n-1 keys must have n number of children
            assert(curr->children->size() == curr->keys->size() + 1);

            // traverse the children in order
            traverse(curr->children->at(ind));
        }
        std::cout << "(";
        printKey(curr->keys->at(ind)->key);
        std::cout << ", " << curr->keys->at(ind)->index << ")" << std::endl;
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




