DEPS = bin/list.o bin/create.o bin/ra.o bin/literal.o bin/common.o \
		 bin/insert.o bin/condition.o bin/expression.o bin/column.o \
		 bin/delete.o bin/sra.o bin/vector.o bin/mock_db.o
OPTS = -Wall

all: init bin/sql_parser
	@echo "Finished building!"

src/lex.yy.c: src/lex/sql.l 
	$(LEX) -i src/lex/sql.l
	@mv lex.yy.c src

src/y.tab.c: src/yacc/sql.y
	$(YACC) -d -v src/yacc/sql.y
	@mv y.tab.c src
	@mv y.tab.h src
	@mkdir -p src/auxfiles
	@mv y.output src/auxfiles

bin/list.o: src/list.c
	$(CC) $(OPTS) -c src/list.c -o bin/list.o

bin/mock_db.o: src/mock_db.c
	$(CC) $(OPTS) -c src/mock_db.c -o bin/mock_db.o

bin/vector.o: src/vector.c
	$(CC) $(OPTS) -c src/vector.c -o bin/vector.o

bin/create.o: src/create.c
	$(CC) $(OPTS) -c src/create.c -o bin/create.o

bin/ra.o: src/ra.c
	$(CC) $(OPTS) -c src/ra.c -o bin/ra.o

bin/sra.o: src/sra.c
	$(CC) $(OPTS) -c src/sra.c -o bin/sra.o

bin/literal.o: src/literal.c
	$(CC) $(OPTS) -c src/literal.c -o bin/literal.o

bin/common.o: src/common.c
	$(CC) $(OPTS) -c src/common.c -o bin/common.o

bin/insert.o: src/insert.c
	$(CC) $(OPTS) -c src/insert.c -o bin/insert.o

bin/delete.o: src/delete.c
	$(CC) $(OPTS) -c src/delete.c -o bin/delete.o

bin/condition.o: src/condition.c
	$(CC) $(OPTS) -c src/condition.c -o bin/condition.o

bin/expression.o: src/expression.c
	$(CC) $(OPTS) -c src/expression.c -o bin/expression.o

bin/column.o: src/column.c
	$(CC) $(OPTS) -c src/column.c -o bin/column.o

deps: bin/list.o bin/vector.o bin/create.o bin/ra.o bin/literal.o \
		bin/common.o bin/insert.o bin/condition.o bin/expression.o \
		bin/column.o bin/delete.o bin/sra.o bin/mock_db.o

bin/sql_parser: src/y.tab.c src/lex.yy.c deps
	@mkdir -p bin
	$(CC) $(OPTS) -o bin/sql_parser src/y.tab.c src/lex.yy.c $(DEPS) -ly -ll

tests: selecttest inserttest deletetest createtest errortest

selecttest: all
	@bin/sql_parser tests/selecttest.sql

inserttest: all
	@bin/sql_parser tests/insertintotest.sql

deletetest: all
	@bin/sql_parser tests/deletefromtest.sql

createtest: all
	@bin/sql_parser tests/createtest.sql

errortest: all
	@bin/sql_parser tests/errortest.sql

createselecttest: all
	@bin/sql_parser tests/createselecttest.sql

init:
	@mkdir -p bin

cleanup:
	-rm test.tab.cacc
	-rm y.output

clean:
	rm bin/*