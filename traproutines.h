#ifndef TRAP_ROUTINES_H
#define TRAP_ROUTINES_H

#include "registers.h"
#include "memory.h"
#include <stdint.h>
#include <array>


class TrapRoutines;
using TrapFuncPtr = void(TrapRoutines::*)(uint16_t*, Memory*) const;

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

	public:
		TrapRoutines();
		~TrapRoutines();
	private:
		TrapRoutines(const TrapRoutines&) = delete;
		TrapRoutines& operator=(const TrapRoutines&) = delete;

	public:
		void ExecuteTrapRoutine(uint16_t, Registers*, Memory*) const;
	private:
		void Trap_GETC(uint16_t*, Memory*) const;
		void Trap_OUT(uint16_t*, Memory*) const;
		void Trap_PUTS(uint16_t*, Memory*) const;
		void Trap_IN(uint16_t*, Memory*) const;
		void Trap_PUTSP(uint16_t*, Memory*) const;
		void Trap_HALT(uint16_t*, Memory*) const;
};

#endif
