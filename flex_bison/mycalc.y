%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYDEBUG 1
int yylex (void);
int yyerror(char const *str);

struct ValType_ {
  int int_val;
  double double_val;
};


%}

%union{
  struct ValType_ val;
}
%token <val> INT_LITERAL
%token ADD SUB MUL DIV CR LP RP
%type <val> expression term primary_expression
%%
line_list
    : line
    | line_list line
    ;
line
    : expression CR
    {
      //printf("result val: %d (%#x)\n", $1, $1);
    }
    ;
expression
    : term
    | expression ADD term
    {
      
      if ( ($1.int_val != 0) && ($3.int_val != 0) )
      {
        $$.int_val = $1.int_val + $3.int_val;
        printf("add: %d (%#x)\n", $$.int_val, $$.int_val);
      }
      else
      {
        $$.double_val = $1.double_val + $1.int_val + $3.double_val + $3.int_val;
        printf("add: %f\n", $$.double_val);
      }

      //$1.int_val;
    }
    | expression SUB term
    {
      //$$ = $1 - $3;
      if ( ($1.int_val != 0) && ($3.int_val != 0) )
      {
        $$.int_val = $1.int_val - $3.int_val;
        printf("minus: %d (%#x)\n", $$.int_val, $$.int_val);
      }
      else
      {
        double v1 = $1.double_val != 0 ? $1.double_val : $1.int_val;
        double v2 = $3.double_val != 0 ? $3.double_val : $3.int_val;

        $$.double_val = v1 - v2;
        printf("minus: %f\n", $$.double_val);
      }
    }
    ;
term
    : primary_expression
    | term MUL primary_expression
    {
      //$$ = $1 * $3;
      if ( ($1.int_val != 0) && ($3.int_val != 0) )
      {
        $$.int_val = $1.int_val * $3.int_val;
        printf("mul: %d (%#x)\n", $$.int_val, $$.int_val);
      }
      else
      {
        double v1 = $1.double_val != 0 ? $1.double_val : $1.int_val;
        double v2 = $3.double_val != 0 ? $3.double_val : $3.int_val;

        $$.double_val = v1 * v2;
        printf("mul: %f\n", $$.double_val);
      }
    }
    | term DIV primary_expression
    {
      //$$ = $1 / $3;
      if ( ($1.int_val != 0) && ($3.int_val != 0) )
      {
        $$.int_val = $1.int_val / $3.int_val;
        printf("div: %d (%#x)\n", $$.int_val, $$.int_val);
      }
      else
      {
        double v1 = $1.double_val != 0 ? $1.double_val : $1.int_val;
        double v2 = $3.double_val != 0 ? $3.double_val : $3.int_val;

        $$.double_val = v1 / v2;
        printf("div: %f\n", $$.double_val);
      }
    }
primary_expression
    : INT_LITERAL
    | LP expression RP
    {
      //$$ = $2;
    }
    | SUB primary_expression
    {
      //$$ = -$2;
    }
%%

#include "y.tab.h"

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
