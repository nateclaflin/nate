#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
	//create a pointer to Person and allocate size of the struct that
	//holds it
	struct Person *who = malloc(sizeof(struct Person));

	//makes sure memory was properly allocated
	assert(who != NULL);
	
	//initialize all the variables yo
	//string duplicate function to make sure struct owns it
	who->name = strdup(name);
	who->age = age;
	who->height = height;
	who->weight = weight;

	//returns the person struct fully filled out
	return who;
}

void Person_destroy(struct Person *who)
{
	//again make sure pointer isn't null
	assert(who != NULL);

	//clean up from malloc
	free(who->name);
	free(who);
}

void Person_print(struct Person *who)
{
	//access each individual piece from struct and print
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
	printf("\tHeight: %d\n", who->height);
	printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[]) {
	//make two people structures
	struct Person *joe = Person_create(
		"Joe Alex", 32, 64, 140);

	struct Person *frank = Person_create(
		"Frank Blank", 20, 72, 180);

	//print them out and where they are in memory
	printf("Joe is at memory location %p:\n", joe);
	Person_print(joe);

	printf("Frank is at memory location %p:\n", frank);
	Person_print(frank);

	//make everyones age 20 years and print them again
	joe->age += 20;
	joe->height -= 2;
	joe->weight += 40;
	Person_print(joe);

	frank->age += 20;
	frank->weight += 20;
	Person_print(frank);

	//destroy them both so we clean up
	Person_destroy(joe);
	Person_destroy(frank);

	return 0;
}
