CXX = gcc
TARGET = ./build/compiler

all: $(TARGET)

$(TARGET): compiler.c
	mkdir build
	$(CXX) compiler.c -o $(TARGET) 
	mv $(TARGET) ./compiler
	rm -rf ./build
.PHONY: clean

clean:
	rm -rf ./build
