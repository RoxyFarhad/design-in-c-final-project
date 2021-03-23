
**Properties of B-Tree**
B-Tree of Order m has the following properties:
All the leaf nodes must be at same level.
All nodes except root must have at least [m/2]-1 keys and maximum of m-1 keys.
All non leaf nodes except root (i.e. all internal nodes) must have at least m/2 children.
If the root node is a non leaf node, then it must have at least 2 children.
A non leaf node with n-1 keys must have n number of children.
All the key values within a node must be in ascending order.


**B-Tree-Node**

Simple Approach:
first row in each node is an array of records containing key and associated data
second row in each node is an array of pointers to child nodes

Another Approach:
first row contain an array of records each containing a key and a record number for the data record, which is found in another file
useful for very large data records


<img src="https://cis.stvincent.edu/html/tutorials/swd/btree/multiway.gif" width="800">


```
struct BTreeNode
{
    int count // number of keys stored in the current Node
    keys[m-1] // array to hold the keys 
    records[m] //array of record numbers (pointers to child nodes)

}
``` 









