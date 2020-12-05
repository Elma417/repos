#include <time.h>
//#include <windows.h>
#include "Structure.h"
#include "Tools.h"
/*
const int timeinout = 5;  //进出时间
const int timeupdown = 5; //上下楼时间
const int AllLength = 30;
int AboveRequest; //[当前层，最高层]的请求人数
int UnderRequest; //[最底层，当前层)的请求人数
int Time;         //总时间
Floor floor[15];
char mp[50][50];
*/
//电梯里第一行体重，第二行目标楼层F1~F12
//楼层里第一行体重，第二行耐心值P0~P99
//打印时，将离开的用户出队列
int main()
{
    //时间初始化
    Time = 0;

    Elevator ele;
    Init(&ele);

    //造门
    for (int i = 1; i <= 7 * ele.MaxFloor; i++)
        if (i % 7 != 0)
            mp[i][AllLength / 2 + 1] = -3; //门对应-3 "|"

    //队列初始化
    for (int i = 1; i <= ele.MaxFloor; i++)
    {
        //每层的人数
        floor[i].UpNum = 0;
        floor[i].DownNum = 0;
        InitQueue(&(floor[i].UpQueue));
        InitQueue(&(floor[i].DownQueue));
    }

    int sta = 0;
    int BefTime = 0;
    while (1)
    {
        //如果等待时间超过100秒了，让用户重新选择自动或手动状态
        if (Time - BefTime >= 100 || Time == 0)
        {
            PrintAll(&ele);
            fflush(stdin);
            printf("请输入接下来乘客的生成方式:\n1.自动模式\n2.手动模式\n");
            while (scanf("%d", &sta)==0||(sta != 1 && sta != 2))
                puts("您输入错误，请重新输入。");
            BefTime = Time;
        }

        //输入乘客信息
        if (sta == 1)
            RandomInput(&ele);
        else
            ManualInput(&ele);

        if (ele.Mode == 0) //等待状态
        {
            Time+=timeupdown;
            ele.NowStayTime+=timeupdown;
            if (ele.NowStayTime > ele.MaxStayTime)
                if (ele.NowFloor != 1)
                    ele.NowFloor--;
            PrintAll(&ele);
        }

        else //上升或下降状态
        {
            //处理当层的进出情况：
            GetOut(&ele, &floor[ele.NowFloor]);
            GetIn(&ele, &floor[ele.NowFloor]);

            //切换状态和控制电梯上下
            EleUpDown(&ele);
        }
    }

    return 0;
}
