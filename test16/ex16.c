#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
	char *name;
	int age;
	int height;
	int weight;
};

struct Person *Person_creat(char *name, int age, int height, int weight)
{
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL);	//check the pointer is not a null pointer

	who->name = strdup(name);	//give the vaule of name to the pointer who which points name(why use strdup because name point a string) 
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;
}

void Person_destory(struct Person *who)
{
	assert(who != NULL);
	free(who->name);
	free(who);
}

void Person_print(struct Person *who)
{
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
	printf("\tHeight: %d\n", who->height);
	printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
	struct Person *Joe = Person_creat("Joe Alex", 20, 64, 140);
	struct Person *Frank = Person_creat("Frank Blank", 20, 72, 180);

	printf("Joe is at memory location %p:\n", Joe);
	printf("Frank is at memory location %p:\n", Frank);
	Joe->age += 20;
	Joe->height -= 2;
	Joe->weight += 40;
	Person_print(Joe);

	Frank->age += 20;
  Frank->weight += 20;
  Person_print(Frank);

	Person_destory(Joe);
	Person_destory(Frank);

	return 0;
}

