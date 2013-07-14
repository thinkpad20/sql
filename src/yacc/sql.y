%{

#include <stdio.h>
#include <stdlib.h>
#include "../include/common.h"
#include "../include/create.h"
#include "../include/literal.h"
#include "../include/insert.h"

void yyerror(char *s);
int yylex(void);
extern int yylineno;
#define YYDEBUG 0
int yydebug=0;
int to_print = 0;
int num_stmts = 0;

%}

%union {
	double dval;
	int ival;
	char *strval;
	LiteralVal *lval;
	Constraint *constr;
	ForeignKeyReference fkeyref;
	ChiColumn *col;
	KeyDec *kdec;
	StrList *slist;
}

%token CREATE TABLE INSERT INTO SELECT FROM WHERE FULL
%token PRIMARY FOREIGN KEY DEFAULT CHECK NOT TOKEN_NULL
%token AND OR NEQ GEQ LEQ REFERENCES ORDER BY DELETE
%token AS INT DOUBLE CHAR VARCHAR TEXT USING CONSTRAINT
%token JOIN INNER OUTER LEFT RIGHT NATURAL CROSS UNION
%token VALUES AUTO_INCREMENT ASC DESC UNIQUE IN ON
%token COUNT SUM AVG MIN MAX INTERSECT EXCEPT DISTINCT
%token <strval> IDENTIFIER
%token <strval> STRING_LITERAL
%token <dval> DOUBLE_LITERAL
%token <ival> INT_LITERAL

%type <ival> column_type
%type <strval> column_name table_name
%type <slist> column_names_list opt_column_names
%type <constr> opt_constraints constraints constraint
%type <lval> literal_value values_list
%type <fkeyref> references_stmt
%type <col> column_dec column_dec_list
%type <kdec> key_dec opt_key_dec_list key_dec_list

%start sql_queries

%%

sql_queries
	: sql_query
	| sql_queries sql_query
	;

sql_query
	: sql_line ';' { printf("parsed %d valid SQL statements\n", ++num_stmts); }
	;

sql_line
	: create_table 
	| select 		
	| insert_into 	
	| delete_from 	
	| /* empty */
	;

create_table
	: CREATE TABLE table_name '(' column_dec_list opt_key_dec_list ')' 
		{
			ChiTable *table = CreateTable($3, $5, $6);
			add_table(table);
		}
	;

column_dec_list
	: column_dec { $$ = $1; }
	| column_dec_list ',' column_dec 
		{ 
			printf("column_dec_list: %p column_dec: %p\n", $1, $3);
			$$ = append_column($3, $1); 
		}
	;

column_dec
	: column_name column_type opt_constraints 
		{ 
			/* printf("column '%s' (%d)\n", $1, $2); */
			$$ = Column($1, $2, $3);
		}
	;

column_type
	: INT 			{ $$ = TYPE_INT; }
	| DOUBLE 		{ $$ = TYPE_DOUBLE; }
	| CHAR 			{ $$ = TYPE_CHAR; }
	| VARCHAR 		{ $$ = TYPE_TEXT; }
	| TEXT 			{ $$ = TYPE_TEXT; }
	| column_type '(' INT_LITERAL ')' 
		{ 
			$$ = $1; 
			fprintf(stderr, "Warning: sized types (line %d) "
					 "not supported in chiDB.\n", yylineno); 
		}
	;

opt_key_dec_list
	: ',' key_dec_list {$$ = $2;}
	| /* empty */		 {$$ = NULL; }
	;

key_dec_list
	: key_dec { $$ = $1; }
	| key_dec_list ',' key_dec { $$ = append_key_dec($1, $3); }
	;

key_dec
	: PRIMARY KEY '(' column_names_list ')' 
		{ $$ = PrimaryKeyDec($4); }
	| FOREIGN KEY '(' column_name ')' references_stmt 
		{$$ = ForeignKeyDec(makeFullFKeyReference($4, $6)); }

references_stmt
	: REFERENCES table_name { $$ = makeFKeyReference($2, NULL); }
	| REFERENCES table_name '(' column_name ')' { $$ = makeFKeyReference($2, $4); }
	;

opt_constraints
	: constraints { $$ = $1; }
	| /* empty */ { $$ = NULL; }
	;

