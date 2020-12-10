const int timeinout = 5;  //进出时间
const int timeupdown = 5; //上下楼时间
const int AllLength = 30;
int AboveRequest; //[当前层，最高层]的请求人数
int UnderRequest; //[最底层，当前层)的请求人数
int Time;         //总时间
Floor floor[15];
int mp[100][100];

//文件导入
void Fprint(Elevator *ele)
{
    FILE *fp;

    if ((fp = fopen("input.txt", "r")) == NULL)
    {
        system("cls");
        fflush(stdin);
        printf("输入文件不存在!\n请创建一个\"input.txt\"文件！\n");
        system("PAUSE");
        return;
    }
    int n;
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        Passenger person;
        fscanf(fp, "%d %d %d %d", &person.InitialFloor, &person.TargetFloor, &person.Weight, &person.Patient);
        person.InitialTime = Time;
        if (person.TargetFloor >= person.InitialFloor)
        {
            EnQueue(&(floor[person.InitialFloor].UpQueue), person);
            floor[person.InitialFloor].UpNum++;
        }
        else
        {
            EnQueue(&(floor[person.InitialFloor].DownQueue), person);
            floor[person.InitialFloor].DownNum++;
        }

        if ((*ele).Mode == 0)
        {
            (*ele).NowStayTime = 0;
            if (person.InitialFloor >= (*ele).NowFloor)
                (*ele).Mode = 1;
            else
                (*ele).Mode = 2;
        }

        if (person.InitialFloor > (*ele).NowFloor)
            AboveRequest++;
    }
    fclose(fp);
}

void PrintEle(Elevator *ele)
{
    if ((*ele).WeightWarn == 1)
    {
        printf("警报已被触发！！！");
    }
    for (int i = 0; i <= 7 * (*ele).MaxFloor + 1; i++)
    {
        for (int j = 0; j <= AllLength + 1; j++)
            switch (mp[i][j])
            {
            case -11:
                printf("  ");
                break;
            case -10:
                printf("P ");
                break;
            case -9:
                printf("▼");
                break;
            case -8:
                printf("# ");
                break;
            case -7:
                printf("▲");
                break;
            case -6:
                printf("F ");
                break;
            case -5:
                printf("W ");
                break;
            case -4:
                printf("==");
                break;
            case -3:
                printf("| ");
                break;
            case -2:
                printf("■");
                break;
            case -1:
                printf("  ");
                break;
            default:
                printf("%02d", mp[i][j]);
                break;
            }
        puts("");
    }
}

//打印当前时间
void PrintTime()
{
    int h, min, sec;
    sec = Time % 60;
    min = Time / 60;
    h = Time / (60 * 60);
    printf("目前的运行时间为%02d:%02d:%02d\n", h, min, sec);
}

void InitMp(Elevator *ele)
{
    //空格对应-1" " 除了门全部清空
    for (int i = 0; i <= 7 * (*ele).MaxFloor + 1; i++)
        for (int j = 0; j <= AllLength + 1; j++)
            if (!(i % 7 != 0 && j == AllLength / 2 + 1))
                mp[i][j] = -1;

    //头尾封墙,墙对应-2 "■"
    for (int j = 0; j <= AllLength + 1; j++)
        mp[0][j] = mp[7 * (*ele).MaxFloor + 1][j] = -2;

    //左封墙
    for (int i = 0; i <= 7 * (*ele).MaxFloor + 1; i++)
        mp[i][0] = -2;

    //构建楼层
    for (int i = 7; i <= 7 * (*ele).MaxFloor; i += 7)
    {
        for (int j = AllLength / 2 + 1; j <= AllLength; j++)
        {
            mp[i][j] = -2;
        }
        mp[i][AllLength + 1] = (*ele).MaxFloor - i / 7 + 1;
    }
}

