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
#include <set>

class Interface
{
    using date_time = std::chrono::system_clock::time_point; 
    private:
        std::map<std::string, int> *columns; 
        std::map<int, std::vector<std::string >*> *indices; /* map that holds the indices to the columns */
        BTree<date_time>* insertData();  
        std::string dateTimetoString(date_time date); 
        void printInstructions(); 
        void select(std::string line, BTree<Interface::date_time> *btree);
        void remove(std::string line, BTree<Interface::date_time> *btree); 
        void insert(std::string line, BTree<Interface::date_time> *btree);  
        void printSelect(std::vector<std::string> columns, std::vector<std::vector<std::string>> values);
    public:
        Interface();
        void run(); 
        ~Interface();
};

#endif