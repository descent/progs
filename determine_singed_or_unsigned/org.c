// from: Expert C Programming - Deep C Secretes
// Write Some Code to Determine if a Variable Is Signed or Not
// the book answer is wrong in ansi c

#include <stdio.h>

#define ORG_ISUNSIGNED_TYPE(type) ((type)0 - 1 > 0)
#define ORG_ISUNSIGNED(a) (a >= 0 && ~a >= 0)

// from: http://stackoverflow.com/questions/7316862/how-to-determine-whether-a-variable-is-unsigned-or-not-in-ansi-c
//
#define ISUNSIGNED_TYPE(type) ((type)(0 - 1) > 0)
#define ISUNSIGNED(a) (a>=0 && ((a=~a)>=0 ? (a=~a, 1) : (a=~a, 0)))

int main(int argc, char *argv[])
{
  unsigned short a=0x1;
  printf("determine by org_ macro\n");
  printf("determine: 'unsigned short'\n");
  if (ORG_ISUNSIGNED_TYPE(unsigned short))
    printf("  unsigned type\n");
  else
    printf("  signed type\n");

  printf("determine: 'variable a'\n");
  if (ORG_ISUNSIGNED(a))
    printf("  unsigned type\n");
  else
    printf("  signed type\n");

  printf("\ndetermine by new macro\n");

  printf("determine: 'unsigned short'\n");
  if (ISUNSIGNED_TYPE(unsigned short))
    printf("  unsigned type\n");
  else
    printf("  signed type\n");

  printf("determine: 'variable a'\n");
  if (ISUNSIGNED(a))
    printf("  unsigned type\n");
  else
    printf("  signed type\n");
  return 0;
}

