#ifndef BTREE_NODE_H
#define BTREE_NODE_H

#include <string>

using namespace std; 
namespace btree
{   

    class Node
    {

        public:

            // constructor
            Node ( ); 
            ~Node( ) = default; 

            string date; 
            int temperature;

            bool isLeaf; 
            size_t max_val_count; 
            size_t min_val_count; 
            size_t val_count; 

            // initialises the node
            void init(Node *parent, size_t max_val_count);

            // following properties of nodes https://www.programiz.com/dsa/b-tree


        // public methods
        public:

            void Node::init(Node *parent, size_t max_val_count, string date, int temperature)
            {
                this->isLeaf = true; 
                this->max_val_count = max_val_count; 
                this->val_count = 0; 
                this->parent = parent;
                this->date = date;
                this->temperature = temperature; 
            }

        friend class Btree; 

    }   
}