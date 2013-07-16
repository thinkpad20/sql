#ifndef __RA_H_
#define __RA_H_

#include "common.h"
#include "condition.h"

/*
RA in Haskell
data RA = Table String
        | Select Expression_t RA -- see below for Expression_t def
        | Project [String] RA
        | Union RA RA
        | Difference RA RA
        | Cross RA RA
        | Rename String [String] RA
*/

typedef struct RA_Table {
   char *name;
} RA_Table;

typedef struct RA_Sigma {
   Condition_t *cond;
   RA *ra;
} RA_Sigma;

typedef struct RA_Pi {
   Expression_t *expr_list;
   RA *ra;
} RA_Pi;

typedef struct RA_Binary {
   RA *ra1, *ra2;
} RA_Binary;

typedef struct RA_Rho {
   char *table_name;
   unsigned num_col_names;
   char **col_names;
   RA *ra;
} RA_Rho;

enum RA_Type {
   RA_TABLE, 
   RA_SIGMA, 
   RA_PI, 
   RA_UNION, 
   RA_DIFFERENCE, 
   RA_CROSS, 
   RA_RHO
};

struct RA {
   enum RA_Type t;
   union {
      RA_Table table;
      RA_Sigma sigma;
      RA_Pi pi;
      RA_Binary binary;
      RA_Rho rho;
   } ra;
};

void printRA(RA *ra);

RA *Table(const char *name);
RA *Sigma(RA *ra, Condition_t *expr);
RA *Pi(RA *ra, Expression_t *expr_list);
RA *Union(RA *ra1, RA *ra2);
RA *Difference(RA *ra1, RA *ra2);
RA *Cross(RA *ra1, RA *ra2);
RA *Rho(RA *ra, const char *table_name, unsigned num_col_names, ...);

void deleteRA(RA *ra);

#endif