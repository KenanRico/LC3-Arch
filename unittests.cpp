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

void Instructions::TestNonTrap(Registers* registers, Memory* memory){
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
		LDR(0x0689, registers, memory);
		if(regs[Registers::R3]==0xabcd) {std::cout<<"LDR test#2 passed\n";} else {std::cout<<"LDR test#2 failed\n";}
		regs[Registers::R4] = 0x0500;
		regs[Registers::R5] = 0xffff;
		mem[0x0510] = 0xb00b;
		LDR(0x0b10, registers, memory);
		if(regs[Registers::R5]==0xb00b) {std::cout<<"LDR test#3 passed\n";} else {std::cout<<"LDR test#3 failed\n";}
	}
	/*STR*/
	{
		regs[Registers::R0] = 0x000f;
		regs[Registers::R1] = 0x9999;
		mem[0x0010] = 0xffff;
		STR(0x0201, registers, memory);
		if(mem[0x0010]==0x9999) {std::cout<<"STR test#1 passed\n";} else {std::cout<<"STR test#1 failed\n";}
		regs[Registers::R2] = 0x00aa;
		regs[Registers::R3] = 0xabcd;
		mem[0x00b3] = 0xffff;
		STR(0x0689, registers, memory);
		if(mem[0x00b3]==0xabcd) {std::cout<<"STR test#2 passed\n";} else {std::cout<<"STR test#2 failed\n";}
		regs[Registers::R4] = 0x0500;
		regs[Registers::R5] = 0xb00b;
		mem[0x0510] = 0xffff;
		STR(0x0b10, registers, memory);
		if(mem[0x0510]==0xb00b) {std::cout<<"STR test#3 passed\n";} else {std::cout<<"STR test#3 failed\n";}
	}

	/*NOT*/
	{
		regs[Registers::R0] = 0x1234;
		regs[Registers::R1] = 0xffff;
		NOT(0x0200, registers, memory);
		if(regs[Registers::R1]==0xedcb) {std::cout<<"NOT test#1 passed\n";} else {std::cout<<"NOT test#1 failed\n";}
		regs[Registers::R2] = 0x6666;
		regs[Registers::R3] = 0xffff;
		NOT(0x0680, registers, memory);
		if(regs[Registers::R3]==0x9999) {std::cout<<"NOT test#2 passed\n";} else {std::cout<<"NOT test#2 failed\n";}
		regs[Registers::R4] = 0x1337;
		regs[Registers::R5] = 0xffff;
		NOT(0x0b00, registers, memory);
		if(regs[Registers::R5]==0xecc8) {std::cout<<"NOT test#3 passed\n";} else {std::cout<<"NOT test#3 failed\n";}
	}

	/*LDI*/
	{
		uint16_t& pc = regs[Registers::PC];

		uint16_t& dr1 = regs[Registers::R1];
		dr1 = 0xffff;
		pc = 0x0100;
		mem[0x0101] = 0x0001;
		mem[0x0001] = 0x1234;
		LDI(0x0201, registers, memory);
		if(dr1==0x1234) {std::cout<<"LDI test#1 passed\n";} else {std::cout<<"LDI test#1 failed\n";}
		uint16_t& dr2 = regs[Registers::R2];
		dr2 = 0xffff;
		pc = 0x0100;
		mem[0x10f] = 0x0002;
		mem[0x0002] = 0x2345;
		LDI(0x040f, registers, memory);
		if(dr2==0x2345) {std::cout<<"LDI test#2 passed\n";} else {std::cout<<"LDI test#2 failed\n";}
		uint16_t& dr4 = regs[Registers::R4];
		dr4 = 0xffff;
		pc = 0x0100;
		mem[0x1ff] = 0x0003;
		mem[0x0003] = 0x3456;
		LDI(0x08ff, registers, memory);
		if(dr4==0x3456) {std::cout<<"LDI test#3 passed\n";} else {std::cout<<"LDI test#3 failed\n";}
	}

	/*STI*/
	{
		uint16_t& pc = regs[Registers::PC];

		regs[Registers::R1] = 0x1234;
		pc = 0x0100;
		mem[0x0101] = 0x0001;
		uint16_t& mem1 = mem[0x0001];
		mem1 = 0xffff;
		STI(0x0201, registers, memory);
		if(mem1==0x1234) {std::cout<<"STI test#1 passed\n";} else {std::cout<<"STI test#1 failed\n";}
		regs[Registers::R2] = 0x2345;
		pc = 0x0100;
		mem[0x10f] = 0x0002;
		uint16_t& mem2 = mem[0x0002];
		mem2 = 0xffff;
		STI(0x040f, registers, memory);
		if(mem2==0x2345) {std::cout<<"STI test#2 passed\n";} else {std::cout<<"STI test#2 failed\n";}
		regs[Registers::R4] = 0x3456;
		pc = 0x0100;
		mem[0x1ff] = 0x0003;
		uint16_t& mem3 = mem[0x0003];
		mem3 = 0xffff;
		STI(0x08ff, registers, memory);
		if(mem3==0x3456) {std::cout<<"STI test#3 passed\n";} else {std::cout<<"STI test#3 failed\n";}
	}

	/*JMP*/
	{
		uint16_t& pc = regs[Registers::PC];

		pc = 0x0000;
		regs[Registers::R0] = 0x6666;
		JMP(0x0000, registers, memory);
		if(0x6666) {std::cout<<"JMP test#1 passed\n";} else {std::cout<<"JMP test#1 failed\n";}
		pc = 0x0000;
		regs[Registers::R1] = 0xaaaa;
		JMP(0x0040, registers, memory);
		if(pc==0xaaaa) {std::cout<<"JMP test#2 passed\n";} else {std::cout<<"JMP test#2 failed\n";}
		pc = 0x0000;
		regs[Registers::R2] = 0x8888;
		JMP(0x0080, registers, memory);
		if(pc==0x8888) {std::cout<<"JMP test#3 passed\n";} else {std::cout<<"JMP test#3 failed\n";}
	}

	/*LEA*/
	{
		uint16_t& pc = regs[Registers::PC];
		
		pc = 0x1000;
		regs[Registers::R0] = 0x0000;
		LEA(0x0001, registers, memory);
		if(regs[Registers::R0]==0x1001) {std::cout<<"LEA test#1 passed\n";} else {std::cout<<"LEA test#1 failed\n";}
		pc = 0x2000;
		regs[Registers::R1] = 0x0000;
		LEA(0x020f, registers, memory);
		if(regs[Registers::R1]==0x200f) {std::cout<<"LEA test#2 passed\n";} else {std::cout<<"LEA test#2 failed\n";}
		pc = 0x3000;
		regs[Registers::R2] = 0x0000;
		LEA(0x04ff, registers, memory);
		if(regs[Registers::R2]==0x30ff) {std::cout<<"LEA test#3 passed\n";} else {std::cout<<"LEA test#3 failed\n";}
	}

}

