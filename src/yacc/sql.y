%{

#include <stdio.h>
#include <stdlib.h>

void yyerror(char *s);
int yylex(void);
#define YYDEBUG 0
int yydebug=0;
int to_print = 0;
int num_stmts = 0;

void puts_mod(const char *line) {
	if (to_print) { puts(line); }
}

%}

%union {
	double dval;
	int ival;
	const char *strval;
}

%token CREATE TABLE INSERT INTO SELECT FROM WHERE
%token PRIMARY FOREIGN KEY DEFAULT CHECK NOT TOKEN_NULL
%token AND OR NEQ GEQ LEQ REFERENCES ORDER BY DELETE
%token AS INT DOUBLE CHAR VARCHAR TEXT USING
%token JOIN INNER OUTER LEFT RIGHT NATURAL CROSS UNION
%token VALUES AUTO INCREMENT ASC DESC UNIQUE IN ON
%token COUNT SUM AVG MIN MAX INTERSECT EXCEPT DISTINCT
%token <strval> IDENTIFIER
%token <strval> STRING_LITERAL
%token <dval> DOUBLE_LITERAL
%token <ival> INT_LITERAL

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
	: CREATE TABLE table_name '(' column_dec_list ')' 
	;

column_dec_list
	: column_dec 
	| column_dec ',' column_dec_list
	;

column_dec
	: column_name column_type opt_constraints 
	| key_dec
	;

column_type
	: type 
	| type '(' INT_LITERAL ')' 
	;

type
	: INT
	| DOUBLE
	| CHAR
	| VARCHAR
	| TEXT
	;

key_dec
	: primary_key_dec
	| foreign_key_dec
	;

primary_key_dec
	: PRIMARY KEY '(' column_names_list ')'
	;

foreign_key_dec
	: FOREIGN KEY '(' column_name ')' references_stmt
	;

references_stmt
	: REFERENCES table_name
	| REFERENCES table_name '(' column_name ')'
	;

opt_constraints
	: constraints
	| /* empty */
	;

constraints
	: constraint
	| constraint constraints
	;

constraint
	: NOT TOKEN_NULL
	| UNIQUE
	| PRIMARY KEY
	| FOREIGN KEY references_stmt
	| DEFAULT default_stmt
	| CHECK bool_expression
	;

default_stmt
	: literal_value
	| AUTO INCREMENT
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
	| opt_table_qualifier column_name_or_star opt_alias
	| function_name '(' expression ')' 
	;

opt_table_qualifier
	: table_name '.'
	| /* empty */
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
	: IDENTIFIER
	;

table_name
	: IDENTIFIER 
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
	: '(' column_names_list ')'
	| /* empty */
	;

column_names_list
	: column_name
	| column_names_list ',' column_name
	;

values_list
	: literal_value
	| values_list ',' literal_value
	;

literal_value
	: INT_LITERAL
	| DOUBLE_LITERAL
	| STRING_LITERAL /* covers chars, varchars and text */
	;

delete_from
	: DELETE FROM table_name where_condition
	;

%%