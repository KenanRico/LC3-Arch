#include "inst_impl.h"
#include "system.h"

#include <stdint.h>



uint16_t sign_extend(uint16_t val, int bit_count){
	if((val>>(bit_count-1)) & 1) {
		val |= (0xFFFF << bit_count);
	}
	return val;
}



void InstBR(uint16_t){

}

void InstADD(uint16_t params){
	uint16_t dr = params>>9;
	uint16_t sr1 = params>>6 & 0x0007;
	if(params & 0x0020){
		/*immediate mode*/
		uint16_t imm5 = sign_extend(params & 0x001f, 5);
		System::reg[dr] = System::reg[sr1] + imm5;
	}else{
		/*reg mode*/
		uint16_t sr2 = params & 0x0007;
		System::reg[dr] = System::reg[sr1] + System::reg[sr2];
	}
	//UpdateFlag(dr);
}

void InstLD(uint16_t params){
	uint16_t offset = params & 0x01ff;
	uint16_t dr = (params>>9) & 0x0007;
	System::reg[dr] = System::memory[System::reg[REG_PC]+offset];
}

void InstST(uint16_t){

}

void InstJSR(uint16_t params){
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
}

void InstAND(uint16_t params){
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
}

void InstLDR(uint16_t params){
	uint16_t sr = (params>>6) & 0x0007;
	uint16_t offset = params & 0x001f;
	uint16_t dr = () & 0x0007
}

void InstSTR(uint16_t){

}

void InstRTI(uint16_t){

}

void InstNOT(uint16_t){

}

void InstLDI(uint16_t){
	uint16_t offset = params & 0x01ff;
	uint16_t dr = (params>>9) & 0x0007;
	System::reg[dr] = System::memory[System::memory[System::reg[REG_PC]+offset]];
}

void InstSTI(uint16_t){

}

void InstJMP(uint16_t params){
	uint16_t base_reg = params>>6 & 0x0007;
	System::reg[System::REG_PC] = System::reg[base_reg];
}

void InstRES(uint16_t){

}

void InstLEA(uint16_t){

}

void InstTRAP(uint16_t){

}
