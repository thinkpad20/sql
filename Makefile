all: bin/sql_parser
	@echo "Finished! Run ./parsesql.sh <filename> to run the parser."

src/lex.yy.c: src/lex/sql.l 
	$(LEX) -i src/lex/sql.l
	@mv lex.yy.c src

src/y.tab.c: src/yacc/sql.y
	$(YACC) -d -v src/yacc/sql.y
	@mv y.tab.c src
	@mv y.tab.h src
	@mkdir -p src/auxfiles
	@mv y.output src/auxfiles

bin/sql_parser: src/y.tab.c src/lex.yy.c
	@mkdir -p bin
	$(CC) -o bin/sql_parser src/y.tab.c src/lex.yy.c -ly -ll

test: all
	@./parsesql.sh tests/selecttest.sql
	@./parsesql.sh tests/insertintotest.sql
	@./parsesql.sh tests/deletefromtest.sql
	@./parsesql.sh tests/createtest.sql

cleanup:
	-rm test.tab.cacc
	-rm y.output