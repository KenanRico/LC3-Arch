CC = g++

lc3make: *.cpp
	$(CC) unittests.cpp platform.cpp main.cpp memory.cpp instructions.cpp registers.cpp traproutines.cpp -o lc3 -std=c++17

