#include "interface.hpp"

/*
 * if lhs > rhs => return 1
 * if lhs == rhs => return 0
 * if lhs < rhs => return -1
 */

int compareDates(std::chrono::system_clock::time_point lhs, std::chrono::system_clock::time_point rhs) { 

    if(lhs.time_since_epoch() < rhs.time_since_epoch()){
        return -1;
    } else if(lhs.time_since_epoch() == rhs.time_since_epoch()){
        return 0; 
    } else {
        return 1; 
    }

};

void printKey(std::chrono::system_clock::time_point tp) { 
    std::time_t time = std::chrono::system_clock::to_time_t(tp);
    auto tm = std::localtime(&time);
    char buffer[10];
    std::strftime(buffer, 10, "%Y-%m-%d", tm);
    std::cout << std::string(buffer) << std::endl;
};

Interface::Interface()
{
    this->indices = new std::map<int, std::vector<std::string> *>(); 
    this->columns = new std::map<std::string, int>(); 
}

Interface::~Interface()
{
    /* remove map, fs, b tree */ 
}

/*
 * main function that runs the interface
 */

void Interface::printInstructions()
{
    std::cout << "\n~~~~~~~~~~~~~~ INSTRUCTIONS ~~~~~~~~~~~~~~~\n" << std::endl; 
    std::cout << "COMMANDS: \n" << std::endl; 
    std::cout << "  1. SELECT <PK>, ..., <columnN> [WHERE <PK> = x]" << std::endl; 
    std::cout << "  2. INSERT (<PK>, ..., <columnN>) (<PK>, ..., <valueN>)" << std::endl; 
    std::cout << "  3. DELETE WHERE PK = x\n" << std::endl; 
}

void Interface::run()
{

    BTree<Interface::date_time> *btree = insertData(); 
    printInstructions(); 
    
    while(1)
    {
        char line[256]; 
        std::cin.getline(line, 256);
        std::string sLine = line; 
        std::string command = sLine.substr(0, sLine.find(" ")); 
        if(command != "SELECT" && command != "INSERT" && command != "DELETE")
        {
            std::cout << "That is not a valid command, please try again" << std::endl; 
            printInstructions(); 
        } else {

            // GET THE COLUMN NAME from the 



        }

    }
    

}

void select();

BTree<Interface::date_time>* Interface::insertData()
{

    char filename[256];
    // wait for a csv file 
    std::cout << "\nPlease enter a CSV file for table data: ";
    std::cin.getline(filename, 256); 
    std::string fName (filename);

    std::ifstream pFile; 
    pFile.open(filename); 

    while((fName.substr(fName.find('.'), 4)) != ".csv" || pFile.is_open() == false){

        if((fName.substr(fName.find('.'), 4)) != ".csv") {
            std::cout << "Must be a csv file (.csv), please enter another: ";
            std::cin.getline(filename, 256);
            fName = filename; 
            pFile.open(filename);
        }
        else if(pFile.is_open() == false) {
            std::cout << "Unknown file filename, please enter another: "; 
            std::cin.getline(filename, 256);
            fName = filename; 
            pFile.open(filename);
        }
    }
    
    // get header line
    std::string header; 
    getline(pFile, header); 

    std::cout << "COLUMN NAMES: " << header << std::endl; 

    size_t pos = 0; 
    int index = 0; 
    std::string token; 

    // get rid of the date value
    pos = header.find(','); 
    header.erase(0, pos+1); 

    while((pos = header.find(',')) != std::string::npos) {
        token = header.substr(0, pos);
        this->columns->operator[](token) = index; 
        header.erase(0, pos + 1);
        index++; 
    }
    
    std::string row; 
    BTree<Interface::date_time> *btree = new BTree<Interface::date_time>(3, &compareDates, &printKey); 
    
    while(getline(pFile, row))
    {
        std::string pk; 
        size_t pos = 0; 
        std::vector<std::string> *values = new std::vector<std::string>(); 
        // get the primary key pos[0]
        if((pos = row.find(',')) != std::string::npos) {
            pk = row.substr(0, pos);
            row.erase(0, pos+1);
        }
        
        // gets the rest of the row 
        std::string token; 
        while((pos = row.find(',')) != std::string::npos) {
            token = row.substr(0, pos);
            values->push_back(token); 
            row.erase(0, pos+1);
        }
        
        // convert the date into ymd format
        std::tm tm = {};
        std::istringstream ss(pk);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        Interface::date_time dt = std::chrono::system_clock::from_time_t(mktime(&tm));

        int index = btree->insert(dt); 
        indices->operator[](index) = values; 
    }
    return btree; 
}

std::string Interface::dateTimetoString(Interface::date_time date)
{
    std::time_t now_date = std::chrono::system_clock::to_time_t(date);
    auto tm = std::localtime(&now_date);
    char buffer[10];
    std::strftime(buffer, 10, "%Y-%m-%d", tm);
    return std::string(buffer); 
}