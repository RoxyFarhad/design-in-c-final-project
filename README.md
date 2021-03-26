

Dependency Structure:
    - main : main.o btree.o
    - main.o: main.cpp 
    - main.cpp: btree.h
    - btree.o: btree.cpp node.h
    - node.o: node.cpp node.h 

btree.cpp: for the methods of btree
btree.hpp: header file for btree
node.cpp: methods for cpp
node.hpp: header for cpp

