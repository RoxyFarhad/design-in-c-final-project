CC = g++ -std=c++17

CFLAGS = -g -Wall

TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).o
			$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: $(TARGET).cpp interface.cpp interface.o
			$(CC) $(CFLAGS) -c $(TARGET).cpp

interface.o: interface.cpp interface.hpp btree.o
	$(CC) $(CFLAGS) -c interface.cpp

btree.o: btree.cpp btree.hpp node.o
	$(CC) $(CFLAGS) -c btree.cpp

node.o: node.hpp

clean:
	rm -f *~ *.o main