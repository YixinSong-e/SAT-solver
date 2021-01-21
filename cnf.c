#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cnf.h"
struct StackNode *head =NULL;
//int flag = 0;
int top = 0;
int literal_polarity[3000];
int vstRecord[3000][10000];
int vst[50000];
struct clauseSet readCnf(const char *filePath)
{

    FILE *fp;
    int noOfInfoLines = -1;
    struct clauseSet aClauseSet;
    int numClause= 0;
    int numLiteral= 0;
    aClauseSet.firstClause = NULL;
    char dummyP[STLEN];
    char dummyC[STLEN];

    int aLiteral = 0;



    // open the file
    if ((fp = fopen(filePath, "r")) == NULL)
    {
        printf("文件路径不正确，不存在该文件，请重试\n");
        return aClauseSet;
    }
    int i = 0;
    char buf[STLEN];
    // get rid of useless lines, set noOfLiterals and noOfClauses
    do
    {
        i = 0;
        fgets(buf, STLEN, fp);
        if (buf[0] == 'p')
        {
            i = 0;
            sscanf(buf, "%s %s %d %d", dummyP, dummyC, &numLiteral, &numClause);
            aClauseSet.literal_count = numLiteral;
            aClauseSet.clause_count = numClause;
        }
        noOfInfoLines++;
    } while (buf[0] == 'p' || buf[0] == 'c');
    rewind(fp);
    for (; i < noOfInfoLines; i++)
        fgets(buf, STLEN, fp);
    struct literal * firstLiteralPointer = NULL;
    struct literal * currentLiteralPointer = NULL;
    // create the clause set

    for(i = 1; i <= numLiteral; i++)
    {
        literal_frequency[i].iD = i;
    }
     struct clause * currentClausePointer = NULL;
    struct clause * lastClausePointer = NULL;
    i++;
    struct literal * lastLiteralPointer = NULL;
    i++;

    for (i = 1; i <= numClause; i++)
    {
        while (fscanf(fp, "%d", &aLiteral))
        {
            int j;
            if (aLiteral == 0)
            {
                currentClausePointer = createClause(firstLiteralPointer);
                break;
            }

            currentLiteralPointer = createLiteral(aLiteral);
            int lite = abs(aLiteral);
            if (!firstLiteralPointer)
                firstLiteralPointer = currentLiteralPointer;
            if(aLiteral > 0) literal_polarity[lite]++;
            else literal_polarity[lite]--;
            if (lastLiteralPointer)
                lastLiteralPointer->nextLiteral = currentLiteralPointer;
            literal_frequency[lite].frequency++;
            lastLiteralPointer = currentLiteralPointer;
        }
        int j;
        lastLiteralPointer = NULL;
        j++;
        firstLiteralPointer = NULL;
        j++;
        currentLiteralPointer = NULL;

        if (!(aClauseSet.firstClause))
            aClauseSet.firstClause = currentClausePointer;
        j++;
        if (lastClausePointer)
            lastClausePointer->nextClause = currentClausePointer;
        lastClausePointer = currentClausePointer;
    }
    for(i = 1; i <= numLiteral; i++)
    {
        int j;
        for(j = i+1; j <= numLiteral; j++)
        {
            if(literal_frequency[i].frequency < literal_frequency[j].frequency)
            {
                struct literalFrequency third = literal_frequency[i];
                literal_frequency[i] = literal_frequency[j];
                literal_frequency[j] = third;
            }
        }
    }
    fclose(fp);
    return aClauseSet;
}

struct literal * createLiteral(int aLiteral)
{
    struct literal * literalPtr = (struct literal *) malloc(sizeof(struct literal));
    int j;
    literalPtr->theLiteral = aLiteral;
    j++;
    literalPtr->nextLiteral = NULL;
    j++;
    return literalPtr;
}


struct clause * createClause(struct literal * firstLiteralPointer)
{
    int ii = 0;
    struct clause * clausePtr = (struct clause *) malloc(sizeof(struct clause));
    int j;
    clausePtr->nextClause = NULL;
    j++;
    clausePtr->firstLiteral = firstLiteralPointer;
    return clausePtr;
}
void traverse(struct clauseSet aClauseSet)
{
    char *filePrint = "traverseCNF.cnf";
    FILE *fp = fopen(filePrint,"w");
    printf("----------------------------------------------------\n");
    printf("now start traversing the cnf\n");
    struct clauseSet myClauseSet = aClauseSet;
    printf("the number of literals are %d, and clauses are %d\n",myClauseSet.literal_count,myClauseSet.clause_count);
    struct clause * currentClausePointer = myClauseSet.firstClause;
    struct literal * currentLiteralPointer = NULL;
    while (currentClausePointer != NULL)
    {
        currentLiteralPointer = currentClausePointer->firstLiteral;
        while (currentLiteralPointer != NULL)
        {
            printf("%d\t", currentLiteralPointer->theLiteral);
            fprintf(fp,"%d\t",currentLiteralPointer->theLiteral);
            currentLiteralPointer = currentLiteralPointer->nextLiteral;
        }
        puts("");
        fprintf(fp,"\n");
        currentClausePointer = currentClausePointer->nextClause;
    }
    printf("----------------------------------------------------\n");
    printf("遍历完成\n");
    printf("已输出到本地文件traverseCNF.cnf中\n");
    fclose(fp);
}

