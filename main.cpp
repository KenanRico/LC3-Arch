#include "system.h"
#include "inst_impl.h"
#include "sysprint.h"



int main(int argc, char** argv){
	PrintRegs();
	System::instruction[System::OP_ADD](0x022f);
	System::instruction[System::OP_ADD](0x0461);
	PrintRegs();
/*
	Setup();
	System::reg[System::Reg::PC] = 0x3000;
	bool running = true;
	while(running){
		uint16_t inst = MemRead(System::reg[System::Reg::PC]++);
		uint16_t op = inst>>12;
		uint16_t params = inst & 0x0fff;
		if(op<16){
			System::instruction[op](params);
		}else{
			HandleBadOpCode();
			running = false;
		}
	}
	ShutDown();
*/
	Setup();
	Registers regs;
	Memory mem;
	Instructions instructions;
	while(running){
		uint16_t inst = mem.GetNextInst(regs.IncPC());
		uint16_t op = 0;
		uint16_t params = 0;
		instructions.Parse(inst, &op, &params);
		if(!instructions.Execute(op, params)){
			HandleBadOpCode();
			running = false;
		}
	}
	return 0;
}
