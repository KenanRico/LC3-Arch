#include "instructions.h"
#include "registers.h"
#include "memory.h"

#include <stdint.h>


#include <iostream>
Instructions::Instructions():
inst(
	{
		&Instructions::BR,
		&Instructions::ADD,
		&Instructions::LD,
		&Instructions::ST,
		&Instructions::JSR,
		&Instructions::AND,
		&Instructions::LDR,
		&Instructions::STR,
		&Instructions::RTI,
		&Instructions::NOT,
		&Instructions::LDI,
		&Instructions::STI,
		&Instructions::JMP,
		&Instructions::RES,
		&Instructions::LEA,
		&Instructions::TRAP
	}
){
	for(int i=0; i<=16; ++i){
		mask[16-i] = 0xffff>>i;
	}
}

Instructions::~Instructions(){

}

void Instructions::Parse(uint16_t instruction, uint16_t* op, uint16_t* params) const{
	*op = (instruction>>12) & mask[4];
	*params = instruction & mask[12];
}

bool Instructions::Execute(uint16_t op, uint16_t params, Registers* reg, Memory* mem) const{
	bool result = true;
	if(op<count){
		(this->*inst[op])(params, reg, mem);
	}else{
		result = false;
	}
	return result;
}


/*------------------------------------------------ Instruction implementation -------------------------------------------------*/

/*
 *Sign extend helper func
 */
uint16_t sign_extend(uint16_t val, int bit_count){
	if ((val >> (bit_count - 1)) & 1) {
		val |= (0xFFFF << bit_count);
	}
	return val;
}


uint16_t Instructions::BR(uint16_t, Registers*, Memory*) const{

}

uint16_t Instructions::ADD(uint16_t params, Registers* registers, Memory* memory) const{
	Registers& reg = *registers;
	uint16_t dr = params>>9 & mask[3];
	uint16_t sr1 = params>>6 & mask[3];
	if(params>>6 & mask[1]){
		/*immediate mode*/
		uint16_t imm5 = sign_extend(params & mask[5], 5);
		reg[dr] = reg[sr1] + imm5;
	}else{
		/*reg mode*/
		uint16_t sr2 = params & mask[3];
		reg[dr] = reg[sr1] + reg[sr2];
	}
	return 0;
	//UpdateFlag(dr);
}

uint16_t Instructions::LD(uint16_t params, Registers* registers, Memory* memory) const{
	uint16_t offset = params & mask[9];
	uint16_t dr = (params>>9) & mask[3];
	Registers& reg = *registers;
	Memory& mem = *memory;
	reg[dr] = mem[reg[Registers::PC]+offset];
}

uint16_t Instructions::ST(uint16_t, Registers*, Memory*) const{

}

uint16_t Instructions::JSR(uint16_t params, Registers* registers, Memory* memory) const{
	Registers& reg = *registers;
	Memory& mem = *memory;
	if(params>>11 & mask[1]){
		//JSR
		reg[Registers::R7] = reg[Registers::PC] + 1;
		uint16_t offset = sign_extend(params&mask[11], 11);
		reg[Registers::PC] += offset;
	}else{
		//JSRR
		uint16_t base_reg = params>>6 & mask[3];
		reg[Registers::PC] = reg[base_reg];
	}
}

uint16_t Instructions::AND(uint16_t params, Registers*, Memory*) const{
#ifdef INST_IMPL
	uint16_t DR = params>>9;
	uint16_t SR1 = params>>6 & 0x0007;
	if(params & 0x0020){
		/*immediate mode*/
		uint16_t imm5 = sign_extend(params & 0x001f, 5);
		System::reg[DR] = System::reg[SR1] & imm5;
	}else{
		/*reg mode*/
		uint16_t SR2 = params & 0x0007;
		System::reg[DR] = System::reg[SR1] & System::reg[SR2];
	}
#endif
}

uint16_t Instructions::LDR(uint16_t params, Registers*, Memory*) const{
#ifdef INST_IMPL
	uint16_t sr = (params>>6) & 0x0007;
	uint16_t offset = params & 0x001f;
	uint16_t dr = () & 0x0007
#endif
}

uint16_t Instructions::STR(uint16_t, Registers*, Memory*) const{

}

uint16_t Instructions::RTI(uint16_t, Registers*, Memory*) const{

}

uint16_t Instructions::NOT(uint16_t, Registers*, Memory*) const{

}

uint16_t Instructions::LDI(uint16_t, Registers*, Memory*) const{
#ifdef INST_IMPL
	uint16_t offset = params & 0x01ff;
	uint16_t dr = (params>>9) & 0x0007;
	System::reg[dr] = System::memory[System::memory[System::reg[REG_PC]+offset]];
#endif
}

uint16_t Instructions::STI(uint16_t, Registers*, Memory*) const{

}

uint16_t Instructions::JMP(uint16_t params, Registers*, Memory*) const{
#ifdef INST_IMPL
	uint16_t base_reg = params>>6 & 0x0007;
	System::reg[System::REG_PC] = System::reg[base_reg];
#endif
}

uint16_t Instructions::RES(uint16_t, Registers*, Memory*) const{

}

uint16_t Instructions::LEA(uint16_t, Registers*, Memory*) const{

}

uint16_t Instructions::TRAP(uint16_t, Registers*, Memory*) const{

}

