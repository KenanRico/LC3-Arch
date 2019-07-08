#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "registers.h"
#include "memory.h"

#include <stdint.h>
#include <array>

class Instructions;
using InstFuncPtr = uint16_t(Instructions::*)(uint16_t, Registers*, Memory*) const;

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

	public:
		Instructions();
		~Instructions();
	private:
		Instructions(const Instructions&) = delete;
		Instructions& operator=(const Instructions&) = delete;

	public:
		void Parse(uint16_t, uint16_t*, uint16_t*) const;
		bool Execute(uint16_t, uint16_t, Registers*, Memory*) const;
	private:
		uint16_t BR(uint16_t, Registers*, Memory*) const;
		uint16_t ADD(uint16_t, Registers*, Memory*) const;
		uint16_t LD(uint16_t, Registers*, Memory*) const;
		uint16_t ST(uint16_t, Registers*, Memory*) const;
		uint16_t JSR(uint16_t, Registers*, Memory*) const;
		uint16_t AND(uint16_t, Registers*, Memory*) const;
		uint16_t LDR(uint16_t, Registers*, Memory*) const;
		uint16_t STR(uint16_t, Registers*, Memory*) const;
		uint16_t RTI(uint16_t, Registers*, Memory*) const;
		uint16_t NOT(uint16_t, Registers*, Memory*) const;
		uint16_t LDI(uint16_t, Registers*, Memory*) const;
		uint16_t STI(uint16_t, Registers*, Memory*) const;
		uint16_t JMP(uint16_t, Registers*, Memory*) const;
		uint16_t RES(uint16_t, Registers*, Memory*) const;
		uint16_t LEA(uint16_t, Registers*, Memory*) const;
		uint16_t TRAP(uint16_t, Registers*, Memory*) const;
};

#endif
