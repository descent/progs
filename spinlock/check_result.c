#include <stdio.h>

#include "spinlock.h"

int main(int argc, char *argv[])
{
#if 0
  int i;
  scanf("%d", &i);
  printf("i: %d\n", i);
#else
  FILE *fs;

  printf("open %s to check\n", FN);

  fs = fopen(FN, "r");
  if (fs == NULL)
  {
    perror("fopen fail");
    return -1;
  }

  int time1, time2, time3;
  int line=1;
  int read_len;
  char buf[1000];
  char *ret;
  int error=0;

  while(1)
  {
  #if 1
    ret = fgets(buf, 1000, fs);
    sscanf(buf, "%d\n", &time1);
    //printf("time1: %d\n", time1);
    if (ret == NULL)
      break;

    ret = fgets(buf, 1000, fs);
    sscanf(buf, "%d\n", &time2);
    //printf("time2: %d\n", time2);
    if (ret ==NULL)
      break;

    ret = fgets(buf, 1000, fs);
    sscanf(buf, "%d\n", &time3);
    //printf("time3: %d\n", time3);
    if (ret ==NULL)
      break;

#if 0
    read_len = fscanf(fs, "%d %*\n", &time2);
    printf("time2: %d\n", time2);
    if (read_len == EOF)
      break;
    read_len = fscanf(fs, "%d %*\n", &time3);
    printf("time3: %d\n", time3);
    if (read_len == EOF)
      break;
#endif
    if (time1 == time2 && time2 == time3)
    {
    }
    else
    {
      printf("time1: %d\n", time1);
      printf("time2: %d\n", time2);
      printf("time3: %d\n", time3);
      printf("line %d error\n", line);
      ++error;
    }
    line+=3;
    #endif
  }

  printf("total error: %d\n", error);
  fclose(fs);
#endif
  return 0;
}
