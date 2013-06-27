%{

#include <stdio.h>
#include <stdlib.h>
void yyerror(char *s);
int yylex(void);

%}

%union {
	double dval;
	int ival;
	const char *strval;
}

%token CREATE TABLE INSERT INTO SELECT FROM WHERE
%token PRIMARY FOREIGN KEY DEFAULT CHECK NOT TOKEN_NULL
%token AND OR NEQ GEQ LEQ REFERENCES ORDER BY DELETE
%token AS IDENTIFIER INT DOUBLE CHAR VARCHAR TEXT
%token JOIN INNER OUTER LEFT RIGHT NATURAL UNION
%token VALUES AUTO INCREMENT ASC DESC UNIQUE IN
%token COUNT SUM AVG MIN MAX
%token <strval> STRING_LITERAL
%token <dval> DOUBLE_LITERAL
%token <ival> INT_LITERAL

%start function

%%

sql_query
	: sql_line ';' { puts("you entered valid SQL"); }
	;

sql_line
	: create_table { puts ("you created a column."); }
	| select { puts ("you selected something."); }
	| insert_into { puts ("you inserted a row."); }
	| delete_from { puts ("you deleted a row."); }
	| /* empty */
	;

create_table
	: CREATE TABLE table_name '(' column_dec_list ')'
	;

column_dec_list
	: column_dec { puts ("you entered a column dec list"); }
	| column_dec ',' column_dec_list
	;

column_dec
	: column_name column_type constraints { puts ("you entered a column."); }
	| key_dec
	;

column_type
	: type { puts ("you entered a column type."); }
	| type '(' INT_LITERAL ')' { puts ("you entered a column type with a size."); }
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
	| select UNION select_statement
	;

select_statement
	: SELECT expression_list FROM table where_clause orderby_clause
	| '(' select_statement ')'
	;

where_clause
	: WHERE bool_expression { puts ("you entered a where clause");}
	| /* empty */
	;

orderby_clause
	: ORDER BY column_name
	| ORDER BY column_name ASC
	| ORDER BY column_name DESC
	| /* empty */
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
	: '>' | '<' | GEQ | LEQ | NEQ
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
	| function
	;

function
	: '*'
	| column_name  { puts ("you entered a column name");}
	| table_name '.' column_name  { puts ("you entered a table name");}
	| function_name '(' expression ')'  { puts ("you entered a function call");}
	;

function_name
	: COUNT | SUM | AVG | MIN | MAX
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
	| table_def join table_def
	;

table_def
	: table_name
	| table_name AS IDENTIFIER
	| table_name IDENTIFIER
	;

join
	: JOIN
	| INNER JOIN
	| LEFT opt_outer JOIN
	| RIGHT opt_outer JOIN
	| NATURAL JOIN
	;

opt_outer
	: OUTER
	| /* empty */
	;

insert_into
	: INSERT INTO table_name column_names VALUES '(' values_list ')'
	;

column_names
	: '(' column_names_list ')'
	| /* empty */
	;

column_names_list
	: column_name
	| column_name ',' column_names_list
	;

values_list
	: literal_value
	| literal_value ',' values_list
	;

literal_value
	: INT_LITERAL
	| DOUBLE_LITERAL
	| STRING_LITERAL /* covers chars, varchars and text */
	;

delete_from
	: DELETE FROM table_name where_clause
	;

%%