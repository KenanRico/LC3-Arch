#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "registers.h"
#include "memory.h"
#include "traproutines.h"

#include <stdint.h>
#include <array>

class Instructions;
using InstFuncPtr = int(Instructions::*)(uint16_t, Registers*, Memory*);

class Instructions{
	public:
		static constexpr int count = 16;
		enum Opcode{
			OP_BR = 0,
			OP_ADD = 1,
			OP_LD = 2,
			OP_ST = 3,
			OP_JSR = 4,
			OP_AND = 5,
			OP_LDR = 6,
			OP_STR = 7,
			OP_RTI = 8,
			OP_NOT = 9,
			OP_LDI = 10,
			OP_STI = 11,
			OP_JMP = 12,
			OP_RES = 13,
			OP_LEA = 14,
			OP_TRAP = 15
		};
	private:
		std::array<InstFuncPtr, count> inst;
		std::array<uint16_t, count+1> mask;
		TrapRoutines trap_routines;
		int status;

	public:
		Instructions();
		~Instructions();
	private:
		Instructions(const Instructions&) = delete;
		Instructions& operator=(const Instructions&) = delete;

	public:
		void Parse(uint16_t, uint16_t*, uint16_t*) const;
		bool Execute(uint16_t, uint16_t, Registers*, Memory*);
		inline int Status() const { return status; }
	private:
		int BR(uint16_t, Registers*, Memory*);
		int ADD(uint16_t, Registers*, Memory*);
		int LD(uint16_t, Registers*, Memory*);
		int ST(uint16_t, Registers*, Memory*);
		int JSR(uint16_t, Registers*, Memory*);
		int AND(uint16_t, Registers*, Memory*);
		int LDR(uint16_t, Registers*, Memory*);
		int STR(uint16_t, Registers*, Memory*);
		int RTI(uint16_t, Registers*, Memory*);
		int NOT(uint16_t, Registers*, Memory*);
		int LDI(uint16_t, Registers*, Memory*);
		int STI(uint16_t, Registers*, Memory*);
		int JMP(uint16_t, Registers*, Memory*);
		int RES(uint16_t, Registers*, Memory*);
		int LEA(uint16_t, Registers*, Memory*);
		int TRAP(uint16_t, Registers*, Memory*);

	public:
		/*unit tests*/
		void TestAll(Registers*, Memory*);
};

uint16_t sign_extend(uint16_t, int);

#endif
