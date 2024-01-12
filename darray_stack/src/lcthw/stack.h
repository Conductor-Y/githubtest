#ifndef _lcthw_Stack_h
#define _lcthw_Stack_h

#include <lcthw/darray.h>

typedef DArray Stack;

#define Stack_create DArray_create
#define Stack_destroy DArray_destroy
#define Stack_clear DArray_clear
#define Stack_clear_destroy DArray_clear_destroy

#define Stack_push DArray_push
#define Stack_pop DArray_pop
#define Stack_peek DArray_last

#define Stack_count DArray_count

#define STACK_FOREACH(S) DARRAY_FOREACH(S)

#endif
