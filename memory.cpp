#include "memory.h"

#include <stdint.h>
#include <iostream>



Memory::Memory(){

}

Memory::~Memory(){

}

void Memory::PrintContent() const{
	for(int i=0; i<size; ++i){
		std::cout<<memory[i]<<" ";
	}
	std::cout<<"\n";
}
