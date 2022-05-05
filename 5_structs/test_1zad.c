#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "1zad.h"
#include <stdlib.h>
#include <stdio.h>

void toString_test() {
	CU_ASSERT_STRING_EQUAL(Day_toString(MON), "Monday");
	CU_ASSERT_STRING_EQUAL(Day_toString(TUE), "Tuesday");
	CU_ASSERT_STRING_EQUAL(Day_toString(SUN), "Sunday");
}


void nextDay_test() {
	CU_ASSERT_EQUAL(Day_nextDay(MON), TUE);
	CU_ASSERT_EQUAL(Day_nextDay(SUN), MON);
	CU_ASSERT_EQUAL(Day_nextDay(WED), THU);
}

void prevDay_test() {
	CU_ASSERT_EQUAL(Day_prevDay(SUN), SAT);
	CU_ASSERT_EQUAL(Day_prevDay(WED), TUE);
	CU_ASSERT_EQUAL(Day_prevDay(MON), SUN);
}

void parse_test() {
    char* a[8] = {"Anything","Mon","d+", "t-", "d+", "d-", "t-", "t+"};
	Action res[6] = {DAY_LATER, TIME_EARLIER, DAY_LATER, DAY_EARLIER, TIME_EARLIER, TIME_LATER};
        Action* arr = parse(8, a);
	
	for (int i = 0; i < 5; i++)
		CU_ASSERT_EQUAL(arr[i], res[i]);
	
}

int main(){
        CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("test_suite", 0, 0);

	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "toString_test", toString_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "nextDay_test", nextDay_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "prevDay_test", prevDay_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "parse_test", parse_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();
}

