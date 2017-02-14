// url: https://leetcode.com/problems/fizz-buzz/
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** fizzBuzz(int n, int* returnSize) 
{
  //char *template[] = {"1", "2", "fizz"};
  #if 0
  static char *str_arr[3];
  #else
  static char **str_arr;
  str_arr = malloc(n * (sizeof (char *)));
  #endif
  //char str[100];

  //printf("str_arr %p, &str_arr %p\n", str_arr, &str_arr);
  for (int i = 1 ; i <= n ; ++i)
  {
    if (i%3==0 && i%5==0)
    {
      str_arr[i-1] = strdup("FizzBuzz");
    }
    else if (i%3==0)
         {
           str_arr[i-1] = strdup("Fizz");
         }
         else if (i%5==0)
              {
                str_arr[i-1] = strdup("Buzz");
              }
              else
              {
                char num_str[20]; 
          
                sprintf(num_str, "%d", i);
                str_arr[i-1] = strdup(num_str);
              }
    //printf("yy %s, &str_arr[i]: %p, str_arr[i]: %p\n", str_arr[i], &str_arr[i], str_arr[i]);
  }
  *returnSize = n;
  return str_arr; 
}

int main(int argc, char *argv[])
{
  int ret_size;
  int n=15;
  char **str_arr = fizzBuzz(n, &ret_size);
  printf("ret_size: %d\n", ret_size);
  for (int i=0 ; i < ret_size ; ++i)
  {
  #if 1
    char *line = str_arr[i];
  #else
    char *line = *str_arr+i;
  #endif

    printf("zz %d ## %p, %s\n", i, line, line);
    //printf("zz %p: %s\n", line, *line);
    printf("xx %d ## %p: %s\n", i, (str_arr + i), *(str_arr + i));
  }
  
  return 0;
}