void PrintAll(Elevator *ele)
{
    //system("pause");
    //system("cls");
    InitMp(ele);
    PrintTime();

    //打印电梯
    //打印电梯底座
    for (int j = 1; j <= AllLength / 2; j++)
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7][j] = -4; //楼层对应-4 "="

    //打印电梯里的上升队列人
    QueuePtr p = (*ele).UpQueue.front;
    int stpos = 1;

    while (p->next != NULL)
    {
        //打印体重
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7 - 6][stpos] = -5; //W对应-5"W"
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7 - 6][stpos + 1] = p->next->people.Weight;
        //打印目标楼层
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7 - 5][stpos] = -6; //F对应-6"F"
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7 - 5][stpos + 1] = p->next->people.TargetFloor;

        //打印人
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7 - 4][stpos] = -7;     //"▲"对应-7
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7 - 4][stpos + 1] = -8; //"#"对应-8
        //改变stpos
        stpos += 2;
        p = p->next;
    }

    stpos = 1;
    //打印电梯里的下降队列人
    p = (*ele).DownQueue.front;
    while (p->next != NULL)
    {
        //打印体重
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7 - 3][stpos] = -5; //W对应-5
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7 - 3][stpos + 1] = p->next->people.Weight;
        //打印目标楼层
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7 - 2][stpos] = -6; //F对应-6"F"
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7 - 2][stpos + 1] = p->next->people.TargetFloor;
        //打印人
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7 - 1][stpos] = -9;     //"xia"对应-9
        mp[((*ele).MaxFloor - (*ele).NowFloor + 1) * 7 - 1][stpos + 1] = -8; //"#"对应-8
        //改变stpos
        stpos += 2;
        p = p->next;
    }

    //打印楼层里的人
    for (int i = 1; i <= (*ele).MaxFloor; i++) //楼层数
    {
        //打印楼层里的上升队列人
        p = floor[i].UpQueue.front;
        stpos = AllLength / 2 + 2;
        while (p->next != NULL)
        {
            //将耐心值超限的人移除
            if (p->next->people.Patient + p->next->people.InitialTime < Time)
            {
                QueuePtr q = p->next;
                if (q->people.InitialFloor > (*ele).NowFloor)
                    AboveRequest--;
                else if (q->people.InitialFloor < (*ele).NowFloor)
                    UnderRequest--;
                p->next = p->next->next;
                if ((floor[i].UpQueue).rear == q)
                    (floor[i].UpQueue).rear = p;
                printf("第%d层的人因为耐心值超限而离开\n", q->people.InitialFloor);
                free(q);
                floor[i].UpNum--;
                continue;
            }

            //打印体重
            mp[(ele->MaxFloor + 1 - i) * 7 - 6][stpos] = -5;
            mp[(ele->MaxFloor + 1 - i) * 7 - 6][stpos + 1] = p->next->people.Weight;
            mp[(ele->MaxFloor + 1 - i) * 7 - 6][stpos + 2] = -1;
            //打印目标楼层
            mp[(ele->MaxFloor + 1 - i) * 7 - 5][stpos] = -10; //P -10
            mp[(ele->MaxFloor + 1 - i) * 7 - 5][stpos + 1] = p->next->people.Patient;
            mp[(ele->MaxFloor + 1 - i) * 7 - 5][stpos + 2] = -1;
            //打印人
            mp[(ele->MaxFloor + 1 - i) * 7 - 4][stpos] = -7;
            mp[(ele->MaxFloor + 1 - i) * 7 - 4][stpos + 1] = -8;
            mp[(ele->MaxFloor + 1 - i) * 7 - 4][stpos + 2] = -1;
            //改变stpos
            stpos += 3;
            p = p->next;
        }

        //打印楼层里的下降队列人
        p = floor[i].DownQueue.front;
        stpos = AllLength / 2 + 2;
        while (p->next != NULL)
        {
            //将耐心值超限的人移除
            if (p->next->people.Patient + p->next->people.InitialTime < Time)
            {
                QueuePtr q = p->next;
                if (q->people.InitialFloor > (*ele).NowFloor)
                    AboveRequest--;
                else if (q->people.InitialFloor < (*ele).NowFloor)
                    UnderRequest--;
                p->next = p->next->next;
                if ((floor[i].DownQueue).rear == q)
                    (floor[i].DownQueue).rear = p;
                printf("第%d层的人因为耐心值超限而离开\n", q->people.InitialFloor);
                free(q);
                floor[i].DownNum--;
                continue;
            }

            //打印体重
            mp[(ele->MaxFloor + 1 - i) * 7 - 3][stpos] = -5;
            mp[(ele->MaxFloor + 1 - i) * 7 - 3][stpos + 1] = p->next->people.Weight;
            mp[(ele->MaxFloor + 1 - i) * 7 - 3][stpos + 2] = -1;
            //打印目标楼层
            mp[(ele->MaxFloor + 1 - i) * 7 - 2][stpos] = -10;
            mp[(ele->MaxFloor + 1 - i) * 7 - 2][stpos + 1] = p->next->people.Patient;
            mp[(ele->MaxFloor + 1 - i) * 7 - 2][stpos + 2] = -1;
            //打印人
            mp[(ele->MaxFloor + 1 - i) * 7 - 1][stpos] = -9;
            mp[(ele->MaxFloor + 1 - i) * 7 - 1][stpos + 1] = -8;
            mp[(ele->MaxFloor + 1 - i) * 7 - 1][stpos + 2] = -1;
            //改变stpos
            stpos += 3;
            p = p->next;
        }
    }
    //输出
    PrintEle(ele);
    puts("");
    printf("目前上升请求数：%d\n目前下降请求数：%d\n", AboveRequest, UnderRequest);
    printf("电梯总重：%d\n", (*ele).NowWeight);
    printf("电梯人数：%d\n", (*ele).NowPassengerNumber);
    printf("电梯所在楼层：%d\n", (*ele).NowFloor);
    switch ((*ele).Mode)
    {
    case 0:
        printf("电梯目前为等待状态\n");
        break;
    case 1:
        printf("电梯目前为上升状态\n");
        break;
    case 2:
        printf("电梯目前为下降状态\n");
        break;
    }
    puts("");
}

