#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void string_print(char *pass); 
void print_reverse(char *pass);
void every_other(char *pass);

int main(int argc, char *argv[]) {
  char input;
  printf("Enter Option: ");
  scanf("%c", &input);
  switch(input) {
    case 'r':
    case 'R':
      print_reverse(*argv);
      break;
    case 'f':
    case 'F':
      string_print(*argv);
      break;
  }

  return 0;
}

//call the prototype
void string_print(char *pass) {
  printf("Enter index:");
  int index[10];
  scanf("%d",index);
  printf("%s\n", (pass+*index));
}

void print_reverse(char *pass) {
  int i = 0;
  char j = 'A'; 
  while(1==1) {
    j = pass[i];
    i++;
    int count;
    if(j == '\0') {
      for(count=i-1; count>=0;count--) {
        printf("%c",pass[count]);
      }
      printf("\n");
      break;
    }
  }
}

void every_other(char *pass) {

}
