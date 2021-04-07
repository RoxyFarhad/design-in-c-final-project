#include "btree.cpp"
#include <stdio.h>
#include <stdlib.h>


int compare(int a, int b)
{
    if(a > b) {
        return 1; 
    } 
    else if(a == b) {
        return 0; 
    } 
    else {
        return -1; 
    }
}

void printKey(int a)
{
    std::cout << a; 
}

int main() 
{
    std::vector<int> degrees = {2, 20, 200, 1000};

    for(int i : degrees) 

    {

    int m = i;
        
    BTree<int> btree(m, &compare, &printKey);

    /* insert elements in descending order */
    for(int i = 1000; i > 0; i--)
    {
        btree.insert(i);
    }

    btree.traverse(); /* traverse calls btree property asserts */ 
    assert(btree.isHeightBalanced()); /* check tree is balanced */

    /* insert elements in ascending order */ 
    for(int i = 1001; i < 10000; i++)
    {
        btree.insert(i);
    }
    btree.traverse(); 
    assert(btree.isHeightBalanced()); 

    /* checks search function */
     
    assert(btree.search(40)->key == 40);
    assert(btree.search(1)->key == 1);
    assert(btree.search(5000)->key == 5000);
    assert(btree.search(9999)->key == 9999);
    assert(btree.search(-10) == nullptr);
    assert(btree.search(0) == nullptr);
    assert(btree.search(10000) == nullptr);

    }


    
}