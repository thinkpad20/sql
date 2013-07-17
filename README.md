## SQL Parser

This can parse a reasonably large subset of SQL. I'm using lex and yacc. The parser generates an abstract syntax tree which is based on Relational Algebra, extended to fit closer with SQL. This extended relational algebra is termed SRA (sugared relational algebra), as it itself can be compiled into more or less pure relational algebra. The data structures and functions for constructing an RA syntax tree are written; however, the SRA to RA compiler is not.

Since relational algebra primarily deals with only queries, there are separate data structures to deal with Create Table, Create Index, Insert Into, and Delete From (and possibly other things in the future). These don't use RA, but they do, for example, use the Expression part of the abstract syntax tree.

## Installation and Usage

Clone into the git repository:

```
> git clone https://github.com/thinkpad20/sql.git
```

Compile:

```
> cd sql
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