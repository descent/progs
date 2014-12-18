#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
  
  char str[] = "987654321";
  int len = strlen(str);

  printf("org str: %s\n", str);

  for (int k=len ; k > 0 ; --k)
  {
    for (int i=0 ; i < k-1 ; ++i)
    {
      if (str[i] > str[i+1])
        swap(str[i], str[i+1]);
    }
  }

  printf("sort str: %s\n", str);

  return 0;
}
