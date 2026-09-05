CXX = gcc
TARGET = ./build/compiler

all: $(TARGET)

$(TARGET): compiler.c
	mkdir build
	$(CXX) compiler.c -o $(TARGET) 

.PHONY: clean

clean:
	rm -rf ./build
