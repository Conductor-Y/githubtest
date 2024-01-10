#include <stdio.h>

#define TURE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define max_size 100		//the maxsize of stack

struct SqStack 
{
	int elements[max_size];		//store elements in stack
	int top;	//stack top pointer
};

void InitStack(struct SqStack *S)
{
	S->top = -1;
}

int StackEmpty(struct SqStack S)		//check stack is empty or not
{
	if(S.top == -1) 
	{
		return TURE;
	}
	else 
	{
		return FALSE;
	}
}

void Push(struct SqStack *S, int e)	//push into the stack	
{
	if(S->top == max_size - 1)	//check stack is full
	{
		printf("Stack is full, can not push\n");
	}
	else
	{
		S->top ++;		//top pointer add first, then push stack
		S->elements[S->top] = e;
	}
}

int Pop(struct SqStack *S, int e)	
{
	if(S->top == -1)		//check stack is empty	
	{
		printf("Stack is empty, can not pop\n");
		return ERROR;
	}
	e = S->elements[S->top];	//Pop stack first, then top pointer minus
	S->top --;
	return e;
}

int GetTop(struct SqStack S, int e)
{
	if(S.top == -1)
	{
		printf("Stack is empty, no top element\n");
		return ERROR;
	}
	else
	{
		e = S.elements[S.top];
		return e;
	}
}


int main(int argc, char *argv[])
{
	struct SqStack S;
	InitStack(&S);
	for(int i = 1; i <= 3; i++)
	{
        Push(&S, i);
    }
	//Push(&S, 1);
	//Push(&S, 2);
	//Push(&S, 3);

	int e = 3;
	int a = Pop(&S, e);
	printf("Pop:%d\n", a);
	int b = Pop(&S, e);
	printf("Pop:%d\n", b);
	int c = Pop(&S, e);
	printf("Pop:%d\n", c);

	return 0;
}