//电梯内的乘客出电梯
void GetOut(Elevator *ele, Floor *flo)
{
    //开始记录当层等待时间
    (*ele).NowWaitTime = 0;
    //删除门
    int st = 7 * ((*ele).MaxFloor - (*ele).NowFloor + 1) - 1;
    for (int i = st; i >= st - 6; i--)
        mp[i][AllLength / 2 + 1] = -11;

    //1.处理电梯上升队列

    //从电梯里的第一个乘客遍历到最后一个
    for (QueuePtr i = (*ele).UpQueue.front; (i != NULL && i->next != NULL); i = i->next)
    {

        //如果该乘客要在此楼下来，删除该节点
        if (i->next->people.TargetFloor == (*ele).NowFloor)
        {
            i->next->people.Patient = 9999999;
            //删除这个节点
            QueuePtr p = i->next;
            i->next = p->next;
            if (((*ele).UpQueue).rear == p)
                ((*ele).UpQueue).rear = i;

            //加入该楼层上升队列的头，体现动态离开的效果
            EnFront(&((*flo).UpQueue), p->people);

            //电梯总人数--
            (*ele).NowPassengerNumber--;
            //该楼层总人数++
            (*flo).UpNum++;
            //增加总时间
            Time += timeinout;
            //增加等待时间
            (*ele).NowWaitTime += timeinout;

            //开启时间警报
            if ((*ele).NowWaitTime > (*ele).MaxWaitTime)
                (*ele).TimeWarn = 1;

            //打印
            PrintAll(ele);

            //状态显示
            puts("乘客正在出电梯，门已经开启\n");

            //将该用户从该楼层上升队列出队
            DeQueue(&((*flo).UpQueue), &p->people);

            //该楼层总人数--
            (*flo).UpNum--;

            //打印
            PrintAll(ele);

            //释放这个节点
            free(p);
        }
    }

    //2.处理电梯下降队列
    for (QueuePtr i = (*ele).DownQueue.front; (i != NULL && i->next != NULL); i = i->next)
    {
        //如果该乘客要在此楼下来，删除该节点
        if (i->next->people.TargetFloor == (*ele).NowFloor)
        {
            i->next->people.Patient = 9999999;
            //删除这个节点
            QueuePtr p = i->next;
            i->next = p->next;
            if (((*ele).DownQueue).rear == p)
                ((*ele).DownQueue).rear = i;

            //加入该楼层上升队列的头，体现动态离开的效果
            EnFront(&((*flo).UpQueue), p->people);

            //电梯总人数--
            (*ele).NowPassengerNumber--;
            //该楼层总人数++
            (*flo).UpNum++;
            //增加总时间
            Time += timeinout;
            //增加等待时间
            (*ele).NowWaitTime += timeinout;

            //开启时间警报
            if ((*ele).NowWaitTime > (*ele).MaxWaitTime)
                (*ele).TimeWarn = 1;

            //打印
            PrintAll(ele);

            //状态显示
            puts("乘客正在出电梯，门已经开启\n");

            //将该用户从该楼层上升队列出队
            DeQueue(&((*flo).UpQueue), &p->people);
            //该楼层总人数--
            (*flo).UpNum--;

            //打印
            PrintAll(ele);

            //释放这个节点
            free(p);
        }
    }

    //回溯门
    for (int i = st; i >= st - 6; i--)
        mp[i][AllLength / 2 + 1] = -3;
}

