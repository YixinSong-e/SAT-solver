#ifndef CNF_H_INCLUDED
#define CNF_H_INCLUDED
#define STLEN 80

char *smallFile[5];
char *midFile[5];
char *largeFile[5];
char *baseFuncFile[4];
char *unSatisFile[4];
char fileName[100];
void init();
//子句结构
struct clause
{
    struct clause *nextClause;
    struct literal *firstLiteral;
};
//文字结构
struct literal
{
    int theLiteral;
    struct literal *nextLiteral;
};
//子句集
struct clauseSet
{
    int literal_count;
    int clause_count;
    struct clause *firstClause;
};



struct clauseSet readCnf(const char *);
struct literal * createLiteral(int);
struct clause * createClause(struct literal *);
void traverse(struct clauseSet);



struct result
{
    int state;
    int literal_count;
    int * arrHead; //
};

struct literalFrequency
{
    int frequency;
    int iD;
}literal_frequency[20000];
struct StackNode
{
    struct clauseSet data;
    int otherChoice;
    struct StackNode * next;
};
struct StackNode * push(struct StackNode *, struct clauseSet, int);
struct StackNode * pop(struct StackNode *, struct clauseSet *, int *);
struct StackNode * push2(struct StackNode *head, struct clauseSet currentClauseSet, int anotherChoice);
struct StackNode * pop2(struct StackNode *head, struct clauseSet *currentClauseSet, int *anotherLiteral);
struct result dfs(struct clauseSet currClauseSet,struct result myResult,int myLiteral);
struct result DPLL(struct clauseSet);
struct result DPLL2(struct clauseSet currClauseSet);
struct clauseSet unit_propagate(struct clauseSet, int, struct result *);
int findUnitLiteral(struct clauseSet, struct result *);
void freeLiteral(struct literal *);
void freeClause(struct clause *);

void showResult(struct result);
void showResulttotakudo(struct result,int );
void showOriginTakudo(char *initialTakudoPath,int jieshu);
void showInitialTakudo(char *,int);
#endif // CNF_H_INCLUDED
