#define LEGAL_PSW "my.good.password"

#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
  char user_pwd[600];
  printf("neter password: ");
  scanf("%s", user_pwd);
  //printf("pwd: %s\n", user_pwd);
  if (strcmp(user_pwd, LEGAL_PSW) == 0)
  {
    printf("password ok, hi!\n");
  }
  else
  {
    printf("worng passwd\n");
  }
  return 0;
}
