#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//prototype for search function
void search(char args[]) {
	printf("Passed into search was: %s\n", args);
	const* hi = "/bin";
	execv("ls", **hi);
}

int main(int argc, char *argv[]) {
	printf("The thing to search is: %s\n",argv[1]);
	search(argv[1]);
	return 0;
}	
