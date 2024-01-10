#include <stdio.h>

int main(int argc, char *argv[])
{
	int a[6];
	a[0] = 10;
	a[1] = 20;
	a[2] = 30;
	a[3] = 40;
	a[4] = 50;
	a[5] = 'Y';
	char b[] = "Yuan";
	char c[] = {'z', 'e', 'w', ' ', '\0'};
	int i = 0;

	printf("%ld %ld\n", sizeof(int), sizeof(a));
	printf("%ld\n", sizeof(a) / sizeof(int));
	printf("%ld %ld\n", sizeof(char), sizeof(b));
	printf("%ld\n", sizeof(b) / sizeof(char));
	printf("%ld\n", sizeof(c) / sizeof(char));
	
	for(i=0; i<6; i++)
	{
		printf("%d\n", a[i]);	
	}
	return 0;
}
