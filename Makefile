DEPS = bin/vector.o bin/create.o bin/ra.o bin/literal.o bin/common.o

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

bin/vector.o: src/vector.c
	$(CC) -c src/vector.c -o bin/vector.o

bin/create.o: src/create.c
	$(CC) -c src/create.c -o bin/create.o

bin/ra.o: src/ra.c
	$(CC) -c src/ra.c -o bin/ra.o

bin/literal.o: src/literal.c
	$(CC) -c src/literal.c -o bin/literal.o

bin/common.o: src/common.c
	$(CC) -c src/common.c -o bin/common.o

deps: bin/vector.o bin/create.o bin/ra.o bin/literal.o bin/common.o

bin/sql_parser: src/y.tab.c src/lex.yy.c deps
	@mkdir -p bin
	$(CC) -o bin/sql_parser src/y.tab.c src/lex.yy.c $(DEPS) -ly -ll

test: all
	@./parsesql.sh tests/selecttest.sql
	@./parsesql.sh tests/insertintotest.sql
	@./parsesql.sh tests/deletefromtest.sql
	@./parsesql.sh tests/createtest.sql

cleanup:
	-rm test.tab.cacc
	-rm y.output

clean:
	rm bin/*