//构建栈模型进行搜索
struct StackNode * push(struct StackNode *head, struct clauseSet currentClauseSet, int anotherChoice)
{
    struct StackNode *node = (struct StackNode *)malloc(sizeof(struct StackNode));
    struct literal *originalLiteral = NULL;
    node->otherChoice = anotherChoice;
    struct literal *currentLiteral = NULL;
    //data的完全复制
    node->data.firstClause = NULL;
    node->data.literal_count = currentClauseSet.literal_count;
    struct clause *currentClause = NULL;;
    struct clause *lastClause = NULL;;
    node->data.clause_count = currentClauseSet.clause_count;

    struct literal *lastLiteral = NULL;;
    node->next = head;
    struct clause *originalClause = currentClauseSet.firstClause;

    if(originalClause) originalLiteral = originalClause->firstLiteral;
    while(originalClause)
    {
        currentClause = (struct clause *)malloc(sizeof(struct clause));
        currentClause->firstLiteral = NULL;
        currentClause->nextClause = NULL;

        if((node->data).firstClause == NULL)
            (node->data).firstClause = currentClause;
        if(lastClause)
            lastClause->nextClause = currentClause;
        lastClause = currentClause;
        while(originalLiteral)
        {
            currentLiteral = (struct literal *)malloc(sizeof(struct literal));
            if(currentClause->firstLiteral == NULL)
                currentClause->firstLiteral = currentLiteral;
            currentLiteral->theLiteral = originalLiteral->theLiteral;
            currentLiteral->nextLiteral = NULL;
            if(lastLiteral)
                lastLiteral->nextLiteral = currentLiteral;
            lastLiteral = currentLiteral;
            originalLiteral = originalLiteral->nextLiteral;
        }
        originalClause = originalClause->nextClause;
        originalLiteral = NULL;
        lastLiteral = NULL;
        if(originalClause) originalLiteral = originalClause->firstLiteral;

    }
    return node;
}
void init()
{
    smallFile[0] = "database/S/problem1-20.cnf";
    smallFile[1] = "database/S/problem6-50.cnf";
    smallFile[2] = "database/S/problem11-100.cnf";
    smallFile[3] = "database/S/problem3-100.cnf";
    smallFile[4] = "database/S/tst_v25_c100.cnf";
    midFile[0] = "database/M/sud00001.cnf";
    midFile[1] = "database/M/sud00009.cnf";
    midFile[2] = "database/M/sud00012.cnf";
    midFile[3] = "database/M/sud00079.cnf";
    midFile[4] = "database/M/problem5-200.cnf";
    largeFile[0] = "database/L/ii8b3.cnf";
    largeFile[1] = "database/L/ii8b4.cnf";
    largeFile[2] = "database/L/ii8d2.cnf";
    largeFile[3] = "database/L/ii8e2.cnf";
    largeFile[4] = "database/L/par16-1.cnf";
    baseFuncFile[0] = "database/基准算例/功能测试/sat-20.cnf";
    baseFuncFile[1] = "database/基准算例/功能测试/unsat-5cnf-30.cnf";
    baseFuncFile[2] = "database/基准算例/性能测试/ais10.cnf";
    baseFuncFile[3] = "database/基准算例/性能测试/sud00009.cnf";
    unSatisFile[0] = "database/不满足算例/u-problem7-50.cnf";
    unSatisFile[1] = "database/不满足算例/u-problem10-100.cnf";
    unSatisFile[2] = "database/不满足算例/php-010-008.shuffled-as.sat05-1171.cnf";
    unSatisFile[3] = "database/不满足算例/u-5cnf_3500_3500_30f1.shuffled-30.cnf";
}

