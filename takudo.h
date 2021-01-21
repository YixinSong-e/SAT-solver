#ifndef TAKUDO_H_INCLUDED
#define TAKUDO_H_INCLUDED

int judgeJie(int);
char *convertToCnf(const char *);
void mainProgram(int jieshu,char *takudo,FILE *writeTo);
void linedfs(int level,int *,int,int,FILE *);
void constraintone(int jieshu,FILE *writeTo);
void constrainttwo(int jieshu,FILE *writeTo);
void constraintthree(int jieshu,FILE *writeTo);
void CreateUnitClause(char *,FILE *writeTo,int);
#endif // TAKUDO_H_INCLUDED
