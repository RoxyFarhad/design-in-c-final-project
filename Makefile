CC = g++ -std=c++2a

CFLAGS = -g -Wall

TARGET = main
TEST = test
UNIT_TEST = unit_test

all: $(TARGET) $(TEST) $(UNIT_TEST)

$(TARGET): $(TARGET).o
			$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(UNIT_TEST): $(UNIT_TEST).o
			$(CC) $(CFLAGS) -o $(UNIT_TEST) $(UNIT_TEST).o

$(TEST): $(TEST).o
			$(CC) $(CFLAGS) -o $(TEST) $(TEST).o

$(TARGET).o: $(TARGET).cpp interface.cpp interface.o
			$(CC) $(CFLAGS) -c $(TARGET).cpp

$(TEST).o: $(TEST).cpp btree.o
			$(CC) $(CFLAGS) -c $(TEST).cpp

$(UNIT_TEST).o: $(UNIT_TEST).cpp btree.o
			$(CC) $(CFLAGS) -c $(UNIT_TEST).cpp

interface.o: interface.cpp interface.hpp TextTable.hpp btree.o
	$(CC) $(CFLAGS) -c interface.cpp

btree.o: btree.cpp btree.hpp node.o
	$(CC) $(CFLAGS) -c btree.cpp

node.o: node.hpp

clean:
	rm -f *~ *.o main test unit_test