constraints
	: constraint { $$ = append_constraint(NULL, $1); 
						/*printf("new constraint:");
						printConstraint($1);
						printf("created a vector of constraints\n");
						printConstraints($$);*/
					 }
	| constraint constraints { $$ = append_constraint($2, $1); 
										/*printf("appended a constraint\n");
										printConstraints($$);*/
									}
	;

constraint
	: NOT TOKEN_NULL { $$ = NotNull(); }
	| UNIQUE				{ $$ = Unique(); }
	| PRIMARY KEY 		{ $$ = PrimaryKey(); }
	| FOREIGN KEY references_stmt { $$ = ForeignKey($3); }
	| DEFAULT literal_value { $$ = Default($2); }
	| AUTO_INCREMENT { $$ = AutoIncrement(); }
	| CHECK bool_expression { $$ = Check(NULL); 
									  fprintf(stderr, "Warning, check not (yet) supported\n"); }
	;

select
	: select_statement
	| select select_combo select_statement
	;

select_combo
	: UNION | INTERSECT | EXCEPT
	;

select_statement
	: SELECT opt_distinct expression_list FROM table opt_select_constraints
	| '(' select_statement ')'
	;

opt_distinct
	: DISTINCT
	| /* empty */
	;

opt_select_constraints
	: select_constraints
	| /* empty */
	;

select_constraints
	: select_constraint
	| select_constraints select_constraint
	;

select_constraint
	: join_condition
	| where_condition
	| orderby
	;

where_condition
	: WHERE bool_expression 
	;

orderby
	: ORDER BY column_name
	| ORDER BY column_name ASC
	| ORDER BY column_name DESC
	;

bool_expression
   : bool_term 
   | bool_term bool_op bool_expression
   ;

bool_term
   : expression comp_op expression
   | expression IN '(' select ')'
   | '(' bool_expression ')'
   | NOT bool_term
   ;

bool_op
	: AND | OR
	;

comp_op
	: '=' | '>' | '<' | GEQ | LEQ | NEQ
	;

expression_list
	: expression
	| expression_list ',' expression
	;

expression
	: expression '+' mulexp 
	| expression '-' mulexp 
	| mulexp 
	;

mulexp
	: mulexp '*' primary 
	| mulexp '/' primary 
	| primary 
	;

primary
	: '(' expression ')' 
	| '-' primary 
	| term 
	;

term
	: literal_value
	| TOKEN_NULL
	| column_reference opt_alias
	| function_name '(' expression ')' 
	;

column_reference
	: column_name_or_star
	| table_name '.' column_name_or_star
	;

opt_alias
	: AS IDENTIFIER
	| IDENTIFIER
	| /* empty */
	;

function_name
	: COUNT | SUM | AVG | MIN | MAX
	;

column_name_or_star
	: '*' 
	| column_name 
	;

column_name
	: IDENTIFIER { $$ = $1; }
	;

table_name
	: IDENTIFIER { $$ = $1; }
	;

table
	: table_def
	| table ',' table_def
	| table join table_def
	;

join_condition
	: ON bool_expression
	| USING '(' column_names_list ')'
	;

table_def
	: table_name opt_alias
	;

join
	: default_join
	| LEFT opt_outer JOIN
	| RIGHT opt_outer JOIN
	| NATURAL JOIN
	| FULL OUTER JOIN
	;

default_join
	: JOIN | CROSS JOIN | INNER JOIN
	;

opt_outer
	: OUTER
	| /* empty */
	;

insert_into
	: INSERT INTO table_name opt_column_names VALUES '(' values_list ')' 
	;

opt_column_names
	: '(' column_names_list ')' { $$ = $2; }
	| /* empty */					 { $$ = NULL; }
	;

column_names_list
	: column_name { $$ = strlist($1, NULL); }
	| column_names_list ',' column_name { $$ = strlist($3, $1); }
	;

values_list
	: literal_value { $$ = $1; }
	| values_list ',' literal_value { $$ = appendLiteralVal($1, $3); }
	;

literal_value
	: INT_LITERAL { $$ = litInt($1); }
	| DOUBLE_LITERAL { $$ = litDouble($1); }
	| STRING_LITERAL
		{
			if (strlen($1) == 1)
				$$ = litChar($1[0]);
			else
				$$ = litText($1);
		}
	;

delete_from
	: DELETE FROM table_name where_condition
	;

%%