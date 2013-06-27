%{

#include <stdio.h>
#include <stdlib.h>
void yyerror(char *s);

%}

%token CREATE TABLE INSERT INTO SELECT FROM WHERE
%token PRIMARY FOREIGN KEY DEFAULT CHECK NOT NULL
%token AND OR NEQ GEQ LEQ REFERENCES ORDER BY DELETE
%token AS IDENTIFIER INT DOUBLE CHAR VARCHAR TEXT
%token JOIN INNER OUTER LEFT RIGHT NATURAL UNION
%token VALUES AUTO INCREMENT ASC DESC STRING_LITERAL
%token INT_LITERAL DOUBLE_LITERAL UNIQUE IN TRUE FALSE

%%

bool_expression
   : bool_term 
   | bool_term bool_op bool_expression
   ;

bool_term
   : expression comp_op expression
   | expression IN IDENTIFIER
   | '(' bool_expression ')'
   | NOT bool_term
   ;

bool_op
   : AND | OR
   ;

comp_op
   : '>' | '<' | GEQ | LEQ | NEQ
   ;

expression
   : term
   | term op expression 
   ;

term
   : IDENTIFIER
   | unary_op term
   | '(' expression ')'
   ;

op
   : '+' | '-' | '*' | '/'
   ;

unary_op
   : '-'
   ;

%%