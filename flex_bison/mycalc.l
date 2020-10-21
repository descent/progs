%{
#include <stdio.h>
#include "y.tab.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#define YY_INPUT(buf,result,max_size) result = mygetinput(buf, max_size);

int val;

// https://stackoverflow.com/questions/36706859/how-to-use-gnu-readline-with-flex-lexer
  static int mygetinput(char *buf, int size) {
    char *line;
    //printf("aa size: %d\n", size); // size: 8192
    if (feof(yyin))  return YY_NULL;
    line = readline("> ");
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
"\n"  {printf("aa new line\n"); return CR;}
([1-9][0-9]*)|0|([0-9]+\.[0-9]+) {
  val = strtol(yytext, 0, 10);
  yylval.int_val = val;
  printf("aa dec yytext: %s, val: %d\n", yytext, val);
  return INT_LITERAL;
}

(0x[0-9]*[a-f]*[A-f]*) {
  val = strtol(yytext, 0, 16);
  yylval.int_val = val;
  printf("bb hex yytext: %s, val: %d\n", yytext, val);
  return INT_LITERAL;
}
[ \t]+ {}
.  {
    fprintf(stderr, "lexer error: %s\n", yytext);
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
