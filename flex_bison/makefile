mycalc: lex.yy.c y.tab.c y.tab.h
	gcc -o $@ lex.yy.c y.tab.c -lreadline -lfl
lex: lex.yy.c
	gcc -g lex.yy.c  -o $@ -lreadline -lfl

lex.yy.c: mycalc.l
	flex $<

y.tab.c: mycalc.y
	bison --yacc -dv mycalc.y
clean:
	rm -rf *.o lex mycalc
