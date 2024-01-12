#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

inline void ListNode_swap(ListNode *a, ListNode *b)			//exchange value of a node with b node
{
	void *temp = a->value;
	a->value = b->value;
	b->value = temp;
}

int List_bubble_sort(List *list, List_compare cmp)		//compare different types of data
{
	int flag = 1;
	if(List_count(list) <= 1) return 0;		//it is unecessary to sort

	do
	{
		flag = 1;
		LIST_FOREACH(list, first, next, cur)
		{
			if(cur->next != NULL)
			{
				if(cmp(cur->value, cur->next->value) > 0)
				{
					ListNode_swap(cur, cur->next);
					flag = 0;
				}
			}
		}
	}while(!flag);		//when no node's value is larger than others, sorting ends

	return 0;
}

//merge left and right, left and right is already sorted
inline List *List_merge(List *left, List *right, List_compare cmp)
{
    List *result = List_create();
	check_mem(result);

    void *val = NULL;

    while(List_count(left) > 0 || List_count(right) > 0) 
	{
        if(List_count(left) > 0 && List_count(right) > 0) 
		{
            if(cmp(List_first(left), List_first(right)) <= 0) 
			{
                val = List_shift(left);		//left one is smaller, val get left list's first node's value and delete this node, the first->next node be the first node
            } 
			else 
			{
                val = List_shift(right);
            }

            List_push(result, val);
        } 
		else if(List_count(left) > 0)		//right list has no value,val stragihtly get left value
		{
            val = List_shift(left);
            List_push(result, val);
        } 
		else if(List_count(right) > 0) 
		{
            val = List_shift(right);
            List_push(result, val);
        }
    }
    return result;

error:
	return NULL;
}

List *List_merge_sort(List *list, List_compare cmp)
{
    if(List_count(list) <= 1) 
	{
        return list;
    }

    List *left = List_create();
    List *right = List_create();

	check_mem(left);
	check_mem(right);

    int middle = List_count(list) / 2;

    LIST_FOREACH(list, first, next, cur)		//devide list into twolists by middle count
	{
        if(middle > 0) 
		{
            List_push(left, cur->value);
        } 
		else 
		{
            List_push(right, cur->value);
        }
        middle--;
    }
	//renuse the function to devide the devided list till can not devide
    List *sort_left = List_merge_sort(left, cmp);		    
	List *sort_right = List_merge_sort(right, cmp);

    if(sort_left != left) List_destroy(left);
    if(sort_right != right) List_destroy(right);

    return List_merge(sort_left, sort_right, cmp);

error:
	return NULL;
}

int min(int x, int y) 
{
    return x < y ? x : y;
}

List *List_upmerge_sort(char *arr[], int len, List_compare cmp)		//from bottom to up merge sorting 
{
    char **a = arr;
    char **b = (char **) malloc(len * sizeof(char*));
    int seg, start;
    for (seg = 1; seg < len; seg += seg) 
	{
        for (start = 0; start < len; start += seg * 2) 
		{
            int low = start, mid = min(start + seg, len), high = min(start + seg * 2, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            
			while (start1 < end1 && start2 < end2)
                b[k++] = cmp(a[start1], a[start2]) < 0 ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        char **temp = a;
        a = b;
        b = temp;
    }
    if (a != arr) 
	{
        for (int i = 0; i < len; i++)
		{
            b[i] = a[i];
		}
		b = a;
    }
	
	List *list = List_create();
	check_mem(list);

	for(int i = 0; i < len; i++)
	{
		List_push(list, arr[i]);
	}

	free(b);
	return list;

error:
	return NULL;
}

List *List_insert_sorted(List *list, char *x, List_compare cmp)
{
	check_mem(list);

	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = x;		//initialize node
	node->next = NULL;
	node->prev = NULL;

	if(cmp(x, list->last->value) > 0)		//insert the bottom of list
	{
		List_push(list, x);
	}

	else if(cmp(x, list->first->value) < 0)			//insert the head of list
	{
		List_unshift(list, x);
	}

	else if(cmp(x, list->first->value) > 0 && cmp(x, list->last->value) < 0)		//insert among the list
	{
		LIST_FOREACH(list, first, next, cur)
		{
			if(cur != NULL && cmp(x, cur->value) < 0)
			{
				if(cur->prev != NULL && cur->next != NULL)
				{
					node->next = cur;
					cur->prev = node;
					node->prev = cur->prev;
					cur->prev->next = node;
				}
			}
		}
	}

	if(node != NULL) free(node);	

	return list;

error:
	return NULL;
}

