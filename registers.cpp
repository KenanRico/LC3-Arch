#include "registers.h"

#include <stdint.h>
#include <iostream>



Registers::Registers(){

}

Registers::~Registers(){

}

uint16_t Registers::GetIncPC(){
	return reg[PC]++;
}

uint16_t& Registers::operator[](int i){
	return reg.at(i);
}

void Registers::UpdateFlag(int i){
	if(reg[i]==0){
		reg[COND] = COND_ZRO; 
	}else if(reg[i]>>15){
		reg[COND] = COND_NEG; 
	}else{
		reg[COND] = COND_POS; 
	}
}

void Registers::PrintContent() const{
	for(int i=0; i<count; ++i){
		std::cout<<reg[i]<<" ";
	}
	std::cout<<"\n";
}
