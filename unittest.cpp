


















void UnitTest::TestInst(){
	/*Test every instruction except TRAP*/
	int count = Instructions::count-1;
	for(int i=0; i<InstTestSuite::count; ++i){
		for(int j=0; j<InstTestSuite::reps; ++j){
			int k = i*InstTestSuite::reps+j;
			inst->Execute(...inst_tests.inst[k]);
			inst_tests.pass[j] &&= *reg[inst_test.target[k]]==inst_tests.result[k];
		}
	}

	/*Test TRAP*/
}
