#ifndef INTERFACE_H
#define INTERFACE_H

#include <map>
#include <fstream>
#include "btree.cpp"
#include <string>

class Interface
{
    private:
        std::map<int, std::vector<std::string>> *indices; /* map that holds the indices to the columns */
    public:
        Interface();
        void insertData();  
        void run(); 
        ~Interface();
};

#endif