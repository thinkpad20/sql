#ifndef __SRA_H_
#define __SRA_H_

#include "common.h"

/*
SQL:
select f.a as Col1, g.a as Col2 from Foo f, Foo g where Col1 != Col2;

--> To SRA:
Pi([(f,a,Col1), (g,a,Col2)],
   Sigma(Col1 != Col2,
      Join([(Foo,f), (Foo,g)])
   )
)

--> To RA:
Pi([Col1, Col2],
   Sigma(Col1 != Col2,
      Cross(
         Rho(Foo, f, [Col1]),
         Rho(Foo, g, [Col2])
      )
   )
)
*/

/*
data SRA = Table TableName
         | Pi [Alias] SRAAlias
         | Sigma Condition SRA
         | NaturalJoin [SRA]
         | Join [SRA] (Maybe JoinCondition)
         | OuterJoin [SRA] OJType (Maybe JoinCondition)
         | Union SRA SRA
         | Difference SRA SRA
         | Intersect SRA SRA

data OJType = Left 
            | Right 
            | Full

data ColumnName = ColumnName (Maybe String) String
data TableName = TableName String (Maybe String)
data JoinCondition = On Condition
                   | Using [String]

data Expression = ColumnRef ColumnName
                | LitInt Integer
                | LitDouble Double
                | LitChar Char
                | LitText String
                | Concat Expression Expression
                | Add Expression Expression
                | Subtract Expression Expression
                | Multiply Expression Expression
                | Divide Expression Expression

data Alias = Alias Expression (Maybe String) -- for naming expressions
*/

typedef struct SRA {

} SRA;

RA *desugar(SRA *sra);

#endif