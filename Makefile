all: lex yacc compile
	@echo "Finished! Run ./parsesql.sh <filename> to run the parser."

lex: src/lex/sql.l
	@$(LEX) -i src/lex/sql.l
	@mv lex.yy.c src

yacc: src/yacc/sql.y
	@$(YACC) -d -v src/yacc/sql.y
	@mv y.tab.c src
	@mv y.tab.h src
	@mkdir -p src/auxfiles
	@mv y.output src/auxfiles

compile: src/y.tab.c src/lex.yy.c
	@$(CC) -o bin/sql_parser src/y.tab.c src/lex.yy.c -ly -ll

test: all
	@./parsesql.sh tests/selecttest.sql
	@./parsesql.sh tests/insertintotest.sql
	@./parsesql.sh tests/deletefromtest.sql
	@./parsesql.sh tests/createtest.sql

cleanup:
	-rm test.tab.cacc
	-rm y.output