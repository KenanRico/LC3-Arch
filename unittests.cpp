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
		regs[Registers::PC] = 0xffff;
		regs[Registers::R0] = 0xffff;
		LD(0x0000, registers, memory);
		if(regs[Registers::R0]==mem[regs[Registers::PC]+sign_extend(0x0000, 9)]){
			std::cout<<"LD test#1 passed\n";
		}else{
			std::cout<<"LD test#1 failed\n";
		}
		regs[Registers::PC] = 0x0000;
		regs[Registers::R1] = 0x0000;
		LD(0x020f, registers, memory);
		if(regs[Registers::R1]==mem[regs[Registers::PC]+sign_extend(0x000f, 9)]){
			std::cout<<"LD test#2 passed\n";
		}else{
			std::cout<<"LD test#2 failed\n";
		}
		regs[Registers::PC] = 0x0000;
		regs[Registers::R2] = 0x0000;
		LD(0x04ff, registers, memory);
		if(regs[Registers::R2]==mem[regs[Registers::PC]+sign_extend(0x00ff, 9)]){
			std::cout<<"LD test#3 passed\n";
		}else{
			std::cout<<"LD test#3 failed\n";
		}
	}
	/*ST*/
	{
		regs[Registers::PC] = 0xf000;
		regs[Registers::R7] = 0xf000;
		ST(0x0e00, registers, memory);
		if(mem[regs[Registers::PC]+sign_extend(0x0000, 9)]==regs[Registers::R7]){
			std::cout<<"ST test#1 passed\n";
		}else{
			std::cout<<"ST test#1 failed\n";
		}
		regs[Registers::PC] = 0xffff;
		regs[Registers::R6] = 0xffff;
		ST(0x0c0f, registers, memory);
		if(mem[regs[Registers::PC]+sign_extend(0x000f, 9)]==regs[Registers::R6]){
			std::cout<<"ST test#2 passed\n";
		}else{
			std::cout<<"ST test#2 failed\n";
		}
		regs[Registers::PC] = 0xffff;
		regs[Registers::R5] = 0xffff;
		ST(0x0aff, registers, memory);
		if(mem[regs[Registers::PC]+sign_extend(0x00ff, 9)]==regs[Registers::R5]){
			std::cout<<"ST test#3 passed\n";
		}else{
			std::cout<<"ST test#3 failed\n";
		}
	}
	/*JSR*/
	{
		regs[Registers::PC] = 0x0001;
		JSR(0x080f, registers, memory);
		if(regs[Registers::PC]==0x0010) {std::cout<<"JSR test#1 passed\n";} else {std::cout<<"JSR test#1 failed\n";}
		regs[Registers::PC] = 0x0001;
		JSR(0x09ff, registers, memory);
		if(regs[Registers::PC]==0x0200) {std::cout<<"JSR test#2 passed\n";} else {std::cout<<"JSR test#2 failed\n";}
		regs[Registers::PC] = 0xffff;
		regs[Registers::R0] = 0xaaaa;
		JSR(0x0000, registers, memory);
		if(regs[Registers::PC]==0xaaaa) {std::cout<<"JSRR test#1 passed\n";} else {std::cout<<"JSRR test#1 failed\n";}
		regs[Registers::PC] = 0xffff;
		regs[Registers::R7] = 0xabcd;
		JSR(0x01c0, registers, memory);
		if(regs[Registers::PC]==0xabcd) {std::cout<<"JSRR test#2 passed\n";} else {std::cout<<"JSRR test#2 failed\n";}
	}
	/*LDR*/
	{
		regs[Registers::R0] = 0x000f;
		regs[Registers::R1] = 0xffff;
		mem[0x0010] = 0x9999;
		LDR(0x0201, registers, memory);
		if(regs[Registers::R1]==0x9999) {std::cout<<"LDR test#1 passed\n";} else {std::cout<<"LDR test#1 failed\n";}
		regs[Registers::R2] = 0x00aa;
		regs[Registers::R3] = 0xffff;
		mem[0x00b3] = 0xabcd;
		LDR(0x0609, registers, memory);
		if(regs[Registers::R3]==0xabcd) {std::cout<<"LDR test#2 passed\n";} else {std::cout<<"LDR test#2 failed\n";}
		regs[Registers::R4] = 0x0500;
		regs[Registers::R5] = 0xffff;
		mem[0x0520] = 0xb00b;
		LDR(0x0b20, registers, memory);
		if(regs[Registers::R5]==0xb00b) {std::cout<<"LDR test#3 passed\n";} else {std::cout<<"LDR test#3 failed\n";}
	}
}
