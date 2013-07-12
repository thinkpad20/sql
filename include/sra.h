#ifndef __SRA_H_
#define __SRA_H_

#include "common.h"

/*
SQL:
select f.a as Col1, g.a as Col2 from Foo f, Foo g where Col1 != Col2;
--> To SRA:
ProjectAs([f.a, g.a], [Col1, Col2],
   Select(Col1 != Col2,
      JoinAs([Foo, Foo], [f, g])
   )
)
--> To RA:
Project([Col1, Col2],
   Select(Col1 != Col2,
      Cross(
         Rename(f, [Col1], Foo),
         Rename(g, [Col2], Foo)
      )
   )
)
*/

/*
data SRA = Table String
         | Project [String] [String] SRA  --second string is "as"
         | Select Expression SRA
         | NaturalJoin [SRA] [String]
         | Join [SRA] [String]
         | JoinUsing String [SRA] [String]
         | OuterJoin SRA SRA String String Type
         | Union SRA SRA
         | Difference SRA SRA
         | Intersect SRA SRA
         | Rename SRA String

data Type = Left | Right | Full
*/

typedef struct SRA {

} SRA;

RA *desugar(SRA *sra);

#endif