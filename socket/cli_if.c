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
#define PARA_SIZE 5

int run_cmd=1;

typedef int (*Func)(const char**token, int len);

typedef struct 
{
  char *name;                   /* User printable name of the function. */
  Func func;
  char *doc;                    /* Documentation for this function.  */
}Command;

Command *find_para(char *name);

int ipaddr(const char**token, int len)
{
  int i=0;
  printf("PARA\n");
  printf("len: %d\n", len);
#if 1
  for (i=0 ; i < len ; ++i)
    printf("token[%d]: %s\n", i, token[i]);
#endif
}

int mask(const char**token, int len)
{
}


Command parameter[] =
{
  {"ipaddr", ipaddr,"doc"},
  {"mask", mask,"doc"},
};


int eth(const char**token, int len)
{
  int i=0;

  printf("len: %d\n", len);
#if 1
  for (i=0 ; i < len ; ++i)
    printf("token[%d]: %s\n", i, token[i]);
#endif

  Command *para;
  para = find_para(token[1]);
  if (para)
  {
    return ((*(para->func)) (token, len));
  }

#if 0
CSID_C_LOCAL_LANIP,
CSID_C_LOCAL_LANNM,
CSID_C_WEBUI_LANSETMASK_GROUPNUM,
CSID_C_DHCP_SVR_IPPOOL_START,
CSID_C_DHCP_SVR_IPPOOL_END,
// need it CSID_S_LOCAL_WANSET_ALTERED ??
CSID_S_PORT_ALTERED,
#endif

}

int quit(const char**token, int len)
{
  run_cmd=0;
  return 0;
}

int ppp(const char**token, int len)
{
  //printf("ARG: %s\n", arg);
}

Command commands[] = 
{
  {"eth", eth, "doc"},
  {"ppp", ppp, "doc"},
  {"exit", quit, "exit"},
  {"quit", quit, "exit"}
#if 0
  {"sim", "doc"},
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
#endif
};
#define COMMAND_SIZE (sizeof(commands)/sizeof(Command))
#define PARAMETER_SIZE (sizeof(parameter)/sizeof(Command))




char *command_generator(const char *text, int state)
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

  /* If no names matched, then return NULL. */
  return ((char *) NULL);
}

char **cmd_completion(const char *text, int start, int end)
{
  char **matches = (char **) NULL;
#if 0
  printf("\n");
  printf("text: %s\n", text);
  printf("start: %d\n", start);
  printf("end: %d\n", end);
#endif
  /* If this word is at the start of the line, then it is a command
     to complete.  Otherwise it is the name of a file in the current
     directory. */
  if (start == 0)
    matches = completion_matches(text, command_generator);

  return (matches);
}

/* Strip whitespace from the start and end of STRING.  Return a pointer
   into STRING. */
char *stripwhite(char *string)
{
  register char *s, *t;

  for (s = string; whitespace(*s); s++)
    ;

  if (*s == 0)
    return (s);

  t = s + strlen(s) - 1;
  while (t > s && whitespace(*t))
    t--;
  *++t = '\0';

  return s;
}


Command *find_command(char *name)
{
  register int i;

  for (i = 0; i < COMMAND_SIZE; i++)
    if (strcmp(name, commands[i].name) == 0)
      return (&commands[i]);

  return ((Command *) NULL);
}

Command *find_para(char *name)
{
  register int i;

  for (i = 0; i < PARAMETER_SIZE; i++)
    if (strcmp(name, parameter[i].name) == 0)
      return (&parameter[i]);

  return ((Command *) NULL);
}

/* Execute a command line. */
int execute_line(char *line)
{
  int i;
  Command *command;
  char *word;

  /* Isolate the command word. */
  i = 0;
  while (line[i] && whitespace(line[i]))
    i++;
  word = line + i;

  while (line[i] && !whitespace(line[i]))
    i++;

  if (line[i])
    line[i++] = '\0';

  command = find_command(word);

  if (!command)
  {
    fprintf(stderr, "%s: No such command for AMIT cli.\n", word);
    return (-1);
  }

  /* Get argument to command, if any. */
  while (whitespace(line[i]))
    i++;

  word = line + i;

  char *arg = word;
  const char *token[PARA_SIZE];
  int t=0;
  i=0;

  while(arg[i])
  {
    while (arg[i] && whitespace(arg[i]))
      i++;
    token[t++] = arg + i;

    while (arg[i] && !whitespace(arg[i]))
      i++;

    if (arg[i])
      arg[i++] = '\0';

    if (t >= PARA_SIZE)
    {
      printf("exceed MAX parameters: %d\n", PARA_SIZE);
      break;
    }

  }
  #if 0
  for (i=0 ; i < t ; ++i)
    printf("token[%d]: %s\n", i, token[i]);
  #endif
  

  /* Call the function. */
  return ((*(command->func)) (token, t));
}

int main(int argc, char *argv[])
{
  char *line;
  printf("COMMAND_SIZE: %d\n", COMMAND_SIZE);

  #if 0
  char entity[MAX_LEN];
  int instance;
  char para[MAX_LEN];
  char value[MAX_LEN];
  #endif

  // rl_bind_key ('\t', rl_insert);
  rl_attempted_completion_function = (CPPFunction *)cmd_completion;

  while(run_cmd)
  {
    line = readline("AMIT> ");
    if (!line)
      break;

    char *s = stripwhite(line);
    if (*s)
    {
      add_history(s);
      execute_line(s);
    }
    free(line);

    // lookup table
    // send csid/value/rw/type request to server
  }

  return 0;
}
