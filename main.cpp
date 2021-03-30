#include "btree.cpp"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int compareInt(int a, int b) { 
    return a - b; 
};

void printKey(int key) { cout << key; };

int main() {
    int m = 5;
    BTree<int> btree(m, &compareInt, &printKey);

    // insert elements in ascending order
    for(int i = 1; i < 10000; i++)
    {
        btree.insert(i);
    }
    btree.traverse(); 

    // insert elements in descending order
    // for(int i = 40; i > 0; i--)
    // {
    //     btree.insert(i);
    // }
    // btree.traverse(); 

    return 0;
}
