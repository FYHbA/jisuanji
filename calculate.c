//本文件是用于实现十进制计算的函数的定义，包括中缀转后缀和计算两个函数
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include<ctype.h>
#include"ku.h"
#include<math.h>
#define CHECK
status change(stackelem c[],stack**a,stack**b)//中缀转后缀表达式
{
    FILE*write=fopen("result.txt","a+");
    stackelem*j=NULL;
    int t=0;
    j=malloc(1);
    char op[]={'+','-','*','/'};
    for(int i=0;c[i]!='\0';i++)
    {
        if(isdigit(c[i])||c[i]=='.')
        {
            *j=c[i];
            push(a,&j);
            while(c[i+1]==' ')
            {
                i++;
                continue;
            }
            while(isdigit(c[i+1])||c[i+1]=='.')
            {
                if(c[i+1]=='.')
                {
                    t++;
                }
                *j=c[i+1];
                push(a,&j);
                i++;
                    while(c[i+1]==' ')
                {
                    i++;
                    continue;
                }
            }
            (*a)->top++;
            (*a)->top[0]=' ';
            if(t>1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);         
                free(j);          
                return ERROR;
            }
            else
            {
                t=0;
            }
            while(c[i+1]==' ')
            {
                i++;
                continue;
            }
            if(c[i+1]=='(')
            {
                while((*b)->top[0]=='*'||(*b)->top[0]=='/')
                {
                    pop(b,&j);
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                *j='*';
                push(b,&j);
            }
        }
        else if(c[i]=='+'||c[i]=='-')
        {
            while(strchr(op,(*b)->top[0]))
            {
                pop(b,&j);
                push(a,&j);
                (*a)->top++;
                (*a)->top[0]=' ';
            }
            *j=c[i];
            push(b,&j);
        }
        else if(c[i]=='>'&&c[i+1]=='=')
        {
             while(1)
            {
                if(strchr(op,(*b)->top[0])||(*b)->top[0]=='<'||(*b)->top[0]=='>')
                {
                    pop(b,&j);
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='<')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='>')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else
                break;
            }
            *j=c[i];
            push(b,&j);
            *j=c[i+1];
            push(b,&j);
            i++;
            #ifdef CHECK
                printf("%s\n",(*b)->base);
                printf("%s\n",(*a)->base);
            #endif
        }
        else if(c[i]=='<'&&c[i+1]=='=')
        {
             while(1)
            {
                if(strchr(op,(*b)->top[0])||(*b)->top[0]=='<'||(*b)->top[0]=='>')
                {
                    pop(b,&j);
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='<')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='>')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else
                break;
            }
            *j=c[i];
            push(b,&j);
            *j=c[i+1];
            push(b,&j);
            i++;
        }
        else if(c[i]=='>'||c[i]=='<')
        {
            while(1)
            {
                if(strchr(op,(*b)->top[0])||(*b)->top[0]=='<'||(*b)->top[0]=='>')
                {
                    pop(b,&j);
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='<')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='>')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else
                break;
            }
            *j=c[i];
            push(b,&j);
        }
        else if(c[i]=='='||c[i]=='!')
        {
            if(c[i+1]=='=')
            {
                 while(1)
                {
                    if(strchr(op,(*b)->top[0])||(*b)->top[0]=='<'||(*b)->top[0]=='>')
                    {
                        pop(b,&j);
                        push(a,&j);
                        (*a)->top++;
                        (*a)->top[0]=' ';
                    }
                    else if((*b)->top[0]=='='&&(*b)->top[-1]=='<')
                    {
                        pop(b,&j);
                        pop(b,&j);
                        push(a,&j);
                        *j='=';
                        push(a,&j);
                        (*a)->top++;
                        (*a)->top[0]=' ';
                    }
                    else if((*b)->top[0]=='='&&(*b)->top[-1]=='>')
                    {
                        pop(b,&j);
                        pop(b,&j);
                        push(a,&j);
                        *j='=';
                        push(a,&j);
                        (*a)->top++;
                        (*a)->top[0]=' ';
                    }
                    else if((*b)->top[0]=='='&&(*b)->top[-1]=='!')
                    {
                        pop(b,&j);
                        pop(b,&j);
                        push(a,&j);
                        *j='=';
                        push(a,&j);
                        (*a)->top++;
                        (*a)->top[0]=' ';
                    }
                    else if((*b)->top[0]=='='&&(*b)->top[-1]=='=')
                    {
                        pop(b,&j);
                        pop(b,&j);
                        push(a,&j);
                        *j='=';
                        push(a,&j);
                        (*a)->top++;
                        (*a)->top[0]=' ';
                    }
                    else
                    break;
                }
                *j=c[i];
                push(b,&j);
                *j=c[i+1];
                push(b,&j);
                i++;
            }
            else
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);   
                free(j); 
                return ERROR;
            }
        }
        else if(c[i]=='|'&&c[i+1]=='|')
        {
             while(1)
            {
                if(strchr(op,(*b)->top[0])||(*b)->top[0]=='<'||(*b)->top[0]=='>')
                {
                    pop(b,&j);
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='<')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='>')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='!')
                {
                        pop(b,&j);
                        pop(b,&j);
                        push(a,&j);
                        *j='=';
                        push(a,&j);
                        (*a)->top++;
                        (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='=')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='&'&&(*b)->top[-1]=='&')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='&';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='|'&&(*b)->top[-1]=='|')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='|';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else
                break;
            }
                *j=c[i];
                push(b,&j);
                *j=c[i+1];
                push(b,&j);
                i++;
        }
        else if(c[i]=='&'&&c[i+1]=='&')
        {
             while(1)
            {
                if(strchr(op,(*b)->top[0])||(*b)->top[0]=='<'||(*b)->top[0]=='>')
                {
                    pop(b,&j);
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='<')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='>')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='!')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='='&&(*b)->top[-1]=='=')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='=';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else if((*b)->top[0]=='&'&&(*b)->top[-1]=='&')
                {
                    pop(b,&j);
                    pop(b,&j);
                    push(a,&j);
                    *j='&';
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                else
                break;
            }
                *j=c[i];
                push(b,&j);
                *j=c[i+1];
                push(b,&j);
                i++;
        }
        else if (c[i]=='*'||c[i]=='/')
        {
            while((*b)->top[0]=='*'||(*b)->top[0]=='/')
            {
                pop(b,&j);
                push(a,&j);
                (*a)->top++;
                (*a)->top[0]=' ';
            }
            *j=c[i];
            push(b,&j);
        }
        else if(c[i]=='(')
        {
            *j=c[i];
            push(b,&j);
            while(c[i+1]==' ')
            {
                i++;
                continue;
            }
            if(c[i+1]=='\0'||c[i+1]==')')
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);   
                free(j); 
                return ERROR;
            }
            if(c[i+1]=='-')
            {
                i++;
                *j=c[i];
                push(a,&j);
                while(c[i+1]==' ')
                {
                    i++;
                    continue;
                }
                while(isdigit(c[i+1])||c[i+1]=='.')
                {
                    if(c[i+1]=='.')
                    {
                       t++;
                    }
                    *j=c[i+1];
                    push(a,&j);
                    i++;
                    while(c[i+1]==' ')
                    {
                       i++;
                       continue;
                    }
                }
                (*a)->top++;
                (*a)->top[0]=' ';
                if(t>1)
                {
                    printf("result>表达式有误\n");
                    fprintf(write,"%s\n","表达式有误");
                    fclose(write);   
                    free(j);                
                    return ERROR;
                }
                else
                t=0;
            }
        }
        else if(c[i]==')')
        {
            while((*b)->top[0]!='(')
            {
                pop(b,&j);
                push(a,&j);
                (*a)->top++;
                (*a)->top[0]=' ';
                if((*b)->top[-1]=='\0')
                {
                    printf("result>表达式有误\n");
                    fprintf(write,"%s\n","表达式有误");
                    fclose(write);   
                    free(j); 
                    return ERROR;
                }
            }
            pop(b,&j);
            while(c[i+1]==' ')
            {
                i++;
                continue;
            }
            if(c[i+1]=='(')
            {
                while((*b)->top[0]=='*'||(*b)->top[0]=='/')
                {
                    pop(b,&j);
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                *j='*';
                push(b,&j);
            }
        }
        else if(c[i]==' ')
        {
            continue;
        }
        else
        {
            printf("result>表达式有误\n");
            fprintf(write,"%s\n","表达式有误");
            fclose(write);
            free(j);
            return ERROR;
        }
    }
    while((*b)->top!=(*b)->base)
    {
        if((*b)->top[0]=='='||(*b)->top[0]=='&'||(*b)->top[0]=='|')
        {
            pop(b,&j);
            pop(b,&j);
            if(*j=='>'||*j=='<'||*j=='='||*j=='!')
            {
                push(a,&j);
                *j='=';
                push(a,&j);
            }
            else if(*j=='&'||*j=='|')
            {
                push(a,&j);
                push(a,&j);
            }
            (*a)->top++;
            (*a)->top[0]=' ';
        }
        else
        {
            pop(b,&j);
            push(a,&j);
            (*a)->top++;
            (*a)->top[0]=' ';
        }
        #ifdef CHECK
            printf("%s\n",(*b)->base);
        #endif
    }
    free(j);
    j=NULL;
    fclose(write);
    #ifdef CHECK
       printf("%s\n",(*a)->base);
    #endif
    return OK;
}
status calculate(stack**a)//后缀计算函数
{
    FILE*write=fopen("result.txt","a+");
    double k[10];
    int s=-1;
    double num1,num2;
    char*p=strtok((*a)->base," ");
    while(p!=NULL)
    {
        if(isdigit(p[0])||isdigit(p[1]))
        {

            s++;
            k[s]=atof(p);
            #ifdef CHECK
                printf("%lf\n",k[s]);
            #endif
        }
        else if(*p=='+')
        { 
            if(s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            else if(s==0)
            {
                k[s]=k[s];
            }
            else
            {
                num2=k[s];
                s--;
                num1=k[s];
                k[s]=num1+num2;
            }  
        }
        else if(*p=='-')
        {
            if(s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            else if(s==0)
            {
                k[s]=-k[s];
            }
            else
            {
                num2=k[s];
                s--;
                num1=k[s];
                k[s]=num1-num2;
            }  
        }
        else if(*p=='*')
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1*num2;
        }
        else if(*p=='/')
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            if(num2==0)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            else
            k[s]=num1/num2;
        }
         else if(strcmp(p,">=")==0)
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1>=num2;
        }
        else if(strcmp(p,"<=")==0)
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1<=num2;
        }
        else if(*p=='>')
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1>num2;
        }
        else if(*p=='<')
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1<num2;
        }
        else if(strcmp(p,"==")==0)
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1==num2;
        }
        else if(strcmp(p,"!=")==0)
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1!=num2;
        }
        else if(strcmp(p,"&&")==0)
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1&&num2;
        }
        else if(strcmp(p,"||")==0)
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1||num2;
        }
        p=strtok(NULL," ");
    }
    if(k[0]<=-2147483648||k[0]>=2147483648)
    {
        printf("result>结果到边界啦\n");
        fprintf(write,"%s\n","结果到边界啦");
        fclose(write);
        return ERROR;
    }
    if(ceil(k[0]) == floor(k[0]))
    {
        int i=(int)k[0];
        printf("result> %d\n",i);
        fprintf(write,"%d\n",i);
    }
    else
    {
        printf("result> %lf\n",k[0]);
        fprintf(write,"%lf\n",k[0]);
    }
    fclose(write);
    return OK;
}