#include "btree.cpp"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int compareInt(int a, int b) { 
    return a - b; 
};

void printKey(int key) { cout << key << endl; };

int main() {
    int m = 4;
    BTree<int> btree(m, &compareInt, &printKey);

    int testKey = 50;
    btree.insert(testKey);
    return 0;
}