//该层乘客进电梯
void GetIn(Elevator *ele, Floor *flo)
{
    //删除门
    int st = 7 * ((*ele).MaxFloor - (*ele).NowFloor + 1) - 1;
    for (int i = st; i >= st - 6; i--)
        mp[i][AllLength / 2 + 1] = -11;

    //电梯为上升状态
    if ((*ele).Mode == 1)
    {
        //处理楼层上升队列
        /* for (QueuePtr i = (*flo).UpQueue.front;(i!=NULL&&i->next != NULL); i = i->next)*/
        while ((*flo).UpNum > 0)
        {

            if ((*ele).NowPassengerNumber == (*ele).MaxPassengerNumber)
                break;
            QueuePtr i = (*flo).UpQueue.front;
            //将这位乘客加入电梯队列队首
            EnFront(&((*ele).UpQueue), i->next->people);

            //删除这个节点
            QueuePtr p = i->next;
            i->next = i->next->next;
            if (((*ele).UpQueue).rear == p)
                ((*ele).DownQueue).rear = i;
            (*ele).NowWeight += p->people.Weight;
            free(p);

            //当层楼人数--
            (*flo).UpNum--;

            //增加乘客出电梯的时间
            Time += timeinout;
            //电梯内的乘客数加1
            (*ele).NowPassengerNumber++;
            //减少上升请求人数

            //特判一下有没有超重警告
            if ((*ele).NowWeight > (*ele).MaxWeight)
            {
                //启动重量警报
                (*ele).WeightWarn = 1;

                //从电梯里删除超重的那个人
                Passenger temp;
                DeQueue(&((*ele).UpQueue), &temp);
                (*ele).NowWeight -= temp.Weight;
                //重新把那个人放回该楼层原队列原位置
                QueuePtr q = (QueuePtr)malloc(sizeof(QNode));
                q->people = temp;
                q->next = i->next;
                i->next = q;
                //当层楼人数++
                (*flo).UpNum++;

                //增加总时间
                Time += timeinout;
                //增加等待时间
                (*ele).NowWaitTime += timeinout;
                //开启时间警报
                if ((*ele).NowWaitTime > (*ele).MaxWaitTime)
                    (*ele).TimeWarn = 1;
                //电梯内的乘客数减1
                (*ele).NowPassengerNumber--;
                //消除重量警报
                (*ele).WeightWarn = 0;
            }

            PrintAll(ele);
            //状态显示
            puts("乘客正在进电梯，门已经开启\n");
        }
    }
    else //下降状态
    {
        //处理楼层下降队列
        /*  for (QueuePtr i = (*flo).DownQueue.front; (i != NULL && i->next != NULL); i = i->next)*/
        while ((*flo).DownNum > 0)
        {
            if ((*ele).NowPassengerNumber == (*ele).MaxPassengerNumber)
                break;

            QueuePtr i = (*flo).DownQueue.front;
            //将这位乘客加入电梯队列队首
            EnFront(&((*ele).DownQueue), i->next->people);

            //删除这个节点
            QueuePtr p = i->next;
            i->next = i->next->next;
            if (((*ele).DownQueue).rear == p)
                ((*ele).DownQueue).rear = i;
            (*ele).NowWeight += p->people.Weight;
            free(p);

            //当层楼人数--
            (*flo).DownNum--;
            //增加乘客出电梯的时间
            Time += timeinout;
            //电梯内的乘客数加1
            (*ele).NowPassengerNumber++;

            //特判一下有没有超重警告
            if ((*ele).NowWeight > (*ele).MaxWeight)
            {
                //启动重量警报
                (*ele).WeightWarn = 1;

                //从电梯里删除超重的那个人
                Passenger temp;
                DeQueue(&((*ele).DownQueue), &temp);
                (*ele).NowWeight -= temp.Weight;

                //重新把那个人放回该楼层原队列原位置
                QueuePtr q = (QueuePtr)malloc(sizeof(QNode));
                q->people = temp;
                q->next = i->next;
                i->next = q;
                //当层楼人数++
                (*flo).DownNum++;

                //增加总时间
                Time += timeinout;
                //增加等待时间
                (*ele).NowWaitTime += timeinout;
                //开启时间警报
                if ((*ele).NowWaitTime > (*ele).MaxWaitTime)
                    (*ele).TimeWarn = 1;
                //电梯内的乘客数减1
                (*ele).NowPassengerNumber--;
                //消除重量警报
                (*ele).WeightWarn = 0;
            }

            PrintAll(ele);
            //状态显示
            puts("乘客正在进电梯，门已经开启\n");
        }
    }
    //等待状态不会调用这个函数，不用判断

    (*ele).TimeWarn = 0;    //取消时间警报
    (*ele).NowWaitTime = 0; //清空当前等待时间

    //回溯门
    for (int i = st; i >= st - 6; i--)
        mp[i][AllLength / 2 + 1] = -3;
}

