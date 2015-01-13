#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <readline/readline.h>
#include <readline/history.h>

int end=1;

int main(int argc, char *argv[])
{
  char *line, *s;

  while(end)
  {
    line = readline("AMIT>");
    add_history(line);

    if (!line)
      break;
  }
  return 0;
}
