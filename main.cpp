#include "memory.h"
#include "registers.h"
#include "instructions.h"
#include "platform.h"
#include "modeconfig.h"
#include "unittests.h"

#include <iostream>




int main(int argc, char** argv){
#if MODE==TEST	
	RunUnittests();
#elif MODE==RUN
	/*Configure platform*/
	Platform platform;
	/*Init resources*/
	Registers regs;
	Memory mem;
	Instructions instructions;
	/*Load program*/
	mem.LoadImage("./Executables/rogue.obj");
	/*execution loop*/
	regs[Registers::PC] = 0x3000;
	platform.DisableInputBuffering();
	while((mem.Status()|instructions.Status())==0x0){
		uint16_t instruction = mem.Read(regs.GetIncPC());
		uint16_t opcode = 0;
		uint16_t params = 0;
		instructions.Parse(instruction, &opcode, &params);
		instructions.Execute(opcode, params, &regs, &mem);
	}
	platform.RestoreInputBuffering();
	std::cout<<"mem status="<<mem.Status()<<"; inst status="<<instructions.Status()<<"\n";
	/*Restore platform original config*/
#endif

	return 0;
}
