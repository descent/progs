#include <stdio.h>
#include <stdlib.h>
#include <linux/keyboard.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/kd.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/vt.h>



termios oldTm;
long oldKbMode;


int main(int argc, char **argv) 
{


        tcgetattr(STDIN_FILENO, &oldTm);

        ioctl(STDIN_FILENO, KDGKBMODE, &oldKbMode);
        //setRawMode(false, true);

        termios tm = oldTm;
        cfmakeraw(&tm);
        tm.c_cc[VMIN] = 1;
        tm.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &tm);


  kbentry entry;

  #define T_SHIFT (1 << KG_SHIFT)
  #define T_CTRL (1 << KG_CTRL)
  #define T_CTRL_ALT ((1 << KG_CTRL) + (1 << KG_ALT))
  
  entry.kb_table = T_CTRL_ALT;
  entry.kb_index = KEY_1;
  entry.kb_value = 0x10;
  ioctl(STDIN_FILENO, KDSKBENT, &entry);

  entry.kb_table = T_CTRL_ALT;
  entry.kb_index = KEY_2;
  entry.kb_value = 0x11;
  ioctl(STDIN_FILENO, KDSKBENT, &entry);

  const int BUFSIZE=128;
  char buf[BUFSIZE]; 
  int nread;
  while(1)
  {
    nread = read (STDIN_FILENO, buf, BUFSIZE);
    printf("nread: %d\n", nread);
    for (int i=0 ; i < nread ; ++i)
      printf("%x\n", buf[i]);
  }
  
  return 0;
}
