#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

// provide str, len variable
#define DATA(unsort) \
  char str[] = unsort; \
  int len = strlen(str); 

void print_array(char *s, int len)
{
  printf("***\n");
  for (int i=0 ; i < len ; ++i)
    printf("%c ", s[i]);
  printf("\n");
  printf("******\n");
}

int partition(char *s, int begin, int end)
{
  char left[100];
  char right[100];
  int left_index=0;
  int right_index=0;
  int len = end - begin + 1;
  int pivot_index = len/2;
  char pivot = s[len/2];

  //print_array(s, len);
  //printf("pivot = s[%d] = %c\n", pivot_index, pivot);

  for (int i=0 ; i < len ; ++i)
  {
    if (i == pivot_index)
      continue;
    if (s[i] < pivot)
      left[left_index++] = s[i];
    else
      right[right_index++] = s[i];
  }

#if 0
  print_array(left, left_index);
  printf("\n");
  print_array(right, right_index);
#endif

  memcpy(s, left, left_index);
  s[left_index] = pivot;
  memcpy(s+left_index+1, right, right_index);

  return left_index;
}

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

void quick_sort(char *str, int len)
{
  int pivot_index = partition(str, 0, len-1);
  printf("new pivot_index: %d\n", pivot_index);
  print_array(str, len);
  printf("===\n");

  if ((pivot_index - 0) > 1)
  {
    printf("left\n");
    pivot_index = partition(str, 0, pivot_index-1);
    printf("new pivot_index: %d\n", pivot_index);
  }

  if ((len - 1 - pivot_index) > 1)
  {
    printf("right\n");
    pivot_index = partition(str+pivot_index+1, pivot_index+1, len-1);
    printf("new pivot_index: %d\n", pivot_index);
  }
  printf("===\n");
  print_array(str, len);
  printf("===\n");
}

int main(int argc, char *argv[])
{
  //bubble_sort();
  //insertion_sort();

  DATA("986251374")
  quick_sort(str, len);

  return 0;
}
