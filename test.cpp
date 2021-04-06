#include "btree.cpp"
#include <chrono>
#include <random>
#include <string>
#include <set>
#include <list>
#include <vector>
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

void printInt(int a)
{
    std::cout << a; 
}

/* method copied from stack overflow */
template< typename T >
typename std::vector<T>::iterator insert_sorted( std::vector<T> & vec, T const& item )
{
    return vec.insert
        ( 
            std::upper_bound( vec.begin(), vec.end(), item ),
            item 
        );
}

float insertVector(std::vector<int> values)
{
    std::vector<int> intVec; 
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    for(int i = 0; i < values.size(); i++)
    {    
        insert_sorted(intVec, values[i]); 
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
    std::chrono::duration<float, std::milli> time_span = end - start;

    return time_span.count();
}

float insertBTree(std::vector<int> values)
{
    int m = 3; 
    BTree<int> btree = BTree<int>(m, &compare, &printInt); 
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    for(int i = 0; i < values.size(); i++)
    {
        btree.insert(values[i]);
    }

    btree.traverse();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
    std::chrono::duration<float, std::milli> time_span = end - start;

    return time_span.count();
}

int main() 
{

    // generate a list of numbers with random value and measure how long it takes to insert
    std::minstd_rand0 randGenerator(1);
    std::vector<int> values; 
    for(int i = 0; i < 150000; i++)
    {   
        int num = randGenerator(); 
        values.push_back(num); 
    }
    float bTime = insertBTree(values);
    float vecTime = insertVector(values); 
    std::cout << "btree-time: " << bTime << std::endl; 
    std::cout << "vec-time: " << vecTime << std::endl; 
}