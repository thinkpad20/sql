## SQL Parser

This can parse a reasonably large subset of SQL. I'm using lex and yacc as front-ends. Currently, it is mostly just a recognizing parser. However, I'm building up a lot of machinery to represent an abstract syntax tree for Relational Algebra and a sugared variant, as well as some other important commands in SQL (create table, insert, etc).

## Installation and Usage

Clone into the git repository:

```
> git clone https://github.com/thinkpad20/sql.git
> cd sql
```

Compile:

```
> make
```

See some example tests with

```
> make test
```

Parse an arbitrary SQL file with

```
> ./parsesql.h <filename>
```