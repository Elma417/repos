#include "tool.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
void main()
{
    SqStack *b;
    Init(root,b);
    while(1)
    {
        //清屏
        PrintAll(root,0,"100000");
        //PrintAll(root,0,code)
        char s[100];
        fgets(s,100,stdin);
        //LINUX;
        Catch(s);
        {

        }
        printf("操作完成！");
        //暂停
    }
}