void Instructions::TestTraps(Registers* registers, Memory* memory){

	Registers& regs = *registers;
	uint16_t& r0 = regs[Registers::R0];
	Memory& mem = *memory;

	/*GETC*/
	{
		r0 = 0xffff;
		TRAP(TrapRoutines::GETC, registers, memory);
		if(trap_routines.Status()==0){
			std::cout<<r0<<"\n";
		}else{
			std::cout<<"TRAP error: "<<trap_routines.BadTrapCode()<<"\n";
		}
	}

	/*OUT*/
	{
		r0 = '!';
		TRAP(TrapRoutines::OUT, registers, memory);
	}

	/*PUTS*/
	{
		r0 = 0x00aa;
		mem[r0] = 'h';
		mem[r0+1] = 'e';
		mem[r0+2] = 'l';
		mem[r0+3] = 'l';
		mem[r0+4] = 'o';
		mem[r0+5] = '\0';
		TRAP(TrapRoutines::PUTS, registers, memory);
		if(trap_routines.Status()!=0){
			std::cout<<"TRAP error: "<<trap_routines.BadTrapCode()<<"\n";
		}
	}

	/*IN*/
	{
		r0 = 0xffff;
		TRAP(TrapRoutines::IN, registers, memory);
	}

	/*PUTSP*/
	{
		r0 = 0x00aa;
		char* c = (char*)&mem[r0];
		*c = 'a';
		*(c+1) = 'p';
		*(c+2) = 'p';
		*(c+3) = 'l';
		*(c+4) = 'e';
		*(c+5) = '\0';
		TRAP(TrapRoutines::PUTSP, registers, memory);
		if(trap_routines.Status()!=0){
			std::cout<<"TRAP error: "<<trap_routines.BadTrapCode()<<"\n";
		}

	}

}
