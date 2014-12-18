#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

#define DATA(unsort) \
  char str[] = unsort; \
  int len = strlen(str); 

void insertion_sort()
{
  DATA("98765")

  printf("== %s: \n", __FUNCTION__);
  printf("org str: %s\n", str);

  for (int i=1 ; i < len ; ++i)
  {
    int key = str[i];

    int k = i-1;
    for (; k >= 0 ; --k)
    {
      if (str[k] > key)
      {
        str[k+1] = str[k];
      }
      else
      {
        break;
      }
    }
    str[k+1] = key;
  }
  printf("sorting str: %s\n", str);
}

void bubble_sort()
{
  
  DATA("987654321")

  printf("== %s: \n", __FUNCTION__);
  printf("org str: %s\n", str);

  for (int k=len ; k > 0 ; --k)
  {
    for (int i=0 ; i < k-1 ; ++i)
    {
      if (str[i] > str[i+1])
        swap(str[i], str[i+1]);
    }
  }

  printf("sorting str: %s\n", str);
}

int main(int argc, char *argv[])
{
  bubble_sort();
  insertion_sort();

  return 0;
}
