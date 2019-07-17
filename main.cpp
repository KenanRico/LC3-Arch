#include "memory.h"
#include "registers.h"
#include "instructions.h"
#include "platform.h"

#include <iostream>



int main(int argc, char** argv){
	/*
	regs.PrintContent();
	instructions.Execute(Instructions::OP_ADD, 0x002c, &regs, &mem);
	regs.PrintContent();
	instructions.Execute(Instructions::OP_ADD, 0x0267, &regs, &mem);
	regs.PrintContent();
	instructions.Execute(Instructions::OP_AND, 0x0440, &regs, &mem);
	regs.PrintContent();
	*/



	/*Configure platform*/
	Platform platform;
	platform.DisableInputBuffering();
	/*Init resources*/
	Registers regs;
	Memory mem;
	Instructions instructions;
	UnitTest unit_test(&regs, &mem, &instructions);
	unit_test.TestInst();
	unit_test.TestMem();
	unit_test.PrintResult();
	/*Load program*/
	mem.LoadImage("someexecutable");
	/*execution loop*/
	while((mem.Status()|instructions.Status())==0x0){

	}
	std::cout<<"mem status="<<mem.Status()<<"; inst status="<<instructions.Status()<<"\n";
	/*Restore platform original config*/
	platform.RestoreInputBuffering();
	return 0;
}
