%{

#include <stdio.h>
#include <stdlib.h>
#include "../include/common.h"
#include "../include/create.h"
#include "../include/vector.h"
#include "../include/literal.h"
#include "../include/insert.h"
#include "../include/ra.h"
#include "../include/condition.h"
#include "../include/expression.h"
#include "../include/delete.h"

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
	Literal_t *lval;
	Constraint_t *constr;
	ForeignKeyRef_t fkeyref;
	Column_t *col;
	KeyDec_t *kdec;
	StrList_t *slist;
	Insert_t *ins;
	Condition_t *cond;
	Expression_t *expr;
	ColumnReference_t *colref;
	ChiDelete *del;
}

%token CREATE TABLE INSERT INTO SELECT FROM WHERE FULL
%token PRIMARY FOREIGN KEY DEFAULT CHECK NOT TOKEN_NULL
%token AND OR NEQ GEQ LEQ REFERENCES ORDER BY DELETE
%token AS INT DOUBLE CHAR VARCHAR TEXT USING CONSTRAINT
%token JOIN INNER OUTER LEFT RIGHT NATURAL CROSS UNION
%token VALUES AUTO_INCREMENT ASC DESC UNIQUE IN ON
%token COUNT SUM AVG MIN MAX INTERSECT EXCEPT DISTINCT
%token CONCAT TRUE FALSE CASE WHEN DECLARE BIT
%token <strval> IDENTIFIER
%token <strval> STRING_LITERAL
%token <dval> DOUBLE_LITERAL
%token <ival> INT_LITERAL

%type <ival> column_type bool_op comp_op function_name
%type <strval> column_name table_name opt_alias column_name_or_star
%type <slist> column_names_list opt_column_names
%type <constr> opt_constraints constraints constraint
%type <lval> literal_value values_list in_statement
%type <fkeyref> references_stmt
%type <col> column_dec column_dec_list
%type <kdec> key_dec opt_key_dec_list key_dec_list
%type <ins> insert_into
%type <cond> condition bool_term where_condition
%type <expr> expression mulexp primary expression_list term
%type <colref> column_reference
%type <del> delete_from

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
			Table_t *table = Table_make($3, $5, $6);
			add_table(table);
		}
	;

column_dec_list
	: column_dec { $$ = $1; }
	| column_dec_list ',' column_dec 
		{ 
			$$ = Column_append($1, $3); 
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
			if ($3 <= 0) {
				fprintf(stderr, "Error: sizes must be greater than 0 (line %d).\n", yylineno);
				exit(1);
			}
			Column_setSize($3);
			fprintf(stderr, "****WARNING: sized types (line %d) "
					 "not yet supported in chiDB.\n", yylineno); 
		}
	;

opt_key_dec_list
	: ',' key_dec_list {$$ = $2;}
	| /* empty */		 {$$ = NULL; }
	;

key_dec_list
	: key_dec { $$ = $1; }
	| key_dec_list ',' key_dec { $$ = KeyDec_append($1, $3); }
	;

key_dec
	: PRIMARY KEY '(' column_names_list ')' 
		{ $$ = PrimaryKeyDec($4); }
	| FOREIGN KEY '(' column_name ')' references_stmt 
		{$$ = ForeignKeyDec(ForeignKeyRef_makeFull($4, $6)); }

references_stmt
	: REFERENCES table_name { $$ = ForeignKeyRef_make($2, NULL); }
	| REFERENCES table_name '(' column_name ')' { $$ = ForeignKeyRef_make($2, $4); }
	;

opt_constraints
	: constraints { $$ = $1; }
	| /* empty */ { $$ = NULL; }
	;

constraints
	: constraint { $$ = Constraint_append(NULL, $1); 
						/*printf("new constraint:");
						Constraint_print($1);
						printf("created a vector of constraints\n");
						Constraint_printList($$);*/
					 }
	| constraint constraints { $$ = Constraint_append($2, $1); 
										/*printf("appended a constraint\n");
										Constraint_printList($$);*/
									}
	;

