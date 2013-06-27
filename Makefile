all: lex yacc compile

lex: src/lexyacc/sql.l
	$(LEX) -i src/lexyacc/sql.l
	mv lex.yy.c src

yacc: src/lexyacc/sql.y
	$(YACC) -d -v src/lexyacc/sql.y
	mv y.tab.c src
	mv y.tab.h src
	mv y.output src/auxfiles

compile: src/y.tab.c src/lex.yy.c
	$(CC) -o bin/sql_parser src/y.tab.c src/lex.yy.c -ly -ll

test: all
	@./parsesql.sh tests/selecttest.sql
	@./parsesql.sh tests/insertintotest.sql
	@./parsesql.sh tests/deletefromtest.sql
	@./parsesql.sh tests/createtest.sql

cleanup:
	-rm test.tab.cacc
	-rm y.output