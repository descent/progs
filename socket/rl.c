#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <unistd.h>


int end=1;

// ref: http://blog.yam.com/ddy1280/article/7040231
unsigned char waitkey(void)
{
    unsigned char c=0;
    unsigned char *p;
    struct termios new_t, old_t;
    tcgetattr(0, &old_t);
    new_t = old_t;
    new_t.c_lflag &= (ICANON);
    new_t.c_lflag &= (~ECHO);
    new_t.c_cc[VTIME] = 0;
    new_t.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_t);

    rl_done=1;
    //readline() accepting that many characters
    rl_num_chars_to_read=1;
    p=readline("");
    rl_num_chars_to_read=0;//no limit

    c=p[0];
    free(p);
    tcsetattr(0, TCSANOW, &old_t);
    c = _rl_to_lower(c);
    return c;
}


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
