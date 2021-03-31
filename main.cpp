#include "btree.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int compareInt(int a, int b) { 
    return a - b; 
};

void printKey(int key) { cout << key; };

int main() {
    int m = 2;
    BTree<int> btree(m, &compareInt, &printKey);

    for(int i = 1; i < 30; i++)
    {
        btree.insert(i);
    }

    btree.traverse();

    btree.remove(1);

    btree.traverse();
    
    // cout << btree.search(1);

    return 0;
}