//控制上下楼以及状态变更
void EleUpDown(Elevator *ele)
{
    //处理完(*ele).NowFloor楼层的进出后，调用此函数

    //上升
    if ((*ele).Mode == 1)
    {
        //如果全部楼层无人请求
        if (AboveRequest == 0 && UnderRequest == 0 && floor[(*ele).NowFloor].UpNum + floor[(*ele).NowFloor].DownNum == 0 && (*ele).NowPassengerNumber==0)
        {
            //切换成等待状态
            (*ele).Mode = 0;
        }

        //上升切换下降
        else if (AboveRequest == 0 && UnderRequest != 0 && (*ele).NowPassengerNumber==0)
        {
            //切换为下降状态
            (*ele).Mode = 2;
        }

        //一般情况
        else
        {
            UnderRequest = UnderRequest + floor[(*ele).NowFloor].DownNum + floor[(*ele).NowFloor].UpNum;
            (*ele).NowFloor++;
            AboveRequest = AboveRequest - floor[(*ele).NowFloor].DownNum - floor[(*ele).NowFloor].UpNum;
            Time += timeupdown;
            PrintAll(ele);
        }
    }
    //下降
    else
    {
        //如果全部楼层无人请求
        if (AboveRequest == 0 && UnderRequest == 0 && floor[(*ele).NowFloor].UpNum + floor[(*ele).NowFloor].DownNum == 0 && (*ele).NowPassengerNumber==0)
        {
            //切换成等待状态
            (*ele).Mode = 0;
        }

        //上升切换下降
        else if (AboveRequest == 0 && UnderRequest != 0 && (*ele).NowPassengerNumber==0)
        {
            //切换为上升状态
            (*ele).Mode = 1;
        }

        //一般情况
        else
        {
            AboveRequest = AboveRequest + floor[(*ele).NowFloor].DownNum + floor[(*ele).NowFloor].UpNum;
            (*ele).NowFloor--;
            UnderRequest = UnderRequest - floor[(*ele).NowFloor].DownNum - floor[(*ele).NowFloor].UpNum;
            Time += timeupdown;
            PrintAll(ele);
        }
    }
    //等待状态不调用此函数
}

//随机生成乘客
void RandomInput(Elevator *ele)
{
    Passenger person;
    srand(time(NULL));

    //控制每秒钟生成人的概率为1/15
    if (rand() % 15 == 0)
        return;

    //生成起始楼层
    do
    {
        person.InitialFloor = rand() % 12 + 1;
    } while (person.InitialFloor == (*ele).NowFloor);

    //生成目标楼层
    do
    {
        person.TargetFloor = rand() % 12 + 1;
    } while (person.TargetFloor == person.InitialFloor);

    //生成乘客体重
    person.Weight = rand() % 60 + 40;

    //生成乘客耐心值
    person.Patient = rand() % 90 + 10;

    person.InitialTime = Time;

    if (person.TargetFloor > person.InitialFloor)
    {
        EnQueue(&(floor[person.InitialFloor].UpQueue), person);
        floor[person.InitialFloor].UpNum++;
    }
    else
    {
        EnQueue(&(floor[person.InitialFloor].DownQueue), person);
        floor[person.InitialFloor].DownNum++;
    }
    if ((*ele).Mode == 0)
    {
        (*ele).NowStayTime = 0;
        if (person.InitialFloor >= (*ele).NowFloor)
            (*ele).Mode = 1;
        else
            (*ele).Mode = 2;
    }

    if (person.InitialFloor > (*ele).NowFloor)
        AboveRequest++;
    else if (person.InitialFloor < (*ele).NowFloor)
        UnderRequest++;
}

