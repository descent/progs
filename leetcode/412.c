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
  char **str_arr;
  str_arr = malloc(n * (sizeof (char *)));
  #endif
  //char str[100];
  const char *fb = "FizzBuzz";
  const char *f = "Fizz";
  const char *b = "Buzz";
  const char *gen_str[] = {
                            "FizzBuzz",
                            "1",
                            "2",
                            "Fizz",
                            "4",
                            "Buzz",
                            "Fizz",
                            "7",
                            "8",
                            "Fizz",
                            "Buzz",
                            "11",
                            "Fizz",
                            "13",
                            "14",
                            "FizzBuzz",
                          };


  //printf("str_arr %p, &str_arr %p\n", str_arr, &str_arr);
  for (int i = 1 ; i <= n ; ++i)
  {
    char *num_str = malloc(20 * sizeof(char));

    if (i<=15)
      str_arr[i-1] = gen_str[i%15];
    else
    {

    //if (i%3==0 && i%5==0)
    if (i%15 == 0)
    {
      str_arr[i-1] = fb;
    }
    else if (i%3==0)
         {
           str_arr[i-1] = f;
         }
         else if (i%5==0)
              {
                str_arr[i-1] = b;
              }
              else
              {
          
                sprintf(num_str, "%d", i);
                str_arr[i-1] = num_str;
              }
               
    }
    //printf("yy %s, &str_arr[i]: %p, str_arr[i]: %p\n", str_arr[i], &str_arr[i], str_arr[i]);
  }
  *returnSize = n;
  return str_arr; 
}


int main(int argc, char *argv[])
{
  int ret_size;
  int n=5;
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
