#include "memory.h"

#include <stdint.h>
#include <iostream>



Memory::Memory(){

}

Memory::~Memory(){

}

uint16_t& Memory::operator[](int i){
	return memory.at(i);
}

void Memory::PrintContent() const{
	for(int i=0; i<size; ++i){
		std::cout<<memory[i]<<" ";
	}
	std::cout<<"\n";
}
