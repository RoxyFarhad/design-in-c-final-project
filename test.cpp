#include "btree.cpp"
#include <chrono>
#include <random>
#include <string>
#include <set>
#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <map>

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

template < typename T>
typename std::list<T>::iterator insert_sorted( std::list<T> &list, T const& item)
{
    return list.insert
        (
            std::upper_bound( list.begin(), list.end(), item),
            item
        );
}

float insertVector(std::vector<int> &intVec, std::vector<int> values)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    for(int i = 0; i < values.size(); i++)
    {    
        insert_sorted(intVec, values[i]); 
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
    std::chrono::duration<float, std::milli> time_span = end - start;

    return time_span.count();
}

float insertMap(std::map<int, int> &intMap, std::vector<int> values)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    for(int i = 0; i < values.size(); i++)
    {
        intMap[i] = values[i]; 
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
    std::chrono::duration<float, std::milli> time_span = end - start;

    return time_span.count();
}

float insertBTree(BTree<int> &btree, std::vector<int> values)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    for(int i = 0; i < values.size(); i++)
    {
        btree.insert(values[i]);
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
    std::chrono::duration<float, std::milli> time_span = end - start;

    return time_span.count();
}

float searchVector(std::vector<int> &vec, std::vector<int> &values, int value)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::vector<int>::iterator it; 
    it = find(vec.begin(), vec.end(), value); 
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
    std::chrono::duration<float, std::milli> time_span = end - start;
    return time_span.count();
}

float searchBTree(BTree<int> &btree, std::vector<int> &values, int value)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    btree.search(value);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
    std::chrono::duration<float, std::milli> time_span = end - start;
    return time_span.count();
}

float searchMap(std::map<int, int> &intMap, std::vector<int> &values, int value)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::vector<int>::iterator it; 
    int x = intMap[value]; 
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
    std::chrono::duration<float, std::milli> time_span = end - start;
    return time_span.count();
}

void bTreeOrder()
{

    std::vector<int> values; 
    std::minstd_rand0 randGenerator(1);

    for(int i = 0; i < 50000; i++)
    {
        values.push_back(randGenerator()); 
    }

    int x = 3; 
    for(int j = 1; j <= 50; j++)
    {
        int m = x*j;
        BTree<int> btree = BTree<int>(m, &compare, &printInt);
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        // speed it takes to insert 50,0000 values
        for(int i = 0; i < values.size(); i++){
            btree.insert(values[i]); 
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
        std::chrono::duration<float, std::milli> time_span = end - start;
        std::cout << time_span.count() << std::endl; 

    }
}

void containerComparisons()
{
    for(int j = 1; j <= 20; j++)
    {
        // generate a list of numbers with random value and measure how long it takes to insert
        int m = 12; 
        BTree<int> btree = BTree<int>(m, &compare, &printInt); 
        std::vector<int> intVec; 
        std::map<int, int> intMap; 

        std::minstd_rand0 randGenerator(1);
        std::vector<int> values; 
        std::vector<int> randInsert; 

        int numOfValues = 50000 * j; 
        for(int i = 0; i < numOfValues; i++)
        {   
            int num = randGenerator(); 
            values.push_back(num);
            randInsert.push_back(num);  
        }

        float bTime = insertBTree(btree, values);
        //float vecTime = insertVector(intVec, values); 
        //float mapTime = insertMap(intMap, values); 
        // float listTime = insertList(values); 
        //std::cout << mapTime << std::endl; 
        // std::cout << "Number of Values: " << numOfValues << std::endl; 
        //std::cout << bTime << std::endl; 
        // std::cout << "vec-insert-time: " << vecTime << std::endl; 

        // choose 10 values randomly and time how long it takes to find those values
        // because vector is linear search - reinsert the values in random order as that doesn't matter for search

        float bSearchTime = 0; 
        float vecSearchTime = 0;
        float mapSearchTime = 0; 
        for(int i = 0; i < 10; i++)
        {
            int index = randGenerator() % (( numOfValues + 1 ));
            int num = values[index]; 
            bSearchTime += searchBTree(btree, values, num); 
            //vecSearchTime += searchVector(randInsert, values, num); 
            mapSearchTime += searchMap(intMap, values, num); 
        }
        bSearchTime = bSearchTime / 10; 
        vecSearchTime = vecSearchTime / 10; 
        mapSearchTime = mapSearchTime / 10; 
        // std::cout << "btree-search-time: " << bSearchTime << std::endl; 
        // std::cout << "vec-search-time: " << vecSearchTime << std::endl; 
        // randomly choose an inserted value and check how long it would take to find it given N values
        std::cout << mapSearchTime << std::endl; 

    }
}

int main() 
{   
    containerComparisons(); 
    //bTreeOrder(); 
}