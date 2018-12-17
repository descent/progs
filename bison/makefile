calc: y.tab.c lex.yy.c
	gcc -o calc y.tab.c lex.yy.c
lex.yy.c: calc.l
	flex $<
y.tab.c: calc.y
	bison -vdty calc.y

clean:
	rm lex.yy.c y.output  y.tab.c  y.tab.h calc
