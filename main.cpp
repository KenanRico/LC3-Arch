#include "memory.h"
#include "registers.h"
#include "instructions.h"
#include "platform.h"
#include "modeconfig.h"

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

#if MODE==TEST	
	Registers* tregs = new Registers();
	Memory* tmem = new Memory();
	Instructions* tinstructions = new Instructions();
	tregs->TestAll();
	tmem->TestAll();
	tinstructions->TestAll(tregs, tmem);
	delete tregs; tregs=nullptr;
	delete tmem; tmem=nullptr;
	delete tinstructions; tinstructions=nullptr;
#elif MODE==RUN
	/*Configure platform*/
	Platform platform;
	platform.DisableInputBuffering();
	/*Init resources*/
	Registers regs;
	Memory mem;
	Instructions instructions;
	/*Load program*/
	mem.LoadImage("someexecutable");
	/*execution loop*/
	while((mem.Status()|instructions.Status())==0x0){

	}
	std::cout<<"mem status="<<mem.Status()<<"; inst status="<<instructions.Status()<<"\n";
	/*Restore platform original config*/
	platform.RestoreInputBuffering();
#endif

	return 0;
}
