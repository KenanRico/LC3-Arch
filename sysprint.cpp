#include "sysprint.h"
#include "registers.h"
#include "memory.h"

#include <iostream>


void Print(const Registers& registers){
	std::cout<<"Registers:\n";
	for(int i=0; i<registers.count; ++i){
		std::cout<<registers.Content()[i]<<" ";
	}
	std::cout<<"\n";
}

void Print(const Memory& memory){
	std::cout<<"Memory:\n";
	for(int i=0; i<memory.size; ++i){
		std::cout<<memory.Content()[i]<<" ";
	}
	std::cout<<"\n";
}
