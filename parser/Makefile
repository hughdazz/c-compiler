parser: lex.l yacc.y
		bison -d yacc.y
		flex lex.l
		gcc -o parser lex.yy.c yacc.tab.c -lfl