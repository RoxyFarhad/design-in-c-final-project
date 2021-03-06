
**Properties of B-Tree**\
B-Tree of Order m has the following properties:
- Property #1 - All the leaf nodes must be at same level.
- Property #2 - All nodes except root must have at least [m/2]-1 keys and maximum of m-1 keys.
- Property #3 - All non leaf nodes except root (i.e. all internal nodes) must have at least m/2 children.
- Property #4 - If the root node is a non leaf node, then it must have at least 2 children.
- Property #5 A non leaf node with n-1 keys must have n number of children.
- Property #6 -All the key values within a node must be in ascending order.

- The root has to have between 1 and 2m-1 elements
- Non-root nodes are m and 2m elements


**B-Tree-Node**

Simple Approach:
first row in each node is an array of records containing key and associated data
second row in each node is an array of pointers to child nodes

Another Approach:
first row contain an array of records each containing a key and a record number for the data record, which is found in another file
useful for very large data records


<img src="https://cis.stvincent.edu/html/tutorials/swd/btree/multiway.gif" width="800">

Usually in a database, the Btree would store the (key, index) together with the index pointing to a value in a b+ tree. 
For this data, we will use a hashmap in the place of b+ tree to store the indexes as a result of a time constraint. (performs the insert/delete in O(1) time and then a search in O(n))

```
struct BTreeNode
{
    int count // number of keys stored in the current Node
    keys[m-1] // array to hold the keys 
    records[m] //array of record numbers (pointers to child nodes)

}
``` 

The BtreeNode has a struct that represents a "key": 
- the key then is of a certain type, which is predefined by a user. 
- e.g. could be string for country, or 


Insert function:
1. if the root is full:
        1. create a new node and make that the root 
        2. new node is not a leaf
        3. root node is currently the child of new node 
        -> then have to split the node
        

- looking at underlying datastructures in the container and see how by changing the structure it affects the runtime of the methods: INSERT, SELECT, REMOVE

SELECT METHOD:
1. returns all the elements (only top 50 shown on screen for simplicity)
2. if there is a where clause then only select that element

