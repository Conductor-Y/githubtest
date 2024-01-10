#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *message)
{
    if(errno) 
	{
        perror(message);
    } 
	else 
	{
		printf("ERROR: %s\n", message);
    }

    exit(1);
}

typedef int (*compare_cb)(int a, int b);
typedef int *(*sort_func)(int *numbers, int count, compare_cb cmp);

int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if(!target) die("Memory error.");

    memcpy(target, numbers, count * sizeof(int));		//initialize target pointer

    for(i = 0; i < count; i++)		//do (coount - 1) times can sort the array from large to small
	{
        for(j = 0; j < count - 1; j++)		//from the last to the top
		{
            if(cmp(target[j], target[j+1]) > 0)		//ensure the larger number is in the higher position  
			{
                temp = target[j+1];		
                target[j+1] = target[j];
                target[j] = temp;
            }
        }
    }

    return target;
}

int *mirror_sort(int *numbers, int count, compare_cb cmp)		//here the last variate is useless, just to adapt the test_sorting format
{
	int temp = 0;
	int i = 0;
	int *target = malloc(count * sizeof(int));

	if(!target) die("Memory error.");

	memcpy(target, numbers, count * sizeof(int));

	int n = count / 2;
	for(i = 0; i < n; i++)		//whatever count is singular or dual, the changing is the same
	{
		temp = target[count-1-i];
		target[count-1-i] = target[i];
		target[i] = temp;
	}
	return target;
}

int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if(a == 0 || b == 0) 
	{
        return 0;
    } 
	else 
	{
        return a % b;
    }
}

void test_sorting(int *numbers, int count, compare_cb cmp, sort_func sortf)
{
    int i = 0;
    int *sorted = sortf(numbers, count, cmp);

    if(!sorted) die("Failed to sort as requested.");

    for(i = 0; i < count; i++) 
	{
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free(sorted);

/*	unsigned char *data = (unsigned char *)cmp;
	for(i = 0; i < 25; i++) 
	{
		printf("%02x:", data[i]);		//convert integert into hex
	}
	printf("\n");
*/	
}


int main(int argc, char *argv[])
{
    if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if(!numbers) die("Memory error.");

    for(i = 0; i < count; i++) 
	{
        numbers[i] = atoi(inputs[i]);
    }
	
	printf("sorting mode 1:\n");
    test_sorting(numbers, count, sorted_order, *bubble_sort);
    test_sorting(numbers, count, reverse_order, *bubble_sort);
    test_sorting(numbers, count, strange_order, *bubble_sort);
	printf("\n");

	printf("sorting mode 2:\n");
	test_sorting(numbers, count, sorted_order, *mirror_sort);

    free(numbers);

    return 0;
}

