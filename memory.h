#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <array>

class Memory{
	public:
		static constexpr int size = 65536;
	private:
		std::array<uint16_t, size> memory;

	public:
		Memory();
		~Memory();
	private:
		Memory(const Memory&) = delete;
		Memory& operator=(const Memory&) = delete;

	public:
		inline uint16_t& operator[](int i){ return memory.at(i); }
		void PrintContent() const;
};

#endif
