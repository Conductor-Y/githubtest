#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
static List *list_2 = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";
char *test4 = "test4 data";
char *test5 = "test5 data";
char *test6 = "test6 data";


char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");
	
	list_2 = List_create();
	mu_assert(list_2 != NULL, "Failed to creat list_2.");

    return NULL;
}


char *test_destroy()
{
    List_clear_destroy(list);
	List_clear_destroy(list_2);

    return NULL;
}


char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

	List_push(list_2, test4);
    mu_assert(List_last(list_2) == test4, "Wrong the first value in list_2");

    List_push(list_2, test5);
    mu_assert(List_last(list_2) == test5, "Wrong the second value in list_2.");
	
	List_push(list_2, test6);
	mu_assert(List_last(list_2) == test6, "Wrong the third value in list_2")
    mu_assert(List_count(list_2) == 3, "Wrong count in list_2.");



    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

	val = List_pop(list_2);
	mu_assert(val == test6, "Wrong value on pop.");

    val = List_pop(list_2);
    mu_assert(val == test5, "Wrong value on pop.");

    val = List_pop(list_2);
    mu_assert(val == test4, "Wrong value on pop.");
    mu_assert(List_count(list_2) == 0, "Wrong count after pop.");



    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
	mu_assert(List_first(list) == test2, "Wrong first value");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}


char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}

char *test_link()
{
	List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong the first value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong the second value.");
    mu_assert(List_count(list) == 2, "Wrong count in list.");

	List_push(list_2, test4);
	mu_assert(List_last(list_2) == test4, "Wrong the first value in list_2.");

	List_push(list_2, test5);
	mu_assert(List_last(list_2) == test5, "Wrong the second value in list_2.");
	mu_assert(List_count(list_2) == 2, "Wrong count in list_2.");

	int count_all = list->count + list_2->count;
	List_link(list, list_2);
	mu_assert(List_last(list) == test5, "Wrong the last value.");
	mu_assert(list->count == count_all, "Wrong the all count.");

	List_pop(list);
	List_pop(list);
	List_pop(list);
	List_pop(list);
	List_pop(list_2);
	List_pop(list_2);

	return NULL;
}

char *test_copy()
{
	List_push(list, test1);
	List_push(list, test2);
	List_push(list, test3);
	List_copy(list, list_2);

	char *val = List_pop(list_2);
	mu_assert(val == test3, "Failed to copy the third node.");
	val = List_pop(list_2);
	mu_assert(val = test2, "Failed to copy the second node.");
	val = List_pop(list_2);
	mu_assert(val = test1, "Failed to copy the first node.");
	mu_assert(list_2->count == 0, "Failed to copy the count.");

	return NULL;
}

char *all_tests() 
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
	mu_run_test(test_shift);
	mu_run_test(test_link);
	mu_run_test(test_copy);
    mu_run_test(test_destroy);
	
    return NULL;
}

RUN_TESTS(all_tests);

