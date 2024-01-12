#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>

typedef int (*List_compare)(const void *a, const void *b);

int List_bubble_sort(List *list, List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);
List *List_upmerge_sort(char *arr[], int len, List_compare cmp);
List *List_insert_sorted(List *list, char *x, List_compare cmp);

#endif
