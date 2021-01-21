#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cnf.h"
#include "takudo.h"
#include "takudoGeneretor.h"
int main()
{

    //const char *fileName = "D:/syx/程序设计综合课程设计任务及指导学生包/SAT测试备选算例/满足算例/M/sud00012.cnf";

    //const char *fileName = "D:/syx/程序设计综合课程设计任务及指导学生包/SAT测试备选算例/满足算例/S/problem1-20.cnf";
   // const char *fileName = "D:/syx/程序设计综合课程设计任务及指导学生包/SAT测试备选算例/满足算例/L/par16-1.cnf";
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
            printf("                     Menu for SAT 数据集\n");
            printf("---------------------------------------------------------------\n");
            printf("             1.小型数据集                          2.中型数据集\n");
            printf("             3.大型数据集                          4.基准数据集\n");
            printf("             5.不满足数据集                        6.自选数据集\n");
            printf("----------------------------------------------------------------\n");
            int k;
            scanf("%d",&k);
            system("cls");
            if(k == 1 || k == 2 || k == 3)
            {
                printf("\n");
                printf("现有5个对应数据集，请输入1-5选择你要选择的文件：(5个文件的难度基本相同)\n");
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
                        printf("              Menu for 操作\n");
                        printf("-------------------------------------------------\n");
                        printf("           1.遍历CNF                      2.进行求解\n");
                        printf("           3.计算优化率                   4.返回\n");
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
                            printf("\nDPLL1 耗时: %f ms\n", timeTaken);
                            myClauseSet = readCnf(smallFile[m]);
                            t = clock();
                            myResult = DPLL2(myClauseSet);
                            t2 = clock();
                            double timeTaken2 = 1000*((double)(t2 - t))/CLOCKS_PER_SEC;
                            printf("DPLL2 耗时: %f ms\n", timeTaken2);
                            double youhualv = (1.0 -timeTaken / timeTaken2) * 100;
                            printf("优化率为%.2f%%\n",youhualv);
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
                        printf("              Menu for 操作\n");
                        printf("-------------------------------------------------\n");
                        printf("           1.遍历CNF                      2.进行求解\n");
                        printf("           3.计算优化率                   4.返回\n");
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
                            printf("\nDPLL1 耗时: %f ms\n", timeTaken);
                            myClauseSet = readCnf(midFile[m]);
                            t = clock();
                            myResult = DPLL2(myClauseSet);
                            t2 = clock();
                            double timeTaken2 = 1000*((double)(t2 - t))/CLOCKS_PER_SEC;
                            printf("DPLL2 耗时: %f ms\n", timeTaken2);
                            double youhualv = (1.0 -timeTaken / timeTaken2) * 100;
                            printf("优化率为%.2f%%\n",youhualv);
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
                        printf("              Menu for 操作\n");
                        printf("-------------------------------------------------\n");
                        printf("           1.遍历CNF                      2.进行求解\n");
                        printf("           3.计算优化率                   4.返回\n");
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
                            printf("\nDPLL1 耗时: %f ms\n", timeTaken);
                            myClauseSet = readCnf(midFile[m]);
                            printf("优化率为100%%\n");
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
                printf("数字1-2为功能测试算例、3-4为性能测试算例\n");
                printf("请输入对应数字\n");
                int m;
                scanf("%d",&m);
                m--;
                while(1)
                {
                    system("cls");
                    printf("              Menu for 操作\n");
                    printf("-------------------------------------------------\n");
                    printf("           1.遍历CNF                      2.进行求解且记录时间\n");
                    printf("                         3.返回\n");
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
                        printf("\nDPLL1 耗时: %f ms\n", timeTaken);
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
                printf("共提供4个不满足算例\n");
                printf("请输入对应数字1-4\n");
                int m;
                scanf("%d",&m);
                m--;
                while(1)
                {
                    system("cls");
                    printf("              Menu for 操作\n");
                    printf("-------------------------------------------------\n");
                    printf("           1.遍历CNF                      2.进行求解且记录时间\n");
                    printf("           3.计算优化率                   4.返回\n");
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
                            printf("该算例为不满足算例\n");
                        }
                        double timeTaken = 1000*((double)(t1-t))/CLOCKS_PER_SEC; // in milliseconds
                        printf("\nDPLL1 耗时: %f ms\n", timeTaken);
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
                        printf("\nDPLL1 耗时: %f ms\n", timeTaken);
                        myClauseSet = readCnf(unSatisFile[m]);
                        t = clock();
                        myResult = DPLL2(myClauseSet);
                        t2 = clock();
                        double timeTaken2 = 1000*((double)(t2 - t))/CLOCKS_PER_SEC;
                        printf("DPLL2 耗时: %f ms\n", timeTaken2);
                        double youhualv = (1.0 -timeTaken / timeTaken2) * 100;
                        printf("优化率为%.2f%%\n",youhualv);
                        if(myResult.state == 0)
                        {
                            printf("该算例为不满足算例\n");
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
                printf("请输入对应路径\n");
                scanf("%s",fileName);
                while(1)
                {
                    system("cls");
                    printf("              Menu for 操作\n");
                    printf("-------------------------------------------------\n");
                    printf("           1.遍历CNF                      2.进行求解\n");
                    printf("           3.计算优化率                   4.返回\n");
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
                        printf("\nDPLL1 耗时: %f ms\n", timeTaken);
                        myClauseSet = readCnf(fileName);
                        t = clock();
                        myResult = DPLL2(myClauseSet);
                        t2 = clock();
                        double timeTaken2 = 1000*((double)(t2 - t))/CLOCKS_PER_SEC;
                        printf("DPLL2 耗时: %f ms\n", timeTaken2);
                        double youhualv = (1.0 -timeTaken / timeTaken2) * 100;
                        printf("优化率为%.2f%%\n",youhualv);
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
                printf("    欢迎使用本数独生成器、求解器        \n");
                printf("        1.自动生成数独进行数独游戏\n");
                printf("        2.读取已知数独进行数独游戏\n");
                printf("        3.返回\n");
                printf("----------------------------------------\n");
                int choose;
                scanf("%d",&choose);
                if(choose == 1)
                {
                    system("cls");
                    int jieshu;
                    printf("选择生成数独的阶数（10阶以内）:\n");
                    scanf("%d",&jieshu);
                    char *myGeneretorAddress = generator(jieshu);
                    showInitialTakudo(myGeneretorAddress,jieshu);
                    printf("输入任意键查看答案\n");
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
                    printf("选择输入数独的阶数:");
                    scanf("%d",&jieshu);
                    char myGeneratorAddress[999];
                    printf("输入数独路径:");
                    scanf("%s",myGeneratorAddress);
                    showOriginTakudo(myGeneratorAddress,jieshu);
                    printf("输入任意键查看答案\n");
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
                    printf("请输入正确的数字\n");
                }

            }
            if(flag2 == 1) continue;

        }
        else if(flag == 0)
        {
            printf("欢迎你下次使用本求解器\n");
            system("pause");
            return 0;
        }
        else
        {
            printf("请输入正确的数字\n");
            system("pause");
            continue;
        }
    }

    system("pause");
    return 0;
}
