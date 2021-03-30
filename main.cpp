#include "btree.cpp"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int compareInt(int a, int b) { 
    return a - b; 
};

void printKey(int key) { cout << key; };

int main() {
    int m = 2;
    BTree<int> btree(m, &compareInt, &printKey);

    for(int i = 1; i < 15; i++)
    {
        btree.insert(i);
    }
    btree.search(10);
    return 0;
}
