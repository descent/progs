/*
 * use pseudo-terminal to auto fill password or yes to scp.
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <unistd.h>
#include <pty.h>
#include <sys/select.h>


#define SIZE 10240
fd_set rset, wset, testfds_w, testfds_r;

int write_data(int pty, const char *input)
{
  int count=0;

}

int main(int argc, char *argv[])
{
  int pty,child;
  int ret;


  child = forkpty(&pty,0,0,0);


  if(!child)
  {
    struct termios tios;

    tcgetattr(0, &tios);
    tios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
    tios.c_oflag &= ~(ONLCR);
    tcsetattr(0, TCSANOW, &tios);

    execl("/home/descent/git/progs/h", "h", NULL);
    //execv(argv[1],&argv[1]);
    //execl("/bin/ls", "./ls", "/", "/home", NULL);
  }
  else
  {
    char message[SIZE];
    int count=0;

    FD_ZERO (&rset);
    FD_SET (pty, &rset);
    FD_ZERO (&wset);
    FD_SET (pty, &wset);
    char input[SIZE] = "weiya\n";
    int i=0;

    while(1)
    {
      const char *send_to_h[] = {"123\n", "abc\n", "hello\n", ""};
      testfds_w = wset;
      testfds_r = rset;
      //struct timeval timeout;
      //timeout.tv_sec=2;
      //timeout.tv_usec=500000;
      int result = select (pty+1, &testfds_r, NULL, NULL, NULL);
      if (result == -1)
      {
        continue;
      }

      if (FD_ISSET (pty, &testfds_r)) 
      {
        count=read(pty, message, SIZE);
        if (count == -1)
          return 0;
        printf("message: %s\n", message);

      }

      if (strcmp(send_to_h[i], "") != 0)
      {
	result = select (pty+1, NULL, &testfds_w, NULL, NULL);
	if (FD_ISSET (pty, &testfds_w)) 
	{
	  count=write(pty, send_to_h[i], strlen(send_to_h[i]) );
	}
	++i;
      }
    }



  }

  return 0;
}
