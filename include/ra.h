#ifndef __RA_H_
#define __RA_H_

#include "common.h"
#include "condition.h"

/*
RA_t in Haskell
data RA_t = Table String
        | Select Expression_t RA_t -- see below for Expression_t def
        | Project [String] RA
        | Union RA_t RA
        | Difference RA_t RA
        | Cross RA_t RA
        | Rename String [String] RA
*/

typedef struct RA_Table_t {
   char *name;
} RA_Table_t;

typedef struct RA_Sigma_t {
   Condition_t *cond;
   RA_t *ra;
} RA_Sigma_t;

typedef struct RA_Pi_t {
   Expression_t *expr_list;
   RA_t *ra;
} RA_Pi_t;

typedef struct RA_Binary {
   RA_t *ra1, *ra2;
} RA_Binary;

typedef struct RA_Rho_t {
   char *table_name, *new_name;
   Expression_t *expr_to_rename;
   RA_t *ra;
} RA_Rho_t;

enum RA_Type {
   RA_TABLE, 
   RA_SIGMA, 
   RA_PI, 
   RA_UNION, 
   RA_DIFFERENCE, 
   RA_CROSS, 
   RA_RHO_TABLE,
   RA_RHO_EXPR,
};

struct RA_s {
   enum RA_Type t;
   union {
      RA_Table_t table;
      RA_Sigma_t sigma;
      RA_Pi_t pi;
      RA_Binary binary;
      RA_Rho_t rho;
   };
};

void RA_print(RA_t *ra);

RA_t *Table(const char *name);
RA_t *Sigma(RA_t *ra, Condition_t *expr);
RA_t *Pi(RA_t *ra, Expression_t *expr_list);
RA_t *Union(RA_t *ra1, RA_t *ra2);
RA_t *Difference(RA_t *ra1, RA_t *ra2);
RA_t *Cross(RA_t *ra1, RA_t *ra2);
RA_t *Rho(RA_t *ra, const char *table_name, unsigned num_col_names, ...);

void RA_free(RA_t *ra);

#endif
