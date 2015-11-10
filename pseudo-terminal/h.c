#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char line[100];
  printf("begin:\n"); 
  while(1)
  {
    
    printf("abc:\n"); 
    fgets(line, 99, stdin);
    printf("input is : %s\n", line);
    if (strcmp(line, "hello\n")==0)
    {
      printf("got it\n");
      break;
    }

  }
  return 0;
}