constraint
	: NOT TOKEN_NULL { $$ = NotNull(); }
	| UNIQUE				{ $$ = Unique(); }
	| PRIMARY KEY 		{ $$ = PrimaryKey(); }
	| FOREIGN KEY references_stmt { $$ = ForeignKey($3); }
	| DEFAULT literal_value { $$ = Default($2); }
	| AUTO_INCREMENT { $$ = AutoIncrement(); }
	| CHECK condition { $$ = Check($2); 
									  fprintf(stderr, "****WARNING, check not yet supported in chiDB\n"); }
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
		{
			/* printf("List of expressions to select: ");
			Expression_printList($3);
			puts(""); */
		}
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
	: WHERE condition { $$ = $2; }
	;

orderby
	: ORDER BY column_name
	| ORDER BY column_name ASC
	| ORDER BY column_name DESC
	;

condition
   : bool_term { $$ = $1; /*printf("Found condition: \n"); Condition_print($$); puts(""); */}
   | bool_term bool_op condition 
   	{ 
   		$$ = ($2 == AND) ? And($1, $3) : Or($1, $3); 
   		/* printf("Found condition: \n"); Condition_print($$); puts(""); */
   	}
   ;

bool_term
   : expression comp_op expression 
   	{
   		$$ = ($2 == '=') ? Eq($1, $3) :
   			  ($2 == '>') ? Gt($1, $3) :
   			  ($2 == '<') ? Lt($1, $3) :
   			  ($2 == GEQ) ? Leq($1, $3) :
   			  ($2 == LEQ) ? Geq($1, $3) :
   			  Not(Eq($1, $3));
   	}
   | expression in_statement { $$ = In($1, $2); }
   | '(' condition ')' 	{ $$ = $2; }
   | NOT bool_term 		{ $$ = Not($2); }
   ;

in_statement
	:  IN '(' values_list ')' { $$ = $3; }
	|	IN '(' select ')'
   	{
   		fprintf(stderr, "****WARNING: IN SELECT statement not yet supported\n");
   	}
   ;

bool_op
	: AND { $$ = AND; } 
	| OR { $$ = OR; }
	;

comp_op
	: '=' { $$ = '='; } 
	| '>' { $$ = '>'; } 
	| '<' { $$ = '<'; } 
	| GEQ { $$ = GEQ; } 
	| LEQ { $$ = LEQ; } 
	| NEQ { $$ = NEQ; } 
	;

expression_list
	: expression opt_alias { $$ = add_alias($1, $2); }
	| expression_list ',' expression opt_alias { $$ = append_expression($1, add_alias($3, $4)); }
	;

expression
	: expression '+' mulexp { $$ = Plus($1, $3); }
	| expression '-' mulexp { $$ = Minus($1, $3); }
	| mulexp						{ $$ = $1; }
	;

mulexp
	: mulexp '*' primary 	{ $$ = Multiply($1, $3); }
	| mulexp '/' primary 	{ $$ = Divide($1, $3); }
	| mulexp CONCAT primary { $$ = Concat($1, $3); }
	| primary 					{ $$ = $1; }
	;

primary
	: '(' expression ')' 	{ $$ = $2; }
	| '-' primary 				{ $$ = Neg($2); }
	| term 						{ $$ = $1; } 
	;

term
	: literal_value			{ $$ = TermLiteral($1); }
	| TOKEN_NULL				{ $$ = TermNull(); }
	| column_reference		{ $$ = TermColumnReference($1); }
	| function_name '(' expression ')' { $$ = TermFunction($1, $3); }
	;

column_reference
	: column_name_or_star { $$ = ColumnReference_make(NULL, $1); }
	| table_name '.' column_name_or_star
		 { $$ = ColumnReference_make($1, $3); }
	;

opt_alias
	: AS IDENTIFIER { $$ = $2; }
	| IDENTIFIER { $$ = $1; }
	| /* empty */ { $$ = NULL; }
	;

function_name
	: COUNT { $$ = FUNC_COUNT; }
	| SUM { $$ = FUNC_SUM; }
	| AVG { $$ = FUNC_AVG; }
	| MIN { $$ = FUNC_MIN; }
	| MAX{ $$ = FUNC_MAX; }
	;

column_name_or_star
	: '*' { $$ = "*"; }
	| column_name { $$ = $1; }
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
	: ON condition
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
		{
			$$ = Insert_make(Table($3), $4, $7);
			Insert_print($$);
		}
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
	| values_list ',' literal_value 
		{ 
			$$ = Literal_append($3, $1); 

		}
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
		{
			$$ = makeDelete($3, $4);
			printDelete($$);
			puts("");
		}
	;

%%