// https://www.ptt.cc/bbs/C_and_CPP/M.1460177747.A.36F.html
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
  int *p;
  int len;


  while(1)
  {
    scanf("%d", &len);
    printf("len: %d\n", len);
    if (len == 0)
      break;
    p = (int*)malloc(len * sizeof(int));
    for (int i=0 ; i < len ; ++i)
      scanf("%d", &p[i]);

    for (int i=0 ; i < len ; ++i)
      printf("p[%d]: %d\n",i, p[i]);
    free(p);
  }
  return 0;
}
