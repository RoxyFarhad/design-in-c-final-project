#include "interface.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <tuple>

using namespace std;

int main() {
    int m = 4;
    // Interface interface; 
    // interface.run(); 

    BTree<int> btree(m, &compareInt, &printKey);

    // insert elements in descending order
    for(int i = 40; i > 0; i--)
    {
        btree.insert(i);
    }

    // insert elements in ascending order
    for(int i = 41; i < 10000; i++)
    {
        btree.insert(i);
    }
    btree.traverse(); 
    assert(btree.search(40)->key == 40);
    assert(btree.search(1)->key == 1);
    assert(btree.search(5000)->key == 5000);
    assert(btree.search(9999)->key == 9999);
    assert(btree.search(-10) == nullptr);
    assert(btree.search(0) == nullptr);
    assert(btree.search(10000) == nullptr);

}