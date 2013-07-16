#include "../include/sra.h"

SRA_t *SRATable(TableReference_t *ref) {
   SRA_t *sra = (SRA_t *)calloc(1, sizeof(SRA_t));
   sra->t = SRA_TABLE;
   sra->table.ref = ref;
   return sra;
}

SRA_t *SRAProject(SRA_t *sra, Expression_t *expr) {
   SRA_t *new_sra = (SRA_t *)calloc(1, sizeof(SRA_t));
   new_sra->t = SRA_PROJECT;
   new_sra->project.sra = sra;
   new_sra->project.expr_list = expr;
   return new_sra;
}

SRA_t *SRASelect(SRA_t *sra, Condition_t *cond) {
   SRA_t *new_sra = (SRA_t *)calloc(1, sizeof(SRA_t));
   new_sra->t = SRA_SELECT;
   new_sra->select.sra = sra;
   new_sra->select.cond = cond;
   return new_sra;
}

SRA_t *SRANaturalJoin(SRAList_t *sras) {
   SRA_t *new_sra = (SRA_t *)calloc(1, sizeof(SRA_t));
   new_sra->t = SRA_NATURAL_JOIN;
   new_sra->natjoin.sras = sras;
   return new_sra;
}

SRA_t *SRAJoin(SRAList_t *sras, JoinCondition_t *cond) {
   SRA_t *new_sra = (SRA_t *)calloc(1, sizeof(SRA_t));
   new_sra->t = SRA_JOIN;
   new_sra->join.sras = sras;
   new_sra->join.opt_cond = cond;
   return new_sra;
}

SRA_t *SRAOuterJoin(enum OJType t, SRAList_t *sras, JoinCondition_t *cond) {
   SRA_t *new_sra = (SRA_t *)calloc(1, sizeof(SRA_t));
   new_sra->t = SRA_OUTER_JOIN;
   new_sra->ojoin.t = t;
   new_sra->ojoin.sras = sras;
   new_sra->ojoin.opt_cond = cond;
   return new_sra;
}

static SRA_t *SRABinary(SRA_t *sra1, SRA_t *sra2, enum SRAType t) {
   SRA_t *sra = (SRA_t *)calloc(1, sizeof(SRA_t));
   sra->t = t;
   sra->binary.sra1 = sra1;
   sra->binary.sra2 = sra2;
   return sra;
}

SRA_t *SRAUnion(SRA_t *sra1, SRA_t *sra2) {
   return SRABinary(sra1, sra2, SRA_UNION);
}

SRA_t *SRAExcept(SRA_t *sra1, SRA_t *sra2) {
   return SRABinary(sra1, sra2, SRA_EXCEPT);
}

SRA_t *SRAIntersect(SRA_t *sra1, SRA_t *sra2) {
   return SRABinary(sra1, sra2, SRA_INTERSECT);
}


void SRA_print(SRA_t *sra) {
   if (!sra) return;
   switch(sra->t) {
      case SRA_TABLE:
         indent_print("Table(%s", sra->table.ref->table_name);
         if (sra->table.ref->alias) printf(" as %s", sra->table.ref->alias);
         printf(")");
         break;
      case SRA_SELECT:
         indent_print("Select(");
         Condition_print(sra->select.cond);
         printf(", ");
         upInd();
         SRA_print(sra->select.sra);
         downInd();
         indent_print(")");
         break;
      case SRA_PROJECT:
         indent_print("Project(");
         Expression_printList(sra->project.expr_list);
         printf(", ");
         upInd();
         SRA_print(sra->project.sra);
         downInd();
         indent_print(")");
         break;
      case SRA_UNION:
         indent_print("Union(");
         upInd();
         SRA_print(sra->binary.sra1);
         indent_print(", ");
         SRA_print(sra->binary.sra2);
         downInd();
         indent_print(")");
         break;
      case SRA_EXCEPT:
         indent_print("Except(");
         upInd();
         SRA_print(sra->binary.sra1);
         indent_print(", ");
         SRA_print(sra->binary.sra2);
         downInd();
         indent_print(")");
         break;
      case SRA_INTERSECT:
         indent_print("Intersect(");
         upInd();
         SRA_print(sra->binary.sra1);
         indent_print(", ");
         SRA_print(sra->binary.sra2);
         downInd();
         indent_print(")");
         break;
      case SRA_JOIN:
         indent_print("Join(");
         upInd();
         SRA_print(sra->binary.sra1);
         indent_print(", \n");
         SRA_print(sra->binary.sra2);
         if (sra->join.opt_cond)
            JoinCondition_print(sra->join.opt_cond);
         downInd();
         indent_print(")");
         break;
      case SRA_NATURAL_JOIN:
         indent_print("NaturalJoin(");
         upInd();
         SRAList_print(sra->natjoin.sras);
         downInd();
         indent_print(")");
         break;
      case SRA_OUTER_JOIN:
         if (sra->ojoin.t == OJ_LEFT) printf("Left");
         else if (sra->ojoin.t == OJ_RIGHT) printf("Right");
         else if (sra->ojoin.t == OJ_FULL) printf("Full");
         else printf("Unknown");
         indent_print("OuterJoin(");
         upInd();
         SRAList_print(sra->ojoin.sras);
         if (sra->ojoin.opt_cond)
            JoinCondition_print(sra->ojoin.opt_cond);
         downInd();
         indent_print(")");
         break;
      default:
         puts("Unknown SRA type");
   }
}

void JoinCondition_print(JoinCondition_t *cond) {
   if (cond->on) {
      printf("on ");
      Condition_print(cond->on);
   }
   if (cond->using_list) {
      printf("using ");
      StrList_print(cond->using_list);
   }
}

void SRAList_print(SRAList_t *sras) {
   int first = 1;
   printf("[");
   while (sras) {
      if (first) first = 0; else printf(", ");
      SRA_print(sras->sra);
      sras = sras->next;
   }
   printf("]");
}

SRAList_t *SRAList_make(SRA_t *sra) {
   SRAList_t *list = (SRAList_t *)calloc(1, sizeof(SRAList_t));
   list->sra = sra;
   return list;
}

static SRAList_t *SRAList_app(SRAList_t *list1, SRAList_t *list2) {
   list1->next = list2;
   return list1;
}

SRAList_t *SRAList_append(SRAList_t *list1, SRAList_t *list2) {
   if (!list1) return list2;
   return SRAList_app(list1, SRAList_append(list1->next, list2));
}