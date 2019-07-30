#ifndef REGISTERS_H
#define REGISTERS_H

#include <array>
#include <stdint.h>

class Registers{
	public:
		static constexpr int count = 10;
		enum Index{
			R0 = 0,
			R1 = 1,
			R2 = 2,
			R3 = 3,
			R4 = 4,
			R5 = 5,
			R6 = 6,
			R7 = 7,
			PC = 8,
			COND = 9
		};
		enum CondFlag{
			COND_POS = 1<<0,
			COND_ZRO = 1<<1,
			COND_NEG = 1<<2
		};
	private:
		std::array<uint16_t, count> reg;

	public:
		Registers();
		~Registers();
	private:
		Registers(const Registers&) = delete;
		Registers& operator=(const Registers&) = delete;

	public:
		inline uint16_t GetIncPC(){ return reg[PC]++; }
		inline uint16_t& operator[](int i){ return reg.at(i); }
		void UpdateFlag(int);
		void PrintContent() const; 

		/*unit tests*/
		void TestAll();
		
};

#endif