struct StackNode * pop(struct StackNode *head, struct clauseSet *currentClauseSet, int *anotherLiteral)
{
    if(head == NULL) return NULL;
    *currentClauseSet = head->data;
    *anotherLiteral = head->otherChoice;
    struct StackNode *kk = head->next;
    free(head);
    return kk;
}
struct StackNode * push2(struct StackNode *head, struct clauseSet currentClauseSet, int anotherChoice)
{
    struct StackNode *node = (struct StackNode *)malloc(sizeof(struct StackNode));
    node->next = head;
    node->otherChoice = anotherChoice;
    node->data.clause_count = currentClauseSet.clause_count;
    node->data.literal_count = currentClauseSet.literal_count;

    //data的完全复制
    node->data.firstClause = NULL;
    struct clause *currentClause = NULL;;
    struct clause *lastClause = NULL;;
    struct literal *currentLiteral = NULL;;
    struct literal *lastLiteral = NULL;;

    int i;
    top++;
    for(i = 1;i <= currentClauseSet.literal_count;i++)
    {
        vstRecord[top][i] = vst[i];
    }
    struct clause *originalClause = currentClauseSet.firstClause;
    struct literal *originalLiteral = NULL;
    if(originalClause) originalLiteral = originalClause->firstLiteral;
    while(originalClause)
    {
        currentClause = (struct clause *)malloc(sizeof(struct clause));
        currentClause->firstLiteral = NULL;
        currentClause->nextClause = NULL;
        if((node->data).firstClause == NULL)
            (node->data).firstClause = currentClause;
        if(lastClause)
            lastClause->nextClause = currentClause;
        lastClause = currentClause;
        while(originalLiteral)
        {
            currentLiteral = (struct literal *)malloc(sizeof(struct literal));
            if(currentClause->firstLiteral == NULL)
                currentClause->firstLiteral = currentLiteral;
            currentLiteral->theLiteral = originalLiteral->theLiteral;
            currentLiteral->nextLiteral = NULL;
            if(lastLiteral)
                lastLiteral->nextLiteral = currentLiteral;
            lastLiteral = currentLiteral;
            originalLiteral = originalLiteral->nextLiteral;
        }
        originalClause = originalClause->nextClause;
        originalLiteral = NULL;
        lastLiteral = NULL;
        if(originalClause) originalLiteral = originalClause->firstLiteral;

    }
    return node;
}
struct StackNode * pop2(struct StackNode *head, struct clauseSet *currentClauseSet, int *anotherLiteral)
{
    if(head == NULL) return NULL;
    int i;
    for(i = 1; i <= currentClauseSet->literal_count;i++)
        vst[i] = vstRecord[top][i];
    top--;
    *currentClauseSet = head->data;
    *anotherLiteral = head->otherChoice;
    struct StackNode *kk = head->next;
    free(head);
    return kk;
}


void freeClause(struct clause * clausePtr)
{
    struct literal * temp = clausePtr->firstLiteral;
    while (temp)
    {
        struct literal *third = temp->nextLiteral;
        if(!temp) free(temp);
        temp = third;
    }
    free(clausePtr);
}

struct clauseSet unit_propagate(struct clauseSet currClauseSet, int dotLiteral, struct result *resultPointer)
{

