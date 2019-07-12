#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <array>
#include <string>

class Memory{
	public:
		static constexpr int size = 65536;
	private:
		std::array<uint16_t, size> memory;
		int status;

	public:
		Memory();
		~Memory();
	private:
		Memory(const Memory&) = delete;
		Memory& operator=(const Memory&) = delete;

	public:
		void LoadImage(const std::string&);
		inline uint16_t& operator[](int i){ return memory.at(i); }
		void PrintContent() const;
		inline int Status() const { return status; }
};

#endif
