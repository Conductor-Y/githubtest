#include <stdio.h>

int main(int argc, char *argv[])
{

  int i = 0;
  while(i < argc) 
	{
      printf("arg %d: %s\n", i, argv[i]);
      i++;
  }

  char *states[] = 
	{
      "California", "Oregon",
      "Washington", "Texas"
  };

  int num_states = 4;
  i = num_states;  
  while(i) 
	{
      printf("state %d: %s\n", i - 1, states[i - 1]);
      i--;
  }

  return 0;
}
