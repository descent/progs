#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;

int compare(const void *a, const void *b)
{
  char a1 = *(char *)a;
  char b1 = *(char *)b;
  if (a1 < b1)
    return -1;
  else if (a1 > b1)
       {
         return 1;
       }
       else
         return 0;
}

int main(int argc, char *argv[])
{
  
  char str[] = "125439876";
  int len = strlen(str);

  printf("org str: %s\n", str);

  qsort(str, len, 1, compare);

  printf("qsort str: %s\n", str);

  return 0;
}
