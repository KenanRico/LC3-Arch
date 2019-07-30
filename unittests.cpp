#include "registers.h"
#include "memory.h"
#include "instructions.h"

#include <iostream>


void Registers::TestAll(){
	std::cout<<"========================Starting register tests...========================\n";

}

void Memory::TestAll(){
	std::cout<<"========================Starting memory tests...========================\n";

}

void Instructions::TestAll(Registers* registers, Memory* memory){
	std::cout<<"========================Starting instruction tests...========================\n";
	Registers& regs = *registers;
	Memory& mem = *memory;
	/*BR*/
	{
		regs[Registers::COND] = Registers::COND_POS;//...001
		regs[Registers::PC] = 0x0000;
		BR(0x020f, registers, memory); if(regs[Registers::PC]==0x000f) { std::cout<<"BR test#1 passed\n"; } else { std::cout<<"BR test#1 failed\n"; }
		regs[Registers::COND] = Registers::COND_ZRO; //...010
		regs[Registers::PC] = 0x0000;
		BR(0x040f, registers, memory); if(regs[Registers::PC]==0x000f) { std::cout<<"BR test#2 passed\n"; } else { std::cout<<"BR test#2 failed\n"; }
		regs[Registers::COND] = Registers::COND_NEG; //...100
		regs[Registers::PC] = 0x0000;
		BR(0x080f, registers, memory); if(regs[Registers::PC]==0x000f) { std::cout<<"BR test#3 passed\n"; } else { std::cout<<"BR test#3 failed\n"; }
	}
	/*LD*/
	{
		regs[Registers::PC] = 0x0000;
		regs[Registers::R0] = 0x0000;
		LD(0x0000, registers, memory);
		if(regs[Registers::R0]==mem[regs[Registers::PC]+0x0000]) { std::cout<<"LD test#1 passed\n"; } else { std::cout<<"LD test#1 failed\n"; }
		regs[Registers::PC] = 0x0000;
		regs[Registers::R1] = 0x0000;
		LD(0x020f, registers, memory);
		if(regs[Registers::R1]==mem[regs[Registers::PC]+0x000f]) { std::cout<<"LD test#2 passed\n"; } else { std::cout<<"LD test#2 failed\n"; }
		regs[Registers::PC] = 0x0000;
		regs[Registers::R2] = 0x0000;
		LD(0x04ff, registers, memory);
		if(regs[Registers::R2]==mem[regs[Registers::PC]+0x00ff]) { std::cout<<"LD test#3 passed\n"; } else { std::cout<<"LD test#3 failed\n"; }
	}
	/*ST*/
	{
		regs[Registers::PC] = 0x0000;
		regs[Registers::R7] = 0x0000;
		ST(0x????, registers, memory);
		if(mem[]==regs[]) {} else {}
	}
}
