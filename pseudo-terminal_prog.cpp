/*
 * use pseudo-terminal to auto fill password or yes to scp.
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <unistd.h>
#include <pty.h>
#include <sys/select.h>


#define SIZE 1024
fd_set rset, wset, testfds_w, testfds_r;

int write_data(int pty, const char *input)
{
  int count=0;

  //while (1)
  {
    int result = select (pty+1, NULL, &testfds_w, NULL, NULL);
    if (FD_ISSET (pty, &testfds_w)) 
    {
      char password[SIZE] = "weiya\n";
      printf("to w\n");
      count=write(pty, input, strlen(input) );
      printf("w: %d\n", count);
      //sleep(5);
    }
  }
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
    const char *fp="/var/log/mmadplayer_play.log";

    if (argc >= 2)
      fp=argv[1];

    execl("/usr/bin/scp", "scp", fp, "weiya@192.168.20.101:/home/weiya/logfile/", NULL);
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

#if 1

    while(1)
    {
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
        printf("r: %d\n", count);
        message[count]=0;
        printf("msg: %s\n", message);
        if (strstr(message, "password:")!=NULL)
        {
          printf("pwd\n");
          strcpy(input, "weiya\n");
        }
        if (strstr(message, "yes")!=NULL)
        {
          printf("yy\n");
          strcpy(input, "yes\n");
        }
        printf("input: %s\n", input);

        write_data(pty, input);


      }



    }
#endif



  }

  return 0;
}
