#include <stdio.h>

int main(int argc, char *argv[]) {
	int areas[] = {10,12,13,14,20};
	char name[] = "Zed";
	char full_name[] = {'Z','e','d',' ','A', '.', ' ','S','H','a','w','\0'};

	//WARNING on some msystems you might have to change the
	//%ld to a %u since it will use insigned ints
	printf("The size of an int: %u\n", sizeof(int));
	printf("the size of areas (int[]):%u\n", sizeof(areas));
	printf("The numer of ints in areas: %u\n",sizeof(areas)/sizeof(int));
	printf("the first area is %d, the 2nd %d.\n",areas[0], areas[1]);
	printf("the size of a char:%u\n",sizeof(char));
	printf("the size of name (char[]): %u\n",sizeof(name));
	printf("the size of full_name (char[]): %u\n",sizeof(full_name));
	printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

	return 0;

}
