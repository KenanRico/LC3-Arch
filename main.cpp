#include "memory.h"
#include "registers.h"
#include "instructions.h"

#include <iostream>



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
	/*
	regs.PrintContent();
	instructions.Execute(Instructions::OP_ADD, 0x002c, &regs, &mem);
	regs.PrintContent();
	instructions.Execute(Instructions::OP_ADD, 0x0267, &regs, &mem);
	regs.PrintContent();
	instructions.Execute(Instructions::OP_AND, 0x0440, &regs, &mem);
	regs.PrintContent();
	*/
	Registers regs;
	Memory mem;
	Instructions instructions;
	mem.LoadImage("someexecutable");
	while((mem.Status()|instructions.Status())==0x0){

	}
	std::cout<<"mem status="<<mem.Status()<<"; inst status="<<instructions.Status()<<"\n";
	return 0;
}
