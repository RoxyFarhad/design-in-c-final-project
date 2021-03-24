CC = g++ -std=c++17

CFLAGS = -g -Wall

TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).o btree.o
			$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o btree.o

$(TARGET).o: $(TARGET).cpp btree.hpp
	$(CC) $(CFLAGS) -c $(TARGET).cpp

btree.o: btree.cpp btree.hpp node.o
	$(CC) $(CFLAGS) -c btree.cpp

node.o: node.hpp

