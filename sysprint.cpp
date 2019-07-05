#include "sysprint.h"
#include "system.h"

#include <iostream>


void PrintRegs(){
	std::cout<<"Registers:\n";
	for(int i=0; i<REG_COUNT; ++i){
		std::cout<<System::reg[i]<<" ";
	}
	std::cout<<"\n";
}

void PrintMem(){
	std::cout<<"Memory:\n";
	for(int i=0; i<RAM_UNIT_COUNT; ++i){
		std::cout<<System::memory[i]<<" ";
	}
	std::cout<<"\n";
}
