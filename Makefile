all: lex yacc compile

lex: sql.l
	lex -i sql.l

yacc: sql.y
	yacc -d -v sql.y

compile: y.tab.c lex.yy.c
	$(CC) -o sql_parser y.tab.c lex.yy.c -ly -ll

test: all
	@./parsesql.sh selecttest.sql
	@./parsesql.sh insertintotest.sql
	@./parsesql.sh deletefromtest.sql
	@./parsesql.sh createtest.sql

cleanup:
	-rm test.tab.cacc
	-rm y.output