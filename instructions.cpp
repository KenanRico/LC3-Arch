#include "instructions.h"
#include "registers.h"
#include "memory.h"
#include "traproutines.h"

#include <stdint.h>

#define OK 0
#define BAD_OP_CODE 1
#define BAD_TRAP_CODE 2
#define TRAP_HALT 3
#define TRAP_FAULT 4

Instructions::Instructions(): status(OK){
	inst[OP_BR] = &Instructions::BR;
	inst[OP_ADD] = &Instructions::ADD;
	inst[OP_LD] = &Instructions::LD;
	inst[OP_ST] = &Instructions::ST;
	inst[OP_JSR] = &Instructions::JSR;
	inst[OP_AND] = &Instructions::AND;
	inst[OP_LDR] = &Instructions::LDR;
	inst[OP_STR] = &Instructions::STR;
	inst[OP_RTI] = &Instructions::RTI;
	inst[OP_NOT] = &Instructions::NOT;
	inst[OP_LDI] = &Instructions::LDI;
	inst[OP_STI] = &Instructions::STI;
	inst[OP_JMP] = &Instructions::JMP;
	inst[OP_RES] = &Instructions::RES;
	inst[OP_LEA] = &Instructions::LEA;
	inst[OP_TRAP] = &Instructions::TRAP;
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

bool Instructions::Execute(uint16_t op, uint16_t params, Registers* reg, Memory* mem){
	bool result = true;
	if(op<count && op!=OP_RTI && op!=OP_RES){
		int update_reg = (this->*inst[op])(params, reg, mem);
		if(update_reg>=0){
			reg->UpdateFlag(update_reg);
		}
	}else{
		result = false;
		status = BAD_OP_CODE;
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


int Instructions::BR(uint16_t params, Registers* registers, Memory* memory){
	Registers& reg = *registers;
	uint16_t cond_flag = params>>9 & mask[3];
	uint16_t offset = sign_extend(params & mask[9], 9);
	if(cond_flag & reg[Registers::COND]){
		reg[Registers::PC] += offset;
	}
	return -1;
}

int Instructions::ADD(uint16_t params, Registers* registers, Memory* memory){
	Registers& reg = *registers;
	uint16_t dr = params>>9 & mask[3];
	uint16_t sr1 = params>>6 & mask[3];
	if(params>>5 & mask[1]){
		/*immediate mode*/
		uint16_t imm5 = sign_extend(params & mask[5], 5);
		reg[dr] = reg[sr1] + imm5;
	}else{
		/*reg mode*/
		uint16_t sr2 = params & mask[3];
		reg[dr] = reg[sr1] + reg[sr2];
	}
	return dr;
}

int Instructions::LD(uint16_t params, Registers* registers, Memory* memory){
	Registers& reg = *registers;
	Memory& mem = *memory;
	uint16_t offset = sign_extend(params & mask[9], 9);
	uint16_t dr = (params>>9) & mask[3];
	reg[dr] = mem.Read(reg[Registers::PC]+offset);
	return dr;
}

int Instructions::ST(uint16_t params, Registers* registers, Memory* memory){
	Registers& reg = *registers;
	Memory& mem = *memory;
	uint16_t sr = params>>9 & mask[3];
	uint16_t offset = sign_extend(params&mask[9], 9);
	mem.Write(reg[Registers::PC]+offset, reg[sr]);
	return -1;
}

int Instructions::JSR(uint16_t params, Registers* registers, Memory* memory){
	Registers& reg = *registers;
	reg[Registers::R7] = reg[Registers::PC];
	if(params>>11 & mask[1]){
		//JSR
		uint16_t offset = sign_extend(params&mask[11], 11);
		reg[Registers::PC] += offset;
	}else{
		//JSRR
		uint16_t base_reg = params>>6 & mask[3];
		reg[Registers::PC] = reg[base_reg];
	}
	return -1;
}

int Instructions::AND(uint16_t params, Registers* registers, Memory* memory){
	Registers& reg = *registers;
	uint16_t dr = params>>9 & mask[3];
	uint16_t sr1 = params>>6 & mask[3];
	if(params>>5 & mask[1]){
		/*immediate mode*/
		uint16_t imm5 = sign_extend(params & mask[5], 5);
		reg[dr] = reg[sr1] & imm5;
	}else{
		/*reg mode*/
		uint16_t sr2 = params & mask[3];
		reg[dr] = reg[sr1] & reg[sr2];
	}
	return dr;
}

int Instructions::LDR(uint16_t params, Registers* registers, Memory* memory){
	Registers& reg = *registers;
	Memory& mem = *memory;
	uint16_t sr = (params>>6) & mask[3];
	uint16_t offset = sign_extend(params&mask[6], 6);
	uint16_t dr = (params>>9) & mask[3];
	reg[dr] = mem.Read(reg[sr]+offset);
	return dr;
}

int Instructions::STR(uint16_t params, Registers* registers, Memory* memory){
	Registers& reg = *registers;
	Memory& mem = *memory;
	uint16_t sr = (params>>9) & mask[3];
	uint16_t br = (params>>6) & mask[3];
	uint16_t offset = sign_extend(params & mask[6], 6);
	mem.Write(reg[br]+offset, reg[sr]);
	return -1;
}

int Instructions::RTI(uint16_t, Registers*, Memory*){
	//Not used
	return -1;
}

int Instructions::NOT(uint16_t params, Registers* registers, Memory*){
	Registers& reg = *registers;
	uint16_t sr = params>>6 & mask[3];
	uint16_t dr = params>>9 & mask[3];
	reg[dr] = ~reg[sr];
	return dr;
}

int Instructions::LDI(uint16_t params, Registers* registers, Memory* memory){
	Registers& reg = *registers;
	Memory& mem = *memory;
	uint16_t offset = sign_extend(params & mask[9], 9);
	uint16_t dr = (params>>9) & mask[3];
	reg[dr] = mem.Read(mem.Read(reg[Registers::PC]+offset));
	return dr;
}

int Instructions::STI(uint16_t params, Registers* registers, Memory* memory){
	Registers& reg = *registers;
	Memory& mem = *memory;
	uint16_t sr = params>>9 & mask[3];
	uint16_t offset = sign_extend(params & mask[9], 9);
	mem.Write(mem.Read(reg[Registers::PC]+offset), reg[sr]);
	return -1;
}

int Instructions::JMP(uint16_t params, Registers* registers, Memory*){
	Registers& reg = *registers;
	uint16_t base_reg = params>>6 & mask[3];
	reg[Registers::PC] = reg[base_reg];
	return -1;
}

int Instructions::RES(uint16_t, Registers*, Memory*){
	//Not used
	return -1;
}

int Instructions::LEA(uint16_t params, Registers* registers, Memory*){
	Registers& reg = *registers;
	uint16_t offset = sign_extend(params&mask[9], 9);
	uint16_t dr = params>>9 & mask[3];
	reg[dr] = reg[Registers::PC] + offset;
	return dr;
}

int Instructions::TRAP(uint16_t params, Registers* registers, Memory* memory){
	uint16_t trap_code = params & mask[8];
	trap_routines.ExecuteTrapRoutine(trap_code, registers, memory);
	if(trap_routines.Status()==0){
		//OK
	}else if(trap_routines.Status()==1){
		status = TRAP_HALT;
	}else{
		status = TRAP_FAULT;
	}
	return -1;
}


