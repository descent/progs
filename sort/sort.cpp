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

#define IN_PLACE
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

#ifdef IN_PLACE
//ref: http://emn178.pixnet.net/blog/post/88613503-%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F%E6%B3%95%28quick-sort%29

  std::swap(s[pivot_index], s[end]);
  int swap_index=begin;
  for (int i = begin ; i < end ; ++i)
  {
    if (s[i] <= pivot)
    {
      std::swap(s[i], s[swap_index]);
      ++swap_index;
    }
  }
  std::swap(s[end], s[swap_index]);

#else
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
#endif

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

void quick_sort(char *str, int left, int right)
{
  int pivot_index = partition(str, left, right);

#if 0
  printf("new pivot_index: %d\n", pivot_index);
  print_array(str, len);
  printf("===\n");
#endif

  // handle left
  if ((pivot_index - left) > 1)
  {
    //printf("left\n");
    //pivot_index = partition(str, 0, pivot_index-1);
    //printf("new pivot_index: %d\n", pivot_index);

    printf("(0, %d)\n", pivot_index-1);
    quick_sort(str, 0, pivot_index-1);
  }

  if ((right - pivot_index) > 1)
  {
    //printf("right\n");
    //pivot_index = partition(str+pivot_index+1, pivot_index+1, len-1);
    //printf("new pivot_index: %d\n", pivot_index);
    int l = pivot_index + 1;
    printf("(%d, %d)\n", l, right);
    quick_sort(str+l, 0, right - pivot_index - 1);
  }
}

int main(int argc, char *argv[])
{
  //bubble_sort();
  //insertion_sort();

  DATA("zxyabcdefg")
  printf("org:\n");
  print_array(str, len);
  quick_sort(str, 0, len-1);
  printf("quick sorting:\n");
  print_array(str, len);
  return 0;
}
