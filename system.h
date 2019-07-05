#ifndef SYSTEM_H
#undef SYSTEM_H


#include "inst_impl.h"

#include <stdint.h>
#include <array>


#define RAM_UNIT_COUNT 65536
#define REG_COUNT 10
#define INST_TYPE_COUNT 16


namespace System{
	extern std::array<uint16_t, RAM_UNIT_COUNT> memory;
	extern std::array<uint16_t, REG_COUNT> reg;
	extern std::array<InstFuncPtr, INST_TYPE_COUNT> instruction;
	enum Reg{
		REG_0 = 0,
		REG_1 = 1,
		REG_2 = 2,
		REG_3 = 3,
		REG_4 = 4,
		REG_5 = 5,
		REG_6 = 6,
		REG_7 = 7,
		REG_PC = 8,
		REG_COND = 9
	};
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
	enum CondFlag{
		COND_POS = 1<<0,
		COND_ZRO = 1<<1,
		COND_NEG = 1<<2
	};
}

#endif
