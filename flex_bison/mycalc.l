%{
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#define YY_INPUT(buf,result,max_size) result = mygetinput(buf, max_size);

struct ValType_ {
  int int_val;
  double double_val;
};

#include "y.tab.h"

int val;

// https://stackoverflow.com/questions/36706859/how-to-use-gnu-readline-with-flex-lexer
  static int mygetinput(char *buf, int size) {
    char *line;
    //printf("aa size: %d\n", size); // size: 8192
    if (feof(yyin))  return YY_NULL;
    line = readline("mycal> ");
    if(!line)        return YY_NULL;
    if(strlen(line) > size-2){
       fprintf(stderr,"input line too long\n"); return YY_NULL; }
    sprintf(buf,"%s\n",line);
    add_history(line);
    free(line);
    return strlen(buf);
  }   


int yywrap(void)
{
  return 1;
}

%}

%%
"+"   return ADD;
"-"   return SUB;
"*"   return MUL;
"/"   return DIV;
"("   return LP;
")"   return RP;
"\n"  {printf("aa new line\n"); return CR;}
([1-9][0-9]*)|0|([0-9]+\.[0-9]+) {
  printf("aa dec yytext: %s\n", yytext);
  if (strchr(yytext, '.'))
  {
#if 1
    yylval.val.int_val = 0;

    yylval.val.double_val = strtod(yytext, 0);
    printf("bb double_val: %f\n", yylval.val.double_val);
#endif
  }
  else
  {
#if 1
    yylval.val.double_val = 0;

    yylval.val.int_val = strtol(yytext, 0, 10);
    printf("aa int_val: %d\n", yylval.val.int_val);
#endif
  }

  return INT_LITERAL;
}

(0x[a-f,0-9]*[A-f]*) {
  yylval.val.int_val = strtol(yytext, 0, 16);
  yylval.val.double_val = 0;
  //printf("hex yytext: %s, signed val: %d, unsigned val: %u, hex val: %#x\n", yytext, val, val, val);
  return INT_LITERAL;
}
[ \t]+ {}
.  {
    fprintf(stderr, "lexer error: '%s'\n", yytext);
    exit(1);
}
%%

#if 0
int main()
{
  while (yylex())
  {
  }
}
#endif