//手动输入乘客
void ManualInput(Elevator *ele)
{
    Passenger person;
    int Turn;
    while (1)
    {
        fflush(stdin);
        printf("请输入这一秒生成的人数[0,10]:");
        if (scanf("%d", &Turn) == 0 || Turn < 0 || Turn > 10)
        {
            printf("输入非法\n");
            continue;
        }
        break;
    }

    for (int i = 1; i <= Turn; i++)
    {
        while (1)
        {
            printf("请输入第%d名乘客的起始楼层[0,12]:", i);
            fflush(stdin);
            if (scanf("%d", &person.InitialFloor) == 0 || person.InitialFloor <= 0 || person.InitialFloor >= 13)
            {
                printf("输入非法\n");
                continue;
            }
            break;
        }
        while (1)
        {
            printf("请输入第%d名乘客的目标楼层[1,12]:", i);
            fflush(stdin);
            if (scanf("%d", &person.TargetFloor) == 0 || person.TargetFloor < 1 || person.TargetFloor > 12)
            {
                printf("输入非法\n");
                continue;
            }
            break;
        }
        while (1)
        {
            printf("请输入第%d名乘客的体重[40,99]kg:", i);
            fflush(stdin);
            if (scanf("%d", &person.Weight) == 0 || person.Weight < 40 || person.Weight > 99)
            {
                printf("输入非法\n");
                continue;
            }
            break;
        }
        while (1)
        {
            printf("请输入第%d名乘客的耐心值[10,99]s:", i);
            fflush(stdin);
            if (scanf("%d", &person.Patient) == 0 || person.Patient < 10 || person.Patient > 99)
            {
                printf("输入非法\n");
                continue;
            }
            break;
        }
        person.InitialTime = Time;

        if (person.TargetFloor >= person.InitialFloor)
        {
            EnQueue(&(floor[person.InitialFloor].UpQueue), person);
            floor[person.InitialFloor].UpNum++;
        }
        else
        {
            EnQueue(&(floor[person.InitialFloor].DownQueue), person);
            floor[person.InitialFloor].DownNum++;
        }

        if ((*ele).Mode == 0)
        {
            (*ele).NowStayTime = 0;
            if (person.InitialFloor >= (*ele).NowFloor)
                (*ele).Mode = 1;
            else
                (*ele).Mode = 2;
        }

        if (person.InitialFloor > (*ele).NowFloor)
            AboveRequest++;
        else if (person.InitialFloor < (*ele).NowFloor)
            UnderRequest++;
    }
}

//打印时，将离开的用户出队列
void Init(Elevator *ele)
{
    InitQueue(&((*ele).UpQueue));
    InitQueue(&((*ele).DownQueue));
    (*ele).NowFloor = 1;
    (*ele).MaxFloor = 12;
    (*ele).NowWeight = 0;
    (*ele).MaxWeight = 500;
    (*ele).NowWaitTime = 0;
    (*ele).MaxWaitTime = 300;
    (*ele).NowStayTime = 0;
    (*ele).MaxStayTime = 0;
    (*ele).NowPassengerNumber = 0;
    (*ele).MaxPassengerNumber = 12;
    (*ele).Mode = 0;
    (*ele).WeightWarn = 0;
    (*ele).TimeWarn = 0;
    //楼层初始化
    for (int i = 1; i <= (*ele).MaxFloor; i++)
    {
        floor[i].UpNum = 0;
        floor[i].DownNum = 0;
        InitQueue(&(floor[i].UpQueue));
        InitQueue(&(floor[i].DownQueue));
    }
}
