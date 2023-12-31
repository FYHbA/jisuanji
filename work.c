//本文件是计算机的主函数
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include<ctype.h>
#include<readline/readline.h>
#include<readline/history.h>
#include"ku.h"
#define CLOSE "\001\033[0m\002"                 // 关闭所有属性
#define BLOD  "\001\033[1m\002"                 // 强调、加粗、高亮
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"  // x: 背景，y: 前景
//#define CHECK
int main()
{
    read_history(NULL);
    char op[6]={"+-*/()"};
    char mode='D';
    stack*a,*b;
    int i=0;
    printf("欢迎是用简易加减乘除计算器，如需要帮助请输入'h'or'help'or'?',请输入表达式： \n");
    while(1)
    {
        StackInit(&a);
        StackInit(&b);
        stackelem *input=readline(BEGIN(49,34)"interaction>"CLOSE);
        while(input[i]==' ')
        {
            i++;
        }
        if(*input=='?'||input=="help"||*input=='h')
        {
            printf("result>");
            printf("这是一个可以进行加减乘除的计算器\n");
            printf("help或者h可以查看帮助\n");
            printf("quit或q结束使用\n");
            printf("enter键计算表达式\n");
            printf("不能输入=号\n");
            printf("你所有打的空格都会被忽略\n");
            printf("输入H是16进制模式，B是2进制模式，D是十进制模式，初始默认十进制。\n");
            printf("二进制和16进制模式只支持无符号整型的+ - * / ()\n");
            printf("二进制支持按位运算，十进制支持关系运算\n");
            printf("注意，关系运算符之间不能有空格，否则会报错\n");
            printf("注意，二进制和十六进制结果若是小数会自动取整数部分\n");
            printf("十六进制字母请输入大写\n");
        }
        else if(strcmp(input,"quit")==0||*input=='q')
        {
            free_all(&a);
            free_all(&b);
            free(input);
            break;
        }
        else if(*input=='D'||*input=='B'||*input=='H')
        {
            if(*input=='D'&&input[1]=='\0')
            {
                printf("result> The calculator switches to Decimal \n");
            }
            else if(*input=='B'&&input[1]=='\0')
            {
                printf("result> The calculator switches to binary \n");
            }
            else if(*input=='H'&&input[1]=='\0')
            {
                printf("result> The calculator switches to hex mode\n");
            }
            if(input[1]=='\0')
            mode=input[0];
        }
        else if(input[0]=='\0')
        {
            free_all(&a);
            free_all(&b);
            free(input);
            i=0;
            continue;
        }
        else if(!isdigit(input[i])&&input[i]!='('&&input[i]=='A'&&input[i]=='B'&&input[i]=='C'&&input[i]=='D'&&input[i]=='E'&&input[i]=='F')
        {
            free_all(&a);
            free_all(&b);
            free(input);
            printf("result>error\n");
            i=0;
            continue;
        }
        if(mode=='D')
        {
            if(isdigit(input[i])||input[i]=='('||input[i]=='-')
            {
                #ifdef CHECK
                    printf("%c\n",input[i]);
                    printf("%d\n",i);
                #endif
                int c=change(input,&a,&b);
                if(c==1)
                {
                    free_all(&a);
                    free_all(&b);
                    free(input);
                    i=0;
                    continue;
                }
                calculate(&a);
            }
            else if(input[0]=='D'&&input[1]=='\0')
            {
                free_all(&a);
                free_all(&b);
                free(input);
                i=0;
                continue;
            }
            else
            {
                free_all(&a);
                free_all(&b);
                free(input);
                printf("result>error\n");
                i=0;
                continue;
            }        
        }
        else if(mode=='B')
        {
            #ifdef CHECK
                printf("%s\n",input);
            #endif
            if(isdigit(input[i])||input[i]=='(')
            {
                int c=change_two(input,&a,&b);
                if(c==1)
                {
                    free_all(&a);
                    free_all(&b);
                    free(input);
                    i=0;
                    continue;
                }
                calculate_two(&a);
            }
            else if(input[0]=='B'&&input[1]=='\0')
            {
                free_all(&a);
                free_all(&b);
                free(input);
                i=0;
                continue;
            }
            else
            {
                free_all(&a);
                free_all(&b);
                free(input);
                printf("result>error\n");
                i=0;
                continue;
            }        
        }
        else if(mode=='H')
        {
            if(isdigit(input[i])||input[i]=='('||input[i]=='A'||input[i]=='B'||input[i]=='C'||input[i]=='D'||input[i]=='E'||input[i]=='F')
            {
                int c=change_hex(input,&a,&b);
                if(c==1)
                {
                    free_all(&a);
                    free_all(&b);
                    free(input);
                    i=0;
                    continue;
                }
                calculate_hex(&a);
            }
            else if(input[0]=='H'&&input[1]=='\0')
            {
                free_all(&a);
                free_all(&b);
                free(input);
                i=0;
                continue;
            }
            else
            {
                free_all(&a);
                free_all(&b);
                free(input);
                printf("result>error\n");
                i=0;
                continue;
            }        
        }
        add_history(input);
        write_history(NULL);
        free_all(&a);
        free_all(&b);
        free(input);
        i=0;
    }
    return 0;
}
