#include <stdio.h>
#include <math.h>

typedef unsigned char u8;
typedef unsigned int u32;

#define PRECISION 6

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

u32 s_strlen(const char *s)
{
  u8 len=0;

  while(*s++)
    ++len;
  return len;
}

u8* float_to_str(float num)
{
  int whole_part = num;
  float fraction_part  = num - whole_part;

  if (num < 0)
  {
    whole_part = -num;
    fraction_part  = -num - whole_part;
  }

   int digit = 0, reminder =0;
   //int log_value = log10(num), 
   int index;
   float wt = 0.0;
   int i=0;

   // String containg result
   static u8 str[30];

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
    index = s_strlen((const char*)str);
    str[index] = '.';

   float tmp1 = fraction_part,  tmp =0;

#if 0
   cout << "fraction_part: " << fraction_part << endl;
   cout << "num: " << num << endl;
   cout << "whole_part: " << whole_part << endl;
#endif
   //Extract the fraction part from  num
   for(i=1; i < PRECISION; i++)
   {
      wt =10; 
      tmp  = tmp1 * wt;
      digit = tmp;
      //cout << "digit: " << digit << endl;
      //cout << "tmp: " << tmp << endl;
      //cout << "tmp1: " << tmp1 << endl;

      //Store digit in string
      str[++index] = digit +48;           // ASCII value of digit  = digit + 48
      tmp1 = tmp - digit;
      if (tmp1 == 0.0)
        break;
   }    
   str[index+1] = 0;

  if (num < 0)
  {
    static u8 neg_str[30+1]={'-'};
    int i=0;
    int len = s_strlen((const char*)str);
    for (i=0 ; i < len ; ++i)
    {
      neg_str[i+1] = str[i];
    }
    neg_str[i+1] = 0;
    return neg_str;
  }
  return str;
}

int main(int argc, char *argv[])
{
  float fv=-1.35*2.3;

  printf("neg fv: %s\n", float_to_str(fv));
  fv=1.35*2.3;
  printf("neg fv: %s\n", float_to_str(fv));

  float v=2.5;
  printf("cos(%f): %s\n", v, float_to_str(cos(v)));
  printf("sin(%f): %s\n", v, float_to_str(sin(v)));

  return 0;
}
