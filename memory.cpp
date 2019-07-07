#include "memory.h"

#include <stdint.h>



Memory::Memory(){

}

Memory::~Memory(){

}

uint16_t Memory::Read(uint16_t i) const{
	return memory[i];
}

void Memory::Write(uint16_t i, uint16_t v){
	memory[i] = v;
}

const std::array<uint16_t, Memory::size>& Memory::Content() const{
	return memory;
}
