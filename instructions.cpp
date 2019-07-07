#include "instructions.h"
#include "registers.h"
#include "memory.h"

#include <stdint.h>




Instructions::Instructions(){
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
	mask[0] = 0x0000;
	mask[1] = 0x0001;
	mask[2] = 0x0003;
	mask[3] = 0x0007;
	mask[4] = 0x000f;
	mask[5] = 0x001f;
	mask[6] = 0x003f;
	mask[7] = 0x007f;
	mask[8] = 0x00ff;
	mask[9] = 0x01ff;
	mask[10] = 0x03ff;
	mask[11] = 0x07ff;
	mask[12] = 0x0fff;
	mask[13] = 0x1fff;
	mask[14] = 0x3fff;
	mask[15] = 0x7fff;
	mask[16] = 0xffff;
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
	uint16_t dr = params>>9 & mask[3];
	uint16_t sr1 = params>>6 & mask[3];
	const std::array<uint16_t, Registers::count>& reg = registers->Content();
	if(params>>6 & mask[1]){
		/*immediate mode*/
		uint16_t imm5 = sign_extend(params & 0x001f, 5);
		registers->Write(dr, reg[sr1] + imm5);
	}else{
		/*reg mode*/
		uint16_t sr2 = params & mask[3];
		registers->Write(dr, reg[sr1]+reg[sr2]);
	}
	return 0;
	//UpdateFlag(dr);
}

uint16_t Instructions::LD(uint16_t params, Registers*, Memory*) const{
#ifdef INST_IMPL
	uint16_t offset = params & 0x01ff;
	uint16_t dr = (params>>9) & 0x0007;
	System::reg[dr] = System::memory[System::reg[REG_PC]+offset];
#endif
}

uint16_t Instructions::ST(uint16_t, Registers*, Memory*) const{

}

uint16_t Instructions::JSR(uint16_t params, Registers*, Memory*) const{
#ifdef INST_IMPL
	if(params>>11 & 0x0001){
		//JSR
		System::reg[System::REG_7] = System::reg[System::REG_PC]+1;
		uint16_t offset = sign_extend(params&0x07ff, 11);
		System::reg[System::REG_PC] += offset;
	}else{
		//JSRR
		uint16_t base_reg = params>>6 & 0x0007;
		System::reg[System::REG_PC] = System::reg[base_reg];
	}
#endif
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


