#include "interface.hpp"
#include <iostream>
#include <fstream>

int compareInt(int a, int b) { 
    return a - b; 
};

void printKey(int key) { std::cout << key; };

Interface::Interface()
{
    
}

Interface::~Interface()
{
    /* remove map, fs, b tree */ 
}

/*
 * main function that runs the interface
 */
void Interface::run()
{
    char filename[256];
    // wait for a csv file 
    std::cout << "\nPlease enter a CSV file for table data: ";
    std::cin.getline(filename, 256); 
    
    FILE *pFile; 
    pFile = fopen(filename, "r"); 

    while(pFile == NULL) {
        std::cout << "\nInvalid filename, please enter another: "; 
        std::cin.getline(filename, 256);
        pFile = fopen(filename, "r");
    }; 

    std::cout << "\n~~~~~~~~~~~~~~ INSTRUCTIONS ~~~~~~~~~~~~~~~\n" << std::endl; 
    std::cout << "COMMANDS: \n" << std::endl; 
    std::cout << "  1. SELECT <PK> [WHERE <PK> = x]" << std::endl; 
    std::cout << "  2. INSERT (<PK>, ..., <columnN>) (<PK>, ..., <valueN>)" << std::endl; 
    std::cout << "  3. DELETE WHERE PK = x\n" << std::endl; 
}

void Interface::insertData()
{
    
}
