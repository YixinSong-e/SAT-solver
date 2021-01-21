#include <stdio.h>
#include <stdlib.h>
#include "takudo.h"
#include "takudoGeneretor.h"
#include "cnf.h"
#include <time.h>
char *generator(int jieshu)
{
    char *address = "generator.txt";
    int k = jieshu * jieshu;
    char test[k];
    srand(time(NULL));
    while(1)
    {
        initialRand(jieshu,test,address);
        char *filef = convertToCnf(address);
        struct result myResult;
        struct clauseSet myClauseSet = readCnf(filef);
        myResult = DPLL(myClauseSet);
        if(myResult.state == 1) break;
    }
    judgeGuess(jieshu,test,address);
    return address;
}
void judgeGuess(int jieshu,char test[],char *address)
{
    int traverseAllRes = jieshu * jieshu;
    int i;
    for(i = 0; i < traverseAllRes;i++)
    {
        if(test[i] == '.')
        {

            FILE *fp = fopen(address,"w");
            int flag = 0;
            test[i] = '0';
            fprintf(fp,"%s",test);
            fclose(fp);
            struct result myResult;
            char *filef = convertToCnf(address);
            struct clauseSet myClauseSet = readCnf(filef);
            myResult = DPLL(myClauseSet);
            if(myResult.state == 1) flag++;
            if(flag == 0)
            {
                fp = fopen(address,"w");
                test[i] = '.';
                fprintf(fp,"%s",test);
                fclose(fp);
                continue;
            }
            else
            {
                fp = fopen(address,"w");
                test[i] = '1';
                fprintf(fp,"%s",test);
                fclose(fp);
                struct result myResult;
                char *filef = convertToCnf(address);
                struct clauseSet myClauseSet = readCnf(filef);
                myResult = DPLL(myClauseSet);
                if(myResult.state == 1) flag++;
            }
            if(flag != 2)
            {
                fp = fopen(address,"w");
                test[i] = '.';
                fprintf(fp,"%s",test);
                fclose(fp);
                continue;
            }
            else
            {
                fp = fopen(address,"w");
                int r = rand() % 2;
                test[i] = r + '0';
                fprintf(fp,"%s",test);
                fclose(fp);
            }

        }
        else continue;
    }
}
void initialRand(int jieshu,char test[],char *address)
{
    FILE *fp = fopen(address,"w");
    int i;
    int k = jieshu * jieshu;
    for(i = 0;i < k;i++) test[i] = '.';
    test[k] = '\0';
    for(i = 0;i < jieshu;i++)
    {
        int random = rand() % k;
        int ass = rand() % 2;
        if(ass == 0) test[random] = '0';
        else test[random] = '1';
    }
    fprintf(fp,"%s",test);
    fclose(fp);
}
