//#include <stdio.h>
//#include <math.h>
#include <cstring>
// ref: http://stackoverflow.com/questions/2302969/how-to-implement-char-ftoafloat-num-without-sprintf-library-function-i

// http://c-faq.com/fp/round.html
//C's floating to integer conversion truncates (discards) the fractional part

/*
  * Program to convert float number to string without using sprintf
  */

#include <iostream>
#include <string>
//#include <cmath>

const int PRECISION = 10;

using namespace std;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

u8* s32_itoa(u32 n, u8* str, int radix)
{
  char digit[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  u8* p=str;
  u8* head=str;
  //int radix = 10;

//  if(!p || radix < 2 || radix > 36)
//    return p;
  if (n==0)
  {
    *p++='0';
    *p=0;
    return str;
  }
  if (radix == 10 && n < 0)
  {
    *p++='-';
    n= -n;
  }
  while(n)
  {
    *p++=digit[n%radix];
    //s32_put_char(*(p-1), (u8*)(0xb8000+80*2));
    n/=radix;
  }
  *p=0;
  #if 1
  for (--p; head < p ; ++head, --p)
  {
    char temp=*head;
    if (*(p-1) != '-')
    {
      *head=*p;
      *p=temp;
    }
  }
  #endif
  return str;
}

int mypow(int x, int y)
{
  int r=1;
  for (int i=0 ; i < y ; ++i)
    r*=x;
  return r;
}

u8*  floatToString(float num)
{
   int whole_part = num;
   int digit = 0, reminder =0;
   //int log_value = log10(num), 
   int index;
   float wt = 0.0;

   // String containg result
   static u8 str[20];

   //Initilise stirng to zero
   //memset(str, 0 ,20);
   
   //u8 whole_str[20] ;
   s32_itoa(whole_part, str, 10);
#if 0
   //Extract the whole part from float num
   for(int  i = 1 ; i < log_value + 2 ; i++)
   {
       wt  =  mypow(10,i);
       reminder = whole_part  %  wt;
       digit = (reminder - digit) / (wt/10);

       //Store digit in string
       str[index--] = digit + 48;              // ASCII value of digit  = digit + 48
       if (index == -1)
          break;    
   }
#endif
    //index = log_value + 1;
    index = strlen((const char*)str);
    str[index] = '.';

   float fraction_part  = num - whole_part;
   float tmp1 = fraction_part,  tmp =0;

   cout << "fraction_part: " << fraction_part << endl;
   cout << "num: " << num << endl;
   cout << "whole_part: " << whole_part << endl;

   //Extract the fraction part from  num
   for( int i= 1; i < PRECISION; i++)
   {
      wt =10; 
      tmp  = tmp1 * wt;
      digit = tmp;
      //cout << "digit: " << digit << endl;
      cout << "tmp: " << tmp << endl;
      cout << "tmp1: " << tmp1 << endl;

      //Store digit in string
      str[++index] = digit +48;           // ASCII value of digit  = digit + 48
      tmp1 = tmp - digit;
      if (tmp1 == 0.0)
        break;
   }    
   str[index] = 0;

   return str;
}


//Main program
int main()
{
  int i;
  //float f = 123456.789;
  double f = 987.1234567;
  u8* str =  floatToString(f);
  cout  << "org f: 987.1234567\n";
  cout  << endl <<  str << endl;
  return 0;
}
