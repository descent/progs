%{

#include <stdio.h>
#include <stdlib.h>
#define YYDEBUG 1

%}
%union{
  int int_val;
}
%token <int_val> INT_LITERAL
%token ADD SUB MUL DIV CR
%type <int_val> expression term primary_expression
%%
line_list
    : line
    | line_list line
    ;
line
    : expression CR
    {
      printf("aa val: %d (%#x)\n", $1, $1);
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
%%
int yyerror(char const *str)
{
  extern char *yytext;
  fprintf(stderr, "parser error near '%s'\n", yytext);
  return 0;
}


int main()
{
  int yyparse(void);
  extern FILE *yyin;
  
  yyin = stdin;
  if (yyparse())
  {
    fprintf(stderr, "error !!\n");
    exit(1);
  }

}
