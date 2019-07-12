#include "traproutines.h"
#include "registers.h"
#include "memory.h"
#include <stdint.h>
#include <array>
#include <iostream>


#define INC_BY 1
//#define INC_BY_UINT16

#define OK 0
#define HALT 1
#define BAD_TRAP_CODE 2


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
),
status(OK){

}

TrapRoutines::~TrapRoutines(){

}

void TrapRoutines::ExecuteTrapRoutine(uint16_t trap_code, Registers* registers, Memory* memory){
	int trap_routine_index = trap_code - 0x20;
	if(trap_code<count){
		(this->*routine[trap_routine_index])(&(*registers)[Registers::R0], memory);
	}else{
		status = BAD_TRAP_CODE;
	}
}

/*---------------------------------------------------Trap routine implementations----------------------------------------------------------*/


void TrapRoutines::Trap_GETC(uint16_t* R0, Memory*){
	char c = '\0';
	std::cin>>c;
	*R0 = (uint16_t)c;
}

void TrapRoutines::Trap_OUT(uint16_t* R0, Memory*){
	std::cout<<(char)*R0;
}

void TrapRoutines::Trap_PUTS(uint16_t* R0, Memory* memory){
	Memory& mem = *memory;
#if INC_BY==1
	std::string str((char*)(&mem[0]+*R0));
#elif INC_BY==2
	std::string str((char*)(&mem[*R0]));
#endif
	std::cout<<str;
}

void TrapRoutines::Trap_IN(uint16_t* R0, Memory*){

}

void TrapRoutines::Trap_PUTSP(uint16_t* R0, Memory* memory){
	Memory& mem = *memory;
#if INC_BY==1
	const uint16_t& unit = *(&mem[0]+*R0);
#elif INC_BY==2
	const uint16_t& unit = mem[*R0];
#endif
	std::cout<<(char)(unit&0xff)<<(char)(unit>>8&0xff);
}

void TrapRoutines::Trap_HALT(uint16_t*, Memory*){
	status = HALT;
}
