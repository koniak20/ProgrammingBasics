//gcc  -lcunit

#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "3zad.h"



void day_test() {
    Term* test = Term_create(9,0,90,TUE); 
	Lesson lesson = {*test,"Test"};
	
	Lesson_earlierDay(&lesson);
	CU_ASSERT_EQUAL(lesson.term.hour, 9);
	CU_ASSERT_EQUAL(lesson.term.minute, 0);
	CU_ASSERT_EQUAL(lesson.term.day, MON);
	
	Lesson_laterDay(&lesson);
	CU_ASSERT_EQUAL(lesson.term.hour, 9);
	CU_ASSERT_EQUAL(lesson.term.minute, 0);
	CU_ASSERT_EQUAL(lesson.term.day, TUE);
	
}

void time_test() {
    Term* test = Term_create(10,30,90,MON); 
	Lesson lesson = {*test,"Test"};
	
	Lesson_earlierTime(&lesson);
	CU_ASSERT_EQUAL(lesson.term.minute, 0);
	CU_ASSERT_EQUAL(lesson.term.day, MON);
	CU_ASSERT_EQUAL(lesson.term.hour, 9);
	
	Lesson_laterTime(&lesson);
	CU_ASSERT_EQUAL(lesson.term.hour, 10);
	CU_ASSERT_EQUAL(lesson.term.minute, 30);
	CU_ASSERT_EQUAL(lesson.term.day, MON);
}

void toString_test() { //"%s, %s %d:%c%d [%d]"
    Term* test = Term_create(9,0,90,MON); 
	Lesson lesson = {*test,"Test"};
	char *s = Lesson_toString(&lesson);
	CU_ASSERT_STRING_EQUAL(s, "Test, Monday 9:00 [90]");
}

int main(int argc, char **argv) {
	CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("test_suite", 0, 0);

	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "day_test", day_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "time_test", time_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "toString_test", toString_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();
}