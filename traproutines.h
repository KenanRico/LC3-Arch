#ifndef TRAP_ROUTINES_H
#define TRAP_ROUTINES_H

#include "registers.h"
#include "memory.h"
#include <stdint.h>
#include <array>


class TrapRoutines;
using TrapFuncPtr = int(TrapRoutines::*)(uint16_t*, Memory*);

class TrapRoutines{
	public:
		static constexpr int count = 6;
		enum TrapCode{
			GETC = 0x20,
			OUT = 0x21,
			PUTS = 0x22,
			IN = 0x23,
			PUTSP = 0x24,
			HALT = 0x25
		};
	private:
		std::array<TrapFuncPtr, count> routine;
		uint16_t bad_trap_code;
		int status;

	public:
		TrapRoutines();
		~TrapRoutines();
	private:
		TrapRoutines(const TrapRoutines&) = delete;
		TrapRoutines& operator=(const TrapRoutines&) = delete;

	public:
		int ExecuteTrapRoutine(uint16_t, Registers*, Memory*);
		inline int Status() const { return status; }
		inline uint16_t BadTrapCode() const { return bad_trap_code; }
	private:
		int Trap_GETC(uint16_t*, Memory*);
		int Trap_OUT(uint16_t*, Memory*);
		int Trap_PUTS(uint16_t*, Memory*);
		int Trap_IN(uint16_t*, Memory*);
		int Trap_PUTSP(uint16_t*, Memory*);
		int Trap_HALT(uint16_t*, Memory*);
};

#endif
