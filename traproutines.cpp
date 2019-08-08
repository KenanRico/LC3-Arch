#include "traproutines.h"
#include "registers.h"
#include "memory.h"
#include <stdint.h>
#include <array>
#include <iostream>
#include <sstream>
#include <stdio.h>


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

int TrapRoutines::ExecuteTrapRoutine(uint16_t trap_code, Registers* registers, Memory* memory){
	int trap_routine_index = trap_code - 0x20;
	int r = -1;
	if(trap_routine_index<count){
		r = (this->*routine[trap_routine_index])(&(*registers)[Registers::R0], memory);
	}else{
		status = BAD_TRAP_CODE;
		bad_trap_code = trap_code;
	}
	return r;
}

/*---------------------------------------------------Trap routine implementations----------------------------------------------------------*/


/*
int TrapRoutines::Trap_GETC(uint16_t* R0, Memory*){
	char c = '\0';
	std::cin>>c;
	*R0 = (uint16_t)c;
	return 0;
}

int TrapRoutines::Trap_OUT(uint16_t* R0, Memory*){
	std::cout<<(char)*R0;
	return -1;
}

int TrapRoutines::Trap_PUTS(uint16_t* R0, Memory* memory){
	Memory& mem = *memory;
	uint16_t* c = &mem[*R0];
	std::string str = "";
	while(*c!=0){
		str.push_back((char)*c);
		++c;
	}
	std::cout<<str;
	return -1;
}

int TrapRoutines::Trap_IN(uint16_t* R0, Memory*){
	std::cout<<"Enter a character: ";
	char c = '\0';
	std::cin>>c;
	std::cout<<c;
	*R0 = (uint16_t)c;
	return 0;
}

int TrapRoutines::Trap_PUTSP(uint16_t* R0, Memory* memory){
	Memory& mem = *memory;
	uint8_t* c = (uint8_t*)&mem[*R0];
	std::string str = "";
	while(*c!=0){
		//str.push_back((uint8_t)(*c&0x00ff));
		//str.push_back((uint8_t)(*c>>8));
		str.push_back((char)*c);
		++c;
	}
	std::cout<<str;
	return -1;
}

int TrapRoutines::Trap_HALT(uint16_t*, Memory*){
	status = HALT;
	return -1;
}
*/


int TrapRoutines::Trap_GETC(uint16_t* R0, Memory*){
	*R0 = (uint16_t)getchar();
	return 0;
}

int TrapRoutines::Trap_OUT(uint16_t* R0, Memory*){
	putc((char)*R0, stdout);
	fflush(stdout);
	return -1;
}

int TrapRoutines::Trap_PUTS(uint16_t* R0, Memory* memory){
	Memory& mem = *memory;
	uint16_t* c = &mem[*R0];
	std::string str = "";
	while(*c!=0){
		putc((char)*c, stdout);
		++c;
	}
	fflush(stdout);
	return -1;
}

int TrapRoutines::Trap_IN(uint16_t* R0, Memory*){
	std::cout<<"Enter a character: ";
	char c = getchar();
	putc(c, stdout);
	*R0 = (uint16_t)c;
	return 0;
}

int TrapRoutines::Trap_PUTSP(uint16_t* R0, Memory* memory){
	Memory& mem = *memory;
	uint16_t* c = &mem[*R0];
	std::string str = "";
	while(*c!=0){
		//str.push_back((uint8_t)(*c&0x00ff));
		//str.push_back((uint8_t)(*c>>8));
		uint8_t c1 = *c & 0xff; putc((char)c1, stdout);
		uint8_t c2 = *c >> 8; if(c2!=0) putc((char)c2, stdout);
		++c;
	}
	fflush(stdout);
	return -1;
}

int TrapRoutines::Trap_HALT(uint16_t*, Memory*){
	status = HALT;
	return -1;
}
