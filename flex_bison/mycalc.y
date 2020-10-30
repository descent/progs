%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYDEBUG 1
int yylex (void);
int yyerror(char const *str);

%}
%union{
  int int_val;
}
%token <int_val> INT_LITERAL
%token ADD SUB MUL DIV CR LP RP
%type <int_val> expression term primary_expression
%%
line_list
    : line
    | line_list line
    ;
line
    : expression CR
    {
      printf("result val: %d (%#x)\n", $1, $1);
    }
    ;
expression
    : term
    | expression ADD term
    {
      $$ = $1 + $3;
      printf("add: %d\n", $$);
    }
    | expression SUB term
    {
      $$ = $1 - $3;
    }
    ;
term
    : primary_expression
    | term MUL primary_expression
    {
      $$ = $1 * $3;
    }
    | term DIV primary_expression
    {
      $$ = $1 / $3;
    }
primary_expression
    : INT_LITERAL
    | LP expression RP
    {
      $$ = $2;
    }
    | SUB primary_expression
    {
      $$ = -$2;
    }
%%
int yyerror(char const *str)
{
  extern char *yytext;
  fprintf(stderr, "'%s' parser error near ", str);
  if (strcmp(yytext, "\n") == 0)
  {
    fprintf(stderr, "'new_line'\n");
  }
  else
    fprintf(stderr, "'%s'\n", yytext);
  return 0;
}


int main()
{
  int yyparse(void);
  extern FILE *yyin;
  
  yyin = stdin;
  while (yyparse())
  {
    fprintf(stderr, "error!!\n");
    //exit(1);
  }
  printf("exit yyparse()\n");

}
