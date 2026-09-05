CXX = gcc
TARGET = compiler

all: $(TARGET)

$(TARGET): compiler.o
	$(CXX) -o $(TARGET) compiler.o 

compiler.o: compiler.c
	$(CXX) -c compiler.c

.PHONY: clean

clean:
	rm -f *.o $(TARGET)
