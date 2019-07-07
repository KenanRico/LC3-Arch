#include "memory.h"
#include "registers.h"
#include "instructions.h"



int main(int argc, char** argv){
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

/*
	Setup();
	Registers regs;
	Memory mem;
	Instructions instructions;
	while(running){
		uint16_t inst = mem.Read(regs.IncPC());
		uint16_t op = 0;
		uint16_t params = 0;
		instructions.Parse(inst, &op, &params);
		if(!instructions.Execute(op, params, &regs, &mem)){
			HandleBadOpCode();
			running = false;
		}
	}
*/
	Registers regs;
	Memory mem;
	Instructions instructions;
	regs.PrintContent();
	instructions.Execute(Instructions::OP_ADD, 0x006c, &regs, &mem);
	regs.PrintContent();
	return 0;
}
