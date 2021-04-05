#include "interface.hpp"
#include "TextTable.hpp"
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
    char buffer[20];
    std::strftime(buffer, 20, "%d-%m-%Y", tm);
    std::cout << std::string(buffer); 
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
    std::cout << "  1. SELECT <PK>, ..., <columnN> FROM table [WHERE <PK> = x]" << std::endl; 
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
            if(command == "SELECT"){
                select(sLine, btree); 
            } else if(command == "INSERT") {
                insert(sLine, btree); 
            } else if(command == "DELETE") {
                remove(sLine, btree); 
            }

        }

    }

}

void Interface::select(std::string line, BTree<Interface::date_time> *btree)
{
    // match as many words with the columns
    std::vector<std::string> validColumns; 
    std::vector<int> validIndices; 
    std::string lineCopy = line.substr(0, line.find("FROM table")); 

    if(lineCopy.find('*') != std::string::npos)
    {
        // all the columns 
        auto it = columns->begin(); 
        for(; it != columns->end(); it++)
        {
            validColumns.push_back(it->first); 
            validIndices.push_back(it->second); 
        }

    } else {
        // match the column names
        // split the string based on " "
        size_t pos = 0; 
        std::string token; 
        while ((pos = lineCopy.find(' ')) != std::string::npos) {
            token = lineCopy.substr(0, pos);
            if(token.at(token.length() - 1) == ',' || token.at(token.length() - 1) == ' ') {
                token.erase(token.size() - 1); 
            }
            if(columns->find(token) != columns->end()) {
                validColumns.push_back(token); 
                validIndices.push_back(columns->operator[](token)); 
            }
            lineCopy.erase(0, pos + 1);
        }
    }
    
    // parse second part - where clause filter
    std::set<Interface::date_time> dates;  

    size_t pos = 0; 
    if ((pos = line.find("WHERE")) != std::string::npos) {
        std::vector<std::string> tokens; 
        lineCopy = line.substr(pos + 5, line.size() - 1);
	    std::string token; 
        while((pos = lineCopy.find(' ')) != std::string::npos) {
            token = lineCopy.substr(0, pos); 
            tokens.push_back(token); 
            lineCopy.erase(0, pos+1); 
        }
        if(lineCopy[lineCopy.length() - 1] == '\n') {
            lineCopy.erase(lineCopy.length() - 1); 
        }; 
        tokens.push_back(lineCopy); 
        auto it = tokens.begin(); 
        while (it != tokens.end()) {
            if((*it) == "=") {
                std::string value = *(it + 1); 
                std::tm tm = {};
                std::istringstream ss(value);
                ss >> std::get_time(&tm, "%d-%m-%Y");
                Interface::date_time dt = std::chrono::system_clock::from_time_t(timegm(&tm));
                dates.insert(dt); 
            }
            it++; 
        }
    }
    
    // output a structure that can then be easily printed
    std::vector<std::vector<std::string>> outputVals; 

    // actually select the elements - if there is no where filter - only shows 50
    if(dates.size() == 0)
    {
        auto it = indices->begin(); 
        for(int count = 0; count < 50; count++) {
            std::vector<std::string> tempValues;  
            std::vector<std::string> curVals = *it->second; 

            int i = 0; 
            while(i < validIndices.size()) {
                std::string value = curVals[validIndices[i]]; 
                tempValues.push_back(value);
                i++; 
            }
            outputVals.push_back(tempValues); 
            it++; 
        }
        // return all the elements - i.e. just print all the indices from the map
    }
    else {
        // get the map index of the elem and then return info 
        auto it = dates.begin(); 
        for(; it != dates.end(); it++) {

            BNodeKey<Interface::date_time> *bKey = btree->search(*it); 
            if(bKey != nullptr) {
                int index = bKey->index; 
                std::vector<std::string> tempValues; 
                std::vector<std::string> *values = indices->operator[](index); 
                for(auto it = values->begin(); it != values->end(); it++) {
                    std::cout << *it << std::endl;
                }
                // only select the valid columns
                int i = 0; 
                while(i < validIndices.size()) {
                    std::cout << "valid index: " << validIndices[i] << std::endl; 
                     std::string value = values->operator[](validIndices[i]);
                    tempValues.push_back(value); 
                    i++; 
                }
                outputVals.push_back(tempValues); 
            }
        } 
    }

    printSelect(validColumns, outputVals); 
    
}

