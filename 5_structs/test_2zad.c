#include <CUnit/Basic.h>
#include "2zad.h"

void creation_tests() {
	Term* t = Term_create(1, 2, 3);
	CU_ASSERT_EQUAL(t->hour, 1);
	CU_ASSERT_EQUAL(t->minute, 2);
	CU_ASSERT_EQUAL(t->duration, 3);
	
	Term_init(t, 4, 5, 6);
	CU_ASSERT_EQUAL(t->hour, 4);
	CU_ASSERT_EQUAL(t->minute, 5);
	CU_ASSERT_EQUAL(t->duration, 6);
	
	Term_destroy(t);
}

void comparison_tests() {
	Term* t1 = Term_create(9, 0, 60);
	Term* t2 = Term_create(12, 30, 90);
	
	CU_ASSERT_EQUAL(Term_equals(t1, t1), 1);
	CU_ASSERT_EQUAL(Term_equals(t2, t2), 1);
	CU_ASSERT_EQUAL(Term_equals(t1, t2), 0);
	
    CU_ASSERT_EQUAL(Term_earlierThan(t1, t2), 1);
	CU_ASSERT_EQUAL(Term_earlierThan(t2, t1), 0);
	CU_ASSERT_EQUAL(Term_earlierThan(t1, t1), 0);
	CU_ASSERT_EQUAL(Term_earlierThan(t2, t2), 0);
	
	CU_ASSERT_EQUAL(Term_laterThan(t1, t2), 0);
	CU_ASSERT_EQUAL(Term_laterThan(t2, t1), 1);
	CU_ASSERT_EQUAL(Term_laterThan(t1, t1), 0);
	CU_ASSERT_EQUAL(Term_laterThan(t2, t2), 0);
	
	Term_destroy(t1);
	Term_destroy(t2);
}

void endTerm_tests() {
	Term* t1 = Term_create(9, 0, 0);
	Term* t2 = Term_create(11, 30, 0);
	Term* t3 = Term_endTerm(t1, t2);
	
	CU_ASSERT_EQUAL(t3->hour, 9);
	CU_ASSERT_EQUAL(t3->minute, 0);
	CU_ASSERT_EQUAL(t3->duration, 150);
	
	Term_destroy(t1);
	Term_destroy(t2);
	Term_destroy(t3);
}

void toString_tests() {
	Term* t1 = Term_create(9, 30, 1050);
	char a[] = "9:30 [1050]";
	char *b = Term_toString(t1);
	
	CU_ASSERT_STRING_EQUAL(a, b);
	
	Term_destroy(t1);
}

int main() {
	CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("test_suite", 0, 0);

	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "creation_tests", creation_tests))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "comparison_tests", comparison_tests))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "endTerm_tests", endTerm_tests))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "toString_tests", toString_tests))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();
}


