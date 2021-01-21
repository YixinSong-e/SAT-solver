#include<stdio.h>
#include <stdlib.h>

#include"takudo.h"
int liner = 0;
int extraVariable = 0;

int judgeJie(int num)
{
    int jieshu =0;

    if(num == 36) jieshu = 6;
    else if(num == 4) jieshu = 2;
    else if(num == 16) jieshu = 4;
    else if(num == 64) jieshu = 8;
    else if(num == 100) jieshu = 10;
    else if(num == 144) jieshu = 12;
    else if(num == 196) jieshu = 14;
    else jieshu = 14;
    return jieshu;
}
void constraintone(int jieshu,FILE *writeTo)
{
    int i = 0;
    for(; i <jieshu; i++)
    {
        int j = 1;
        for(;j <=jieshu-2;j++)
        {
            int level = i * jieshu;
            fprintf(writeTo,"%d %d %d 0\n",j+level,j+1+level,j+2+level);
            fprintf(writeTo,"%d %d %d 0\n",-(j+level),-(j+1+level),-(j+2+level));
            liner+=2;
        }

    }
    for(i = 0;i<jieshu-2;i++)
    {
        int j = 1;
        for(;j <=jieshu;j++)
        {
            fprintf(writeTo,"%d %d %d 0\n",j+i*jieshu,j+i*jieshu+jieshu,j+i*jieshu+jieshu*2);
            fprintf(writeTo,"%d %d %d 0\n",-(j+i*jieshu),-(j+i*jieshu+jieshu),-(j+i*jieshu+jieshu*2));
            liner+=2;
        }
    }
}
void constrainttwo(int jieshu,FILE *writeTo)
{
    int f[jieshu+1];
    linedfs(0,f,0,jieshu,writeTo);
}
void CreateUnitClause(char *takudo,FILE *writeTo,int jieshu)
{
    int i;
    for(i = 0;i<jieshu*jieshu;i++)
    {
        if(takudo[i] != '.')
        {
            if(takudo[i] == '0')  fprintf(writeTo,"%d 0\n",-(i+1));
            else fprintf(writeTo,"%d 0\n",i+1);
            liner+=1;
        }
    }
}
void mainProgram(int jieshu,char *takudo,FILE *writeTo)
{
    liner = 0;
    extraVariable = 0;
    constraintone(jieshu,writeTo);
    constrainttwo(jieshu,writeTo);
    constraintthree(jieshu,writeTo);
    CreateUnitClause(takudo,writeTo,jieshu);
}
char *convertToCnf(const char *fromTo)
{

    FILE *fp;
    if ((fp = fopen(fromTo, "r")) == NULL)
    {

        exit(EXIT_FAILURE);
    }
    const char *destination = "convert.txt";
    FILE *writeTo;
    writeTo = fopen(destination,"w");
    char takudo[999];
    fgets(takudo,999,fp);
    int jieshu = judgeJie(strlen(takudo));
    mainProgram(jieshu,takudo,writeTo);
    fclose(writeTo);
    writeTo = fopen(destination,"w");
    fprintf(writeTo,"p cnf %d %d\n",extraVariable,liner);
    mainProgram(jieshu,takudo,writeTo);
    fclose(writeTo);
    return destination;

}
void linedfs(int level,int f[],int last,int jieshu,FILE *writeTo)
{
    if(level == jieshu/2 +1)
    {
        int j;
        for(j = 0; j <jieshu;j++)
        {
            int i;
            for(i =0;i <= jieshu/2;i++)
            {
                fprintf(writeTo,"%d ",f[i]+j*jieshu);
            }
            fprintf(writeTo,"0 \n");
            for(i =0;i <= jieshu/2;i++)
            {
                fprintf(writeTo,"%d ",-f[i]-j*jieshu);
            }
            fprintf(writeTo,"0\n");
            for(i =0;i <= jieshu/2;i++)
            {
                fprintf(writeTo,"%d ",(f[i]-1)*jieshu+j+1);
            }
            fprintf(writeTo,"0\n");
            for(i =0;i <= jieshu/2;i++)
            {
                fprintf(writeTo,"%d ",-((f[i]-1)*jieshu+j+1));
            }
            fprintf(writeTo,"0\n");
            liner+=4;
        }

        return;
    }
    int i;
    for(i = last+1;i <=jieshu;i++)
    {
        f[level] = i;
        linedfs(level+1,f,i,jieshu,writeTo);
    }
}
void constraintthree(int jieshu,FILE *writeTo)
{
    int i;
    extraVariable = jieshu * jieshu;

    for(i = 1;i <= jieshu;i++)
    {
        int j;
        for(j = i+1;j <= jieshu;j++)
        {
            int k;
            for(k = 1;k <= jieshu;k++)
            {
                extraVariable += 1;
                int a = (i-1)*jieshu + k;
                int b = (j-1)*jieshu + k;
                fprintf(writeTo,"%d %d 0\n",a,-extraVariable);
                fprintf(writeTo,"%d %d 0\n",b,-extraVariable);
                fprintf(writeTo,"%d %d %d 0\n",-a,-b,extraVariable);

                extraVariable += 1;
                fprintf(writeTo,"%d %d 0\n",-a,-extraVariable);
                fprintf(writeTo,"%d %d 0\n",-b,-extraVariable);
                fprintf(writeTo,"%d %d %d 0\n",a,b,extraVariable);
                liner+=6;
            }
        }
    }
    int temp = jieshu * jieshu + 1;
    for(i = 1;i <= jieshu;i++)
    {

        int record = extraVariable;
        int j;
        for(j = i+1;j <= jieshu;j++)
        {
            int k;
            record = extraVariable;
            for(k = 1;k <= jieshu;k++)
            {
                extraVariable+=1;
                fprintf(writeTo,"%d %d 0\n",-temp,extraVariable);
                fprintf(writeTo,"%d %d 0\n",-temp-1,extraVariable);
                fprintf(writeTo,"%d %d %d 0\n",temp,temp+1,-extraVariable);
                liner+=3;
                temp += 2;
            }
            extraVariable+=1;
            for(k = 1;k <= jieshu;k++)
            {
                fprintf(writeTo,"%d %d 0\n",extraVariable,record+k);
                liner++;
            }

            fprintf(writeTo,"%d ",-extraVariable);
            for(k =1; k <= jieshu;k++) fprintf(writeTo,"%d ",-(record+k));
            fprintf(writeTo,"0\n");
            liner+=1;
        }
    }
    int ltemp = extraVariable + 1;
    for(i = 1;i <= jieshu;i++)
    {
        int j;
        for(j = i+1;j <= jieshu;j++)
        {
            int k;
            for(k = 1;k <= jieshu;k++)
            {
                extraVariable++;
                int a = (k-1)*jieshu + i;
                int b = (k-1)*jieshu + j;
                fprintf(writeTo,"%d %d 0\n",a,-extraVariable);
                fprintf(writeTo,"%d %d 0\n",b,-extraVariable);
                fprintf(writeTo,"%d %d %d 0\n",-a,-b,extraVariable);
                extraVariable += 1;
                fprintf(writeTo,"%d %d 0\n",-a,-extraVariable);
                fprintf(writeTo,"%d %d 0\n",-b,-extraVariable);
                fprintf(writeTo,"%d %d %d 0\n",a,b,extraVariable);
                liner+=6;
            }
        }
    }
    temp = ltemp;
    for(i = 1;i <= jieshu;i++)
    {


        int j;
        for(j = i+1;j <= jieshu;j++)
        {
            int record = extraVariable;
            int k;
            for(k = 1;k <= jieshu;k++)
            {
                extraVariable+=1;
                fprintf(writeTo,"%d %d 0\n",-temp,extraVariable);
                fprintf(writeTo,"%d %d 0\n",-temp-1,extraVariable);
                fprintf(writeTo,"%d %d %d 0\n",temp,temp+1,-extraVariable);
                liner+=3;
                temp += 2;
            }
            extraVariable+=1;
            for(k = 1;k <= jieshu;k++)
            {
                fprintf(writeTo,"%d %d 0\n",extraVariable,record+k);
                liner++;
            }
            fprintf(writeTo,"%d ",-extraVariable);
            for(k =1; k <= jieshu;k++) fprintf(writeTo,"%d ",-(record+k));
            fprintf(writeTo,"0\n");
            liner+=1;
        }
    }
}
