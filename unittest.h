#ifndef UNIT_TEST_H
#define UNIT_TEST_H


class UnitTest{
	private:
		class InstTestSuite;
		class memTestSuite;
	private:
		InstTestSuite inst_tests;
		MemTestSuite mem_tests;
		Registers* regs;
		Memory* mem;
		Instructions* inst;
	
	public:
		UnitTest(Registers*, Memory*, Instructions*);
		~UnitTest();
	private:
		UnitTest() = delete;
		UnitTest(const UnitTest&) = delete;
		UnitTest& operator=(const UnitTest&) = delete;

	public:
		void TestInst();
		void TestMem();
		void PrintResult();
};


class UnitTest::InstTestSuite{
	public:
		static constexpr int count = Instructions::count;
		static constexpr int reps = 3;
		std::array<uint16_t, count> inst;
		std::array<int, count*reps> target;
		std::array<uint16_t, count*reps> result;
		std::array<bool, count> pass;
};

class UnitTest::memTestSuite{

};

#endif
