parser: ./lex.l ./yacc.y ../../deps/cJSON/cJSON.c
		bison -d ./yacc.y
		flex ./lex.l
		gcc -o parser lex.yy.c yacc.tab.c ../../deps/cJSON/cJSON.c -g -lfl