    struct clause *nowClause = currClauseSet.firstClause;
    int k;
    if(nowClause == NULL)//空了
    {
        resultPointer->state = 1;
        return currClauseSet;
    }
    if(nowClause->firstLiteral == NULL)
    {
        resultPointer->state = 0;
        return currClauseSet;
    }
    struct clause *lastClause = NULL;
//    if(flag == 1) traverse(currClauseSet);
    do
    {
        if(nowClause->firstLiteral == NULL)//该子句不成立
        {
            resultPointer->state = 0;
            return currClauseSet;
        }

        struct literal *nowLiteral = nowClause->firstLiteral;
        struct literal *lastLiteral = NULL;
        //if(flag == 1) printf("%d\n",nowClause->firstLiteral->theLiteral);
        while(nowLiteral)
        {

            if(nowLiteral->theLiteral == dotLiteral)//本子句中有
            {
                struct clause *temp = nowClause;
                if(lastClause == NULL)//代表说是第一个
                {
                    //printf("%d ",nowLiteral->theLiteral);
                    currClauseSet.firstClause = currClauseSet.firstClause->nextClause;
                    k++;
                    freeClause(temp);

                    nowClause = currClauseSet.firstClause;
                    k++;
                    if(currClauseSet.firstClause == NULL)
                    {
                        resultPointer->state = 1;
                        return currClauseSet;
                    }

                }
                else
                {

                    k++;
                    lastClause->nextClause = nowClause->nextClause;
                    nowClause = nowClause->nextClause;
                    freeClause(temp);
                }
                lastLiteral = NULL;
                if(nowClause)   nowLiteral = nowClause->firstLiteral;
                else nowLiteral = NULL;
                continue;

            }
            else if(nowLiteral->theLiteral == -dotLiteral)//子句有相反符号
            {
                if(lastLiteral == NULL)//代表首字符
                {
                    nowClause->firstLiteral = nowLiteral->nextLiteral;
                    if(nowClause->firstLiteral == NULL)
                    {
                        resultPointer->state = 0;
                        return currClauseSet;
                    }
                    if(!nowLiteral) free(nowLiteral);
                    nowLiteral = nowClause->firstLiteral;
                }
                else
                {
                    lastLiteral->nextLiteral = nowLiteral->nextLiteral;
                    if(!nowLiteral) free(nowLiteral);
                    k++;
                    nowLiteral = lastLiteral->nextLiteral;
                }
                continue;
            }
            lastLiteral = nowLiteral;
            k++;
            if(nowLiteral) nowLiteral = nowLiteral->nextLiteral;
            k++;
        }
        lastClause = nowClause;
        k++;
        if(nowClause) nowClause = nowClause->nextClause;

    }while(nowClause != NULL);
    return currClauseSet;
}
struct result initResult(struct result myResult)
{
    int i;
    for(i = 0; i < myResult.literal_count;i++)
    {
        myResult.arrHead[i] = -1;
    }
    return myResult;
}
struct result DPLL(struct clauseSet currClauseSet)
{
    struct result myResult;
    myResult.state = -1;
    myResult.literal_count = currClauseSet.literal_count;
    myResult.arrHead = (int *)malloc(myResult.literal_count * sizeof(int));
    myResult = initResult(myResult);
    if(currClauseSet.firstClause == NULL)
    {
        myResult.state = 1;
        return myResult;
    }
    int myLiteral;
    struct StackNode *head =NULL;
    myLiteral = currClauseSet.firstClause->firstLiteral->theLiteral;

    head = push(head,currClauseSet,-myLiteral);//存储另一个选择
    while(1)
    {
        //printf("%d ",myLiteral);
        int k = abs(myLiteral) - 1;
        myResult.arrHead[k] = myLiteral > 0 ? 1:0;
        k++;
        currClauseSet = unit_propagate(currClauseSet,myLiteral,&myResult);
        //printf("%d\n",currClauseSet.firstClause->firstLiteral->theLiteral);

        //检验
        if(myResult.state == 1) return myResult;
        else if(myResult.state == 0)
        {
            if(head != NULL)
            {
                head = pop(head,&currClauseSet,&myLiteral);
                myResult.state = -1;
                continue;
            }
            else return myResult;
        }
        //单子句
        myLiteral = findUnitLiteral(currClauseSet,&myResult);
        while(myLiteral)
        {

            //printf("%d ",myLiteral);
            myResult.arrHead[abs(myLiteral) - 1] = myLiteral > 0 ? 1 : 0;
          //  if(myLiteral == -86) flag = 1;
            currClauseSet = unit_propagate(currClauseSet,myLiteral,&myResult);
          //  if(flag == 1) printf("I'm here too\n");
            myLiteral = findUnitLiteral(currClauseSet,&myResult);

        }
        if(myResult.state == 1) return myResult;
        else if(myResult.state == 0)
        {
            if(head != NULL)
            {
                head = pop(head,&currClauseSet,&myLiteral);
                myResult.state = -1;
                continue;
            }
            else return myResult;
        }
        myLiteral = currClauseSet.firstClause->firstLiteral->theLiteral;
        head = push(head,currClauseSet,-myLiteral);

    }

    return myResult;

}
struct result DPLL2(struct clauseSet currClauseSet)
{
    struct result myResult;
    myResult.state = -1;
    top = 0;
    myResult.literal_count = currClauseSet.literal_count;
    myResult.arrHead = (int *)malloc(myResult.literal_count * sizeof(int));
    int i;
    for(i = 0; i < myResult.literal_count;i++)
    {
        myResult.arrHead[i] = -1;
        vst[i] = 0;
    }
    if(currClauseSet.firstClause == NULL)
    {
        myResult.state = 1;
        return myResult;
    }

    for(i = 1; i <= currClauseSet.literal_count;i++)
    {
        int id = literal_frequency[i].iD;
        if(vst[id] == 0)
        {
            if(literal_polarity[id] < 0) id = -id;
            myResult = dfs(currClauseSet,myResult,id);
        }
    }
    return myResult;

}

