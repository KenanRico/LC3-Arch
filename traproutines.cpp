#include "traproutines.h"
#include "registers.h"
#include "memory.h"
#include <stdint.h>
#include <array>


TrapRoutines::TrapRoutines(): 
routine(
	{
		&TrapRoutines::Trap_GETC,
		&TrapRoutines::Trap_OUT,
		&TrapRoutines::Trap_PUTS,
		&TrapRoutines::Trap_IN,
		&TrapRoutines::Trap_PUTSP,
		&TrapRoutines::Trap_HALT
	}
){

}

TrapRoutines::~TrapRoutines(){

}

void TrapRoutines::ExecuteTrapRoutine(uint16_t trap_code, Registers* registers, Memory* memory) const{
	int trap_routine_index = trap_code - 0x20;
	(this->*routine[trap_routine_index])((*registers)[Registers::R0], memory);
}

/*---------------------------------------------------Trap routine implementations----------------------------------------------------------*/


void TrapRoutines::Trap_GETC(uint16_t* R0, Memory*) const{
	char c = '';
	std::cin>>c;
	*R0 = (uint16_t)c;
}

void TrapRoutines::Trap_OUT(uint16_t* R0, Memory*) const{

}

void TrapRoutines::Trap_PUTS(uint16_t* R0, Memory*) const{

}

void TrapRoutines::Trap_IN(uint16_t* R0, Memory*) const{

}

void TrapRoutines::Trap_PUTSP(uint16_t* R0, Memory*) const{

}

void TrapRoutines::Trap_HALT(uint16_t*, Memory*) const{

}
