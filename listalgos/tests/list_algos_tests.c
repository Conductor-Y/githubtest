#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>
#include <time.h>

char *values[] = {"XXXX", "abcd", "1234", "9847", "sxcx", "saoa", "aoxf", "pisy", "9538", "8573", "suxv"};		//char* aim to have different types of element
char *insert_value = "ksid";

#define NUM_VALUES 11

List *create_words()
{
    int i = 0;
    List *words = List_create();
	check_mem(words);

    for(i = 0; i < NUM_VALUES; i++) 
	{
        List_push(words, values[i]);
    }

    return words;

error:
	return NULL;
}

int is_sorted(List *words)			//compare value is int
{
    LIST_FOREACH(words, first, next, cur) 
	{
        if(cur->next && strcmp(cur->value, cur->next->value) > 0) 
		{
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }

    return 1;
}

char *test_bubble_sort()
{
    List *words = create_words();
	mu_assert(words != NULL, "Failed to create words list.");

    // should work on a list that needs sorting
    int rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    // should work on an already sorted list
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted failed.");
    mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

    List_destroy(words);

    // should work on an empty list
    words = List_create(words);
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    List_destroy(words);

    return NULL;
}

char *test_merge_sort()
{
    List *words = create_words();
	mu_assert(words != NULL, "Failed to create words list.");

    // should work on a list that needs sorting
    List *res = List_merge_sort(words, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    List *res2 = List_merge_sort(res, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Should still be sorted after merge sort.");
	
	List_destroy(res2);
    List_destroy(res);
    List_destroy(words);

    return NULL;
}

char *test_upmerge_sort()
{
	List *res = List_upmerge_sort(values, NUM_VALUES, (List_compare)strcmp);	
	mu_assert(is_sorted(res), "List are not sorted after upmerge sort.");

	List *res2 = List_upmerge_sort(values, NUM_VALUES, (List_compare)strcmp);
	mu_assert(is_sorted(res2), "Should still be sorted after upmerge sort.");

	List_destroy(res);
	List_destroy(res2);

	return NULL;
}

char *test_insert_sorted()
{
	List *words = create_words();
	mu_assert(words != NULL, "Failed to create words.");

	List *res = List_merge_sort(words, (List_compare)strcmp);		//res is already sorted 
	mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

	List *res2 = List_insert_sorted(res, insert_value, (List_compare)strcmp);
	mu_assert(is_sorted(res2), "res are not sorted after insert sort.");

//	List_destroy(res2);
//	List_destroy(res);
//	List_destroy(words);

	return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);
	mu_run_test(test_upmerge_sort);
	mu_run_test(test_insert_sorted);
    return NULL;
}

RUN_TESTS(all_tests);


/*test time
int main()
{
	List *words = create_words();

	clock_t start, finish;
	double Total_time;
	
	start = clock();

	for(int i = 0; i < 10000; i++)
	{
//		List_bubble_sort(words, (List_compare)strcmp);
		List_merge_sort(words, (List_compare)strcmp);
	};

	finish = clock();

	Total_time = (double)(finish - start) / CLOCKS_PER_SEC; //单位换算成秒
	printf("%f seconds\n", Total_time);



	return 0;
}
*/





