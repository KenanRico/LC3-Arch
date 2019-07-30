#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <array>
#include <string>

class Memory{
	public:
		static constexpr int size = 65536;
		enum MemMappedReg{
			KBSR = 0xfe00,
			KBDR = 0xfe02
		};
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
		uint16_t& operator[](int);
		void PrintContent() const;
		inline int Status() const { return status; }

		/*unit tests*/
		void TestAll();
};

#endif
