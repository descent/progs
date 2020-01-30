/*
 * for the question
 * https://www.ptt.cc/bbs/C_and_CPP/M.1579751448.A.BB6.html
 */
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  char *ptr="abcdef";
  pid_t pid;

  pid = fork();

  if (pid == 0)
  {
    printf("child ptr: %p\n", ptr);
  }
  else
  {
    printf("parent ptr: %p\n", ptr);
  }

  return 0;
}
