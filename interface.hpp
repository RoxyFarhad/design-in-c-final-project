#ifndef INTERFACE_H
#define INTERFACE_H

#include <map>
#include <fstream>
#include <iostream>
#include "btree.cpp"
#include <string>
#include <chrono>
#include <sstream>
#include <ctime>
#include <utility>
class Interface
{
    using date_time = std::chrono::system_clock::time_point; 
    private:
        std::map<std::string, int> *columns; 
        std::map<int, std::vector<std::string >*> *indices; /* map that holds the indices to the columns */
        BTree<date_time>* insertData();  
        std::string dateTimetoString(date_time date); 
        void printInstructions(); 
        void select(); 
    public:
        Interface();
        void run(); 
        ~Interface();
};

#endif