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

    for(int i = 1; i < 16; i++)
    {
        btree.insert(i);

    }
    for(int i = 1; i < 16; i++)
    {
        cout << i << endl;
        btree.traverse();
        cout << i << endl;
        btree.deletion(i);
        // btree.traverse();

    }

    // for(int i = 100; i > 50; i--)
    // {
    //     cout << i << endl;
    //     btree.remove(i);
    //     btree.traverse();
    // }



    // btree.traverse();
    // for(int i = 1; i < 20; i++)
    // {
    //     btree.search(i);   
    // }

    // btree.remove(6);
    // btree.traverse();
    // btree.remove(15);
    // btree.remove(88);
    // cout << "27 NOW" <<endl;
    // cout << " " << endl;
    // btree.remove(27);

    // btree.traverse();


    
    // cout << btree.search(1);

    return 0;
}
