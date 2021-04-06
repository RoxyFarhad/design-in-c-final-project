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
    int m = 3;
    BTree<int> btree(m, &compareInt, &printKey);

    for(int i = 1; i < 200; i++)
    {
        btree.insert(i);

    }

    btree.traverse();
    for(int i = 1; i < 200; i++)
    {
        btree.search(i);   
    }

    btree.remove(135);

    btree.traverse();


    
    // cout << btree.search(1);

    return 0;
}
