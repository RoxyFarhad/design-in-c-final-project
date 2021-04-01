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

    for(int i = 1; i < 20; i++)
    {
        btree.insert(rand() % 100 + 1);
    }
    btree.traverse(); 
    return 0;
}
