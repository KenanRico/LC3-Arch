#include "registers.h"

#include <stdint.h>



Registers::Registers(){

}

Registers::~Registers(){

}

uint16_t Registers::GetIncPC(){
	return reg[PC]++;
}

uint16_t Registers::Read(int i) const{
	return reg.at(i);
}

void Registers::Write(int i, uint16_t val){
	reg.at(i) = val;
}

const std::array<uint16_t, Registers::count>& Registers::Content() const{
	return reg;
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
