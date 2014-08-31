#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
//initialize an empy array called name
  char name[40];

//print a dialogue for input
  printf("Enter Your Name: ");

//take the data, %39 means a maximum of 39 characters
//can be input (cause of \0)
  scanf("%39s", name);
//takes in a string and starts with the pointer of
//first position of name
  
//initialize empy int called age
  int age;
  printf("Enter Your Age: ");
//for ints you need an & unlike arrays since they are already
//pointers to an address

  scanf("%i",&age);

  printf("%s, %i\n", name, age);
}


