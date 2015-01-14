#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_LEN 256

int eth(char *cmd_str, int len)
{
  printf("OUTPUT: ");
  printf("%s\n", cmd_str);
}

int end=1;

typedef struct 
{
  char *name;                   /* User printable name of the function. */
  char *doc;                    /* Documentation for this function.  */
}Command;

Command commands[] = 
{
  {"ls", "doc"},
  {"labs", "doc"},
  {"lde", "doc"},
  {"abc", "doc"},
  {"abcd", "doc"},
  {"azz", "doc"},
  {"lbgrde", "doc"},
  {"aa", "doc"},
  {"ab", "doc"},
  {"lacdef", "doc"}
};

#define COMMAND_SIZE (sizeof(commands)/sizeof(Command))

char *command_generator(char *text, int state)
{
  static int list_index, len;
  char *name;

  //printf("xx state: %d\n", state);
  //printf("xx text: %s\n", text);

  /* If this is a new word to complete, initialize now.  This includes
     saving the length of TEXT for efficiency, and initializing the index
     variable to 0. */
  if (!state)
  {
    list_index = 0;
    len = strlen(text);
  }

  int i;
  for (i = list_index ; i < COMMAND_SIZE ; ++i)
  {
    char *name = commands[list_index].name;
    //printf("xx i: %d\n", i);
    list_index++;
    if (strncmp(name, text, len) == 0)
    {
      //printf("xx ret\n");
      return (strdup(name));
    }
  }

#if 0
  if (list_index < sizeof(commands)/sizeof(Command) )
  {
    /* Return the next name which partially matches from the command list. */
    while (name = commands[list_index].name)
    {
      printf("xx list_index: %d\n", list_index);

      list_index++;
      if (strncmp(name, text, len) == 0)
        return (strdup(name));


      if (list_index >= sizeof(commands)/sizeof(Command) )
        break;
    }
  }
#endif

  /* If no names matched, then return NULL. */
  return ((char *) NULL);
}

char **cmd_completion(char *text, int start, int end)
{
  char **matches;

  matches = (char **) NULL;
  printf("\n");
  printf("text: %s\n", text);
  printf("start: %d\n", start);
  printf("end: %d\n", end);

  /* If this word is at the start of the line, then it is a command
     to complete.  Otherwise it is the name of a file in the current
     directory. */
  if (start == 0)
    matches = completion_matches(text, command_generator);

  return (matches);
}

int main(int argc, char *argv[])
{
  char *line;
  int size = sizeof(commands)/sizeof(Command);
  printf("size: %d\n", size);

  char entity[MAX_LEN];
  #if 0
  int instance;
  char para[MAX_LEN];
  char value[MAX_LEN];
  #endif
  //scanw("%s", entity);
  //mvprintw(1, 0, "%s %d %s %s", entity, instance, para, value);

  rl_attempted_completion_function = (CPPFunction *)cmd_completion;

  while(end)
  {
    line = readline("AMIT>");
    add_history(line);

    if (!line)
      break;

    //eth(line, strlen(line));
    if (strcmp(line, "exit") == 0)
      break;
    // lookup table
    // send csid/value/rw/type request to server
  }

  return 0;
}
