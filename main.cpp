#include "btree.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// using namespace std;

int compareInt(int a, int b) { 
    return a - b; 
};

void printKey(int key) { std::cout << key; };

int main() {
    int m = 3;
    BTree<int> btree(m, &compareInt, &printKey);

    for(int i = 1; i < 20; i++)
    {
        btree.insert(i);

    }

    // for(int i = 1; i < 3; i++)
    // {
    //     BNode<int> *curr = btree.getNode(i); 
    //     btree.deletion(curr, i);
    //     btree.traverse();
    // }

    BNode<int> *curr = btree.getNode(12); 
    btree.deletion(curr, 12);
    btree.traverse();
    
    

    // std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    // for(int i = 1; i < 1100000; i++)
    // {
    //     try{
    //         btree.deletion(i);
    //     }
    //     catch (std::exception& e)
    //     {
    //         std::cerr << "Exception caught : " << e.what() << std::endl;
    //     }
    //     // cout << i << endl;
    //     // btree.traverse();
    //     // cout << i << endl;

    //     // btree.traverse();

    // }
    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
    // std::chrono::duration<float, std::milli> time_span = end - start;
    // std::cout << time_span.count();

    // btree.remove(12);

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
