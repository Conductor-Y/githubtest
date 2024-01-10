#include <stdio.h>

struct Person
{
	char name[20];
	int age;
	int height;
	int weight;
};

void print_person(struct Person person)
{
	printf("Name:%s\n", person.name);
  printf("Age:%d\n", person.age);
  printf("Height:%d\n", person.height);
  printf("Weight:%d\n", person.weight);
}

int main(int argc, char *argv[])
{
	struct Person person;

	snprintf(person.name, sizeof(person.name), "Joe holy");
	person.age = 25;
	person.height = 175;
	person.weight = 70;
	
	printf("Name:%s\n", person.name);
	printf("Age:%d\n", person.age);
	printf("Height:%d\n", person.height);
	printf("Weight:%d\n", person.weight);

	print_person(person);

	return 0;
}