struct result dfs(struct clauseSet currClauseSet,struct result myResult,int myLiteral)
{
     if(myResult.state == 1) return myResult;
     myResult.state = -1;
     int singleLiteral;
     int j;
    singleLiteral = findUnitLiteral(currClauseSet,&myResult);
    while(singleLiteral)
    {

        myResult.arrHead[abs(singleLiteral) - 1] = singleLiteral > 0 ? 1 : 0;
        vst[abs(singleLiteral)] = 1;
        currClauseSet = unit_propagate(currClauseSet,singleLiteral,&myResult);
        singleLiteral = findUnitLiteral(currClauseSet,&myResult);
    }
    if(myResult.state == 1) return myResult;
    else if(myResult.state == 0)
    {
         return myResult;
    }
     for(j = 0; j< 2;j++)
     {
         vst[abs(myLiteral)] = 1;
         if(j == 0)
         {
             head = push2(head,currClauseSet,-myLiteral);
         }
         myResult.arrHead[abs(myLiteral) - 1] = myLiteral > 0 ? 1:0;
         currClauseSet = unit_propagate(currClauseSet,myLiteral,&myResult);
         if(myResult.state == 1) return myResult;
         else if(myResult.state == 0)
         {
            if(head != NULL)
            {
                if(j == 0)
                {
                    myResult.state = -1;
                    head = pop2(head,&currClauseSet,&myLiteral);
                    continue;
                }
                else
                {

                    return myResult;
                }
            }
            else return myResult;
         }
        int i;
        for(i = 1; i <= currClauseSet.literal_count;i++)
        {
            myLiteral = literal_frequency[i].iD;
            if(vst[myLiteral] == 0)
            {
                if(literal_polarity[myLiteral] < 0) myLiteral = -myLiteral;
                break;
            }
        }
        myResult = dfs(currClauseSet,myResult,myLiteral);
        if(myResult.state == 1) return myResult;
        else if(myResult.state == 0)
        {

            if( j == 0)
            {
                head = pop2(head,&currClauseSet,&myLiteral);
                myResult.state = -1;
                continue;
            }
            else
            {
                return myResult;
            }
        }
        if(myResult.state == 1) return myResult;

     }
    return myResult;
}

void showResult(struct result myResult)
{
    int i;
    FILE *fp = fopen("resultDPLL.txt","w");
    for(i = 0; i < myResult.literal_count;i++)
    {
        printf("%d : %d\n",i+1,myResult.arrHead[i]);
        fprintf(fp,"%d:%d\n",i+1,myResult.arrHead[i]);
    }
    if(myResult.state == 1)
    {
        printf("该算例为可满足算例\n");
    }
    fclose(fp);

}
void showResulttotakudo(struct result myResult,int jieshu)
{
    int i;
    printf("----------------------------------------\n");
    printf("参考答案如下：\n");
    for(i = 0;i < jieshu*jieshu;i++)
    {
        printf("%d ",myResult.arrHead[i]);
        if( (i+1) % jieshu == 0 ) printf("\n");
    }
    printf("----------------------------------------\n");
}
void showInitialTakudo(char *initialTakudoPath,int jieshu)
{
    FILE *fp = fopen(initialTakudoPath,"r");
    char initialString[jieshu*jieshu];
    fgets(initialString,jieshu*jieshu+1,fp);
    printf("您选择的阶数为%d\n",jieshu);
    printf("下面随机生成一个不完整的且具有唯一解的且尽可能少填的数独\n");
    int i,j;
    for(i = 0;i < jieshu;i++)
    {
        for(j = 0;j < jieshu;j++)
        {
            if(initialString[i*jieshu+j] == '.') printf("_ ");
            else printf("%c ",initialString[i*jieshu+j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}
void showOriginTakudo(char initialTakudoPath[],int jieshu)
{
    FILE *fp = fopen(initialTakudoPath,"r");
    char initialString[jieshu*jieshu];
    fgets(initialString,jieshu*jieshu+1,fp);
    printf("您选择的阶数为%d\n",jieshu);
    printf("下面您选择的数独：\n");
    int i,j;
    for(i = 0;i < jieshu;i++)
    {
        for(j = 0;j < jieshu;j++)
        {
            if(initialString[i*jieshu+j] == '.') printf("_ ");
            else printf("%c ",initialString[i*jieshu+j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}
int findUnitLiteral(struct clauseSet currClauseSet, struct result *myResult)
{
    struct clause *currClause = currClauseSet.firstClause;
    struct literal *currLiteral;
    while(currClause)
    {
        currLiteral = currClause->firstLiteral;

        if(currLiteral == NULL)
        {
            myResult->state = 0;
            return 0;
        }
        else if(currLiteral->nextLiteral == NULL)
        {

            return currLiteral->theLiteral;
        }
        else currClause = currClause->nextClause;
    }
    return 0;
}
