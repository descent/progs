/*
 *  vfork test
 */
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
int a=1;
  printf("before a: %d\n", a);

  pid_t pid = vfork();
  //pid_t pid = fork();
  if (pid == 0)
  { // child
    ++a;
    printf("vfork: child ## a: %d\n", a);
    while(1);
    //exit(2);
  }
  else
  {  // parent
    printf("vfork: parent ## a: %d\n", a);
    while(1);
  }
  return 0;
}
