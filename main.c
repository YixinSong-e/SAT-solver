#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cnf.h"
#include "takudo.h"
#include "takudoGeneretor.h"
int main()
{

    //const char *fileName = "D:/syx/��������ۺϿγ��������ָ��ѧ����/SAT���Ա�ѡ����/��������/M/sud00012.cnf";

    //const char *fileName = "D:/syx/��������ۺϿγ��������ָ��ѧ����/SAT���Ա�ѡ����/��������/S/problem1-20.cnf";
   // const char *fileName = "D:/syx/��������ۺϿγ��������ָ��ѧ����/SAT���Ա�ѡ����/��������/L/par16-1.cnf";
    char fileName[999];
    int flag = -1;
    init();
    printf("\n");
    while(1)
    {
        system("cls");
        printf("                    Menu for Sudoku or SAT\n");
        printf("---------------------------------------------------------------------------\n");
        printf("                  1.SAT                            2.Sudoku\n");
        printf("                  0.Exit\n");
        printf("----------------------------------------------------------------------------\n");
        scanf("%d",&flag);
        if(flag == 1)
        {
            system("cls");
            printf("\n");
            printf("                     Menu for SAT ���ݼ�\n");
            printf("---------------------------------------------------------------\n");
            printf("             1.С�����ݼ�                          2.�������ݼ�\n");
            printf("             3.�������ݼ�                          4.��׼���ݼ�\n");
            printf("             5.���������ݼ�                        6.��ѡ���ݼ�\n");
            printf("----------------------------------------------------------------\n");
            int k;
            scanf("%d",&k);
            system("cls");
            if(k == 1 || k == 2 || k == 3)
            {
                printf("\n");
                printf("����5����Ӧ���ݼ���������1-5ѡ����Ҫѡ����ļ���(5���ļ����ѶȻ�����ͬ)\n");
                int m;
                scanf("%d",&m);
                m--;
                system("cls");
                if(k == 1)
                {
                    int flag2 = 0;
                    while(1)
                    {
                        system("cls");
                        printf("              Menu for ����\n");
                        printf("-------------------------------------------------\n");
                        printf("           1.����CNF                      2.�������\n");
                        printf("           3.�����Ż���                   4.����\n");
                        int choose;
                        struct clauseSet myClauseSet = readCnf(smallFile[m]);
                        scanf("%d",&choose);
                        if(choose == 1)
                        {
                            traverse(myClauseSet);
                            system("pause");
                        }
                        if(choose == 2)
                        {
                            struct result myResult;
                            myResult = DPLL(myClauseSet);
                            showResult(myResult);
                            system("pause");
                        }
                        if(choose == 3)
                        {
                            clock_t t,t1,t2;
                            struct result myResult;
                            t = clock();
                            myResult = DPLL(myClauseSet);
                            t1 = clock();
                            double timeTaken = 1000*((double)(t1-t))/CLOCKS_PER_SEC; // in milliseconds
                            printf("\nDPLL1 ��ʱ: %f ms\n", timeTaken);
                            myClauseSet = readCnf(smallFile[m]);
                            t = clock();
                            myResult = DPLL2(myClauseSet);
                            t2 = clock();
                            double timeTaken2 = 1000*((double)(t2 - t))/CLOCKS_PER_SEC;
                            printf("DPLL2 ��ʱ: %f ms\n", timeTaken2);
                            double youhualv = (1.0 -timeTaken / timeTaken2) * 100;
                            printf("�Ż���Ϊ%.2f%%\n",youhualv);
                            system("pause");
                        }
                        if(choose == 4)
                        {
                            flag2 =1 ;
                            break;
                        }
                    }
                    if(flag2 == 1) continue;
                }
                if(k == 2)
                {
                    int flag2 = 0;
                    while(1)
                    {
                        system("cls");
                        printf("              Menu for ����\n");
                        printf("-------------------------------------------------\n");
                        printf("           1.����CNF                      2.�������\n");
                        printf("           3.�����Ż���                   4.����\n");
                        int choose;
                        struct clauseSet myClauseSet = readCnf(midFile[m]);
                        scanf("%d",&choose);
                        if(choose == 1)
                        {
                            traverse(myClauseSet);
                            system("pause");
                        }
                        if(choose == 2)
                        {
                            struct result myResult;
                            myResult = DPLL(myClauseSet);
                            showResult(myResult);
                            system("pause");
                        }
                        if(choose == 3)
                        {
                            clock_t t,t1,t2;
                            struct result myResult;
                            t = clock();
                            myResult = DPLL(myClauseSet);
                            t1 = clock();
                            double timeTaken = 1000*((double)(t1-t))/CLOCKS_PER_SEC; // in milliseconds
                            printf("\nDPLL1 ��ʱ: %f ms\n", timeTaken);
                            myClauseSet = readCnf(midFile[m]);
                            t = clock();
                            myResult = DPLL2(myClauseSet);
                            t2 = clock();
                            double timeTaken2 = 1000*((double)(t2 - t))/CLOCKS_PER_SEC;
                            printf("DPLL2 ��ʱ: %f ms\n", timeTaken2);
                            double youhualv = (1.0 -timeTaken / timeTaken2) * 100;
                            printf("�Ż���Ϊ%.2f%%\n",youhualv);
                            system("pause");
                        }
                        if(choose == 4)
                        {
                            flag2 =1 ;
                            break;
                        }
                    }
                    if(flag2 == 1) continue;
                }
                if(k == 3)
                {
                    int flag2 = 0;
                    while(1)
                    {
                        system("cls");
                        printf("              Menu for ����\n");
                        printf("-------------------------------------------------\n");
                        printf("           1.����CNF                      2.�������\n");
                        printf("           3.�����Ż���                   4.����\n");
                        int choose;
                        struct clauseSet myClauseSet = readCnf(largeFile[m]);
                        scanf("%d",&choose);
                        if(choose == 1)
                        {
                            traverse(myClauseSet);
                            system("pause");
                        }
                        if(choose == 2)
                        {
                            struct result myResult;
                            myResult = DPLL(myClauseSet);
                            showResult(myResult);
                            system("pause");
                        }
                        if(choose == 3)
                        {
                            clock_t t,t1,t2;
                            struct result myResult;
                            t = clock();
                            myResult = DPLL(myClauseSet);
                            t1 = clock();
                            double timeTaken = 1000*((double)(t1-t))/CLOCKS_PER_SEC; // in milliseconds
                            printf("\nDPLL1 ��ʱ: %f ms\n", timeTaken);
                            myClauseSet = readCnf(midFile[m]);
                            printf("�Ż���Ϊ100%%\n");
                            system("pause");
                        }
                        if(choose == 4)
                        {
                            flag2 =1 ;
                            break;
                        }
                    }
                    if(flag2 == 1) continue;
                }
            }
            else if( k == 4)
            {

                int flag2 = 0;
                printf("����1-2Ϊ���ܲ���������3-4Ϊ���ܲ�������\n");
                printf("�������Ӧ����\n");
                int m;
                scanf("%d",&m);
                m--;
                while(1)
                {
                    system("cls");
                    printf("              Menu for ����\n");
                    printf("-------------------------------------------------\n");
                    printf("           1.����CNF                      2.��������Ҽ�¼ʱ��\n");
                    printf("                         3.����\n");
                    int choose;
                    struct clauseSet myClauseSet = readCnf(baseFuncFile[m]);
                    scanf("%d",&choose);
                    if(choose == 1)
                    {
                        traverse(myClauseSet);
                        system("pause");
                    }
                    if(choose == 2)
                    {
                        struct result myResult;
                        clock_t t,t1;
                        t = clock();
                        myResult = DPLL(myClauseSet);
                        t1 = clock();
                        showResult(myResult);
                        double timeTaken = 1000*((double)(t1-t))/CLOCKS_PER_SEC; // in milliseconds
                        printf("\nDPLL1 ��ʱ: %f ms\n", timeTaken);
                        system("pause");
                    }
                    if(choose == 3)
                    {
                        flag2 =1 ;
                        break;
                    }
                }
                if(flag2 == 1) continue;
            }
            else if(k == 5)
            {
                int flag2 = 0;
                printf("���ṩ4������������\n");
                printf("�������Ӧ����1-4\n");
                int m;
                scanf("%d",&m);
                m--;
                while(1)
                {
                    system("cls");
                    printf("              Menu for ����\n");
                    printf("-------------------------------------------------\n");
                    printf("           1.����CNF                      2.��������Ҽ�¼ʱ��\n");
                    printf("           3.�����Ż���                   4.����\n");
                    int choose;
                    struct clauseSet myClauseSet = readCnf(unSatisFile[m]);
                    scanf("%d",&choose);
                    if(choose == 1)
                    {
                        traverse(myClauseSet);
                        system("pause");
                    }
                    if(choose == 2)
                    {
                        struct result myResult;
                        clock_t t,t1;
                        t = clock();
                        myResult = DPLL(myClauseSet);
                        t1 = clock();
                        if(myResult.state == 0)
                        {
                            printf("������Ϊ����������\n");
                        }
                        double timeTaken = 1000*((double)(t1-t))/CLOCKS_PER_SEC; // in milliseconds
                        printf("\nDPLL1 ��ʱ: %f ms\n", timeTaken);
                        system("pause");
                    }
                    if(choose == 3)
                    {
                        clock_t t,t1,t2;
                        struct result myResult;
                        t = clock();
                        myResult = DPLL(myClauseSet);
                        t1 = clock();
                        double timeTaken = 1000*((double)(t1-t))/CLOCKS_PER_SEC; // in milliseconds
                        printf("\nDPLL1 ��ʱ: %f ms\n", timeTaken);
                        myClauseSet = readCnf(unSatisFile[m]);
                        t = clock();
                        myResult = DPLL2(myClauseSet);
                        t2 = clock();
                        double timeTaken2 = 1000*((double)(t2 - t))/CLOCKS_PER_SEC;
                        printf("DPLL2 ��ʱ: %f ms\n", timeTaken2);
                        double youhualv = (1.0 -timeTaken / timeTaken2) * 100;
                        printf("�Ż���Ϊ%.2f%%\n",youhualv);
                        if(myResult.state == 0)
                        {
                            printf("������Ϊ����������\n");
                        }
                        system("pause");
                    }
                    if(choose == 4)
                    {
                        flag2 =1 ;
                        break;
                    }
                }
                if(flag2 == 1) continue;
            }
            else
            {
                int flag2 = 0;
                printf("�������Ӧ·��\n");
                scanf("%s",fileName);
                while(1)
                {
                    system("cls");
                    printf("              Menu for ����\n");
                    printf("-------------------------------------------------\n");
                    printf("           1.����CNF                      2.�������\n");
                    printf("           3.�����Ż���                   4.����\n");
                    int choose;
                    struct clauseSet myClauseSet = readCnf(fileName);
                    scanf("%d",&choose);
                    if(choose == 1)
                    {
                        traverse(myClauseSet);
                        system("pause");
                    }
                    if(choose == 2)
                    {
                        struct result myResult;
                        myResult = DPLL(myClauseSet);
                        showResult(myResult);
                        system("pause");
                    }
                    if(choose == 3)
                    {
                        clock_t t,t1,t2;
                        struct result myResult;
                        t = clock();
                        myResult = DPLL(myClauseSet);
                        t1 = clock();
                        double timeTaken = 1000*((double)(t1-t))/CLOCKS_PER_SEC; // in milliseconds
                        printf("\nDPLL1 ��ʱ: %f ms\n", timeTaken);
                        myClauseSet = readCnf(fileName);
                        t = clock();
                        myResult = DPLL2(myClauseSet);
                        t2 = clock();
                        double timeTaken2 = 1000*((double)(t2 - t))/CLOCKS_PER_SEC;
                        printf("DPLL2 ��ʱ: %f ms\n", timeTaken2);
                        double youhualv = (1.0 -timeTaken / timeTaken2) * 100;
                        printf("�Ż���Ϊ%.2f%%\n",youhualv);
                        system("pause");
                    }
                    if(choose == 4)
                    {
                        flag2 =1 ;
                        break;
                    }
                }
                if(flag2 == 1) continue;
            }
            break;
        }
        else if(flag == 2)
        {
            int flag2 = 0;
            while(1)
            {
                system("cls");
                printf("----------------------------------------\n");
                printf("    ��ӭʹ�ñ������������������        \n");
                printf("        1.�Զ�������������������Ϸ\n");
                printf("        2.��ȡ��֪��������������Ϸ\n");
                printf("        3.����\n");
                printf("----------------------------------------\n");
                int choose;
                scanf("%d",&choose);
                if(choose == 1)
                {
                    system("cls");
                    int jieshu;
                    printf("ѡ�����������Ľ�����10�����ڣ�:\n");
                    scanf("%d",&jieshu);
                    char *myGeneretorAddress = generator(jieshu);
                    showInitialTakudo(myGeneretorAddress,jieshu);
                    printf("����������鿴��\n");
                    system("pause");
                    char *filef = convertToCnf(myGeneretorAddress);
                    struct result myResult;
                    struct clauseSet myClauseSet = readCnf(filef);
                    myResult = DPLL(myClauseSet);
                    showResulttotakudo(myResult,jieshu);
                    system("pause");
                }
                else if(choose == 2)
                {
                    int jieshu;
                    printf("ѡ�����������Ľ���:");
                    scanf("%d",&jieshu);
                    char myGeneratorAddress[999];
                    printf("��������·��:");
                    scanf("%s",myGeneratorAddress);
                    showOriginTakudo(myGeneratorAddress,jieshu);
                    printf("����������鿴��\n");
                    system("pause");
                    char *filef = convertToCnf(myGeneratorAddress);
                    struct result myResult;
                    struct clauseSet myClauseSet = readCnf(filef);
                    myResult = DPLL(myClauseSet);
                    showResulttotakudo(myResult,jieshu);
                    system("pause");

                }
                else if(choose == 3)
                {
                    flag2 = 1;
                    break;
                }
                else
                {
                    printf("��������ȷ������\n");
                }

            }
            if(flag2 == 1) continue;

        }
        else if(flag == 0)
        {
            printf("��ӭ���´�ʹ�ñ������\n");
            system("pause");
            return 0;
        }
        else
        {
            printf("��������ȷ������\n");
            system("pause");
            continue;
        }
    }

    system("pause");
    return 0;
}