void Interface::insert(std::string line, BTree<Interface::date_time> *btree)
{   
    // std::vector<std::string> validColumns; 
    // std::vector<int> validIndices;     
    
    // std::string chosenColumns = line.substr(line.find('('), line.find(')')); 
    // while ((pos = chosenColumns.find(',')) != std::string::npos) {
    //     token = chosenColumns.substr(0, pos);
    //     if(token.at(token.length() - 1) == ',') {
    //         token.erase(token.size() - 1); 
    //     }
    //     if(columns->find(token) != columns->end()) {
    //         validColumns.push_back(token); 
    //         validIndices.push_back(columns->operator[](token)); 
    //     }
    //     chosenColumns.erase(0, pos + 1);
    // }
    // validColumns.push_back(chosenColumns)

}   

void Interface::remove(std::string line, BTree<Interface::date_time> *btree)
{

}

void Interface::printSelect(std::vector<std::string> columns, std::vector<std::vector<std::string>> values) 
{
    TextTable t( '-', '|', '+' );
    // adding the header rows
    auto columnIt = columns.begin(); 
    while(columnIt != columns.end())
    {
        std::cout << *columnIt << std::endl; 
        t.add(*columnIt); 
        columnIt++; 
    }
    t.endOfRow(); 

    // adding the values
    auto valueIt = values.begin(); 
    while(valueIt != values.end()){
        std::vector<std::string> row = *valueIt; 
        auto rowIt = row.begin(); 
        while(rowIt != row.end()) {
            t.add(*rowIt); 
            rowIt++; 
        }
        t.endOfRow(); 
        valueIt++; 
    }
    t.setAlignment( 2, TextTable::Alignment::RIGHT );
    std::cout << t; 
}

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
    size_t last = 0; 
    int index = 0; 
    std::string token; 

    while((pos = header.find(',', last)) != std::string::npos) {
        token = header.substr(last, pos-last);
        this->columns->operator[](token) = index;
        last = pos + 1;  
        index++; 
    }
    pos = header.length()-1;
    token = header.substr(last, pos - last);
    this->columns->operator[](token) = index; 
    
    for(auto it = columns->begin(); it != columns->end(); it++){
        std::cout << it->first << ", " << it->second << std::endl; 
    }

    std::string row; 
    BTree<Interface::date_time> *btree = new BTree<Interface::date_time>(3, &compareDates, &printKey); 
    
    while(getline(pFile, row))
    {
        std::string pk; 
        size_t pos = 0; 
        std::vector<std::string> *stringVal = new std::vector<std::string>(); 
        // get the primary key pos[0]
        if((pos = row.find(',')) != std::string::npos) {
            pk = row.substr(0, pos);
            row.erase(0, pos+1);
        }
	    stringVal->push_back(pk);         
        // gets the rest of the row 
        std::string token; 
        while((pos = row.find(',')) != std::string::npos) {
            token = row.substr(0, pos);
            stringVal->push_back(token); 
            row.erase(0, pos+1);
        }
        if(row[row.length() - 1] == '\n') {
            row.erase(row.length() - 1); 
        }
        stringVal->push_back(row); 
        // convert the date into ymd format
        std::tm tm = {};
        std::istringstream ss(pk);
        ss >> std::get_time(&tm, "%d-%m-%Y");
        Interface::date_time dt = std::chrono::system_clock::from_time_t(timegm(&tm));
        int index = btree->insert(dt); 
        indices->operator[](index) = stringVal; 
    }
    return btree; 
}

std::string Interface::dateTimetoString(Interface::date_time date)
{
    std::time_t now_date = std::chrono::system_clock::to_time_t(date);
    auto tm = std::localtime(&now_date);
    char buffer[20];
    std::strftime(buffer, 20, "%d-%m-%Y", tm);
    return std::string(buffer); 
}
