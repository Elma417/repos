typedef int Status;
typedef Data TElemType;
#define MAX_TREE_SIZE 100
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0
#define OK 1

typedef struct Tree
{
    TElemType data;
    struct Tree *father, *child, *next;
} Tree;

Tree *root;

typedef struct Data
{
    char code[10]; //类型：学校x；学院x；专业x；班级x；学生xx
    char name[20];
    int score;
} Data;

int JudgeType(char code[10])
{
    for (int i = 1; i <= 3 ;i++)
        if(code[i]-'0'==0)
            return i - 1;
    if(code[4]==0&&code[5]==0)
        return 3;
    return 4;
    //学校：0；学院：1；专业：2；班级：3；学生：4
}
void InitTree(Tree *t)
{
    (*t).father = (Tree *)malloc(MAX_TREE_SIZE * sizeof(Tree));
    (*t).child = (Tree *)malloc(MAX_TREE_SIZE * sizeof(Tree));
    (*t).next = (Tree *)malloc(MAX_TREE_SIZE * sizeof(Tree));
}
void AddTree(Tree *t, TElemType node)
{
}

Tree *SearchTree(Tree *t, char code[10])
{
}

void PrintAll(Tree *t, int Mode, char code[10])
{
    //Mode 0 输出整棵树 并将所有学生制表 以及班级的统计数据
    if(Mode==0)
    {
        Tree *now = (*t).child;
        if(now!=NULL)
        {
            
        }
        while((*now).next!=NULL)
        {

            now = now->next;
        }
    }


    //Mode 1 不涉及班级的输出
    //只需要输出到code代表的节点以及它的子节点
        //Mode 2 输入的code是班级
        //输出到该班级 只将该班级的学生单独制表 以及统计数据
            //Mode 3 输入的Code是学生
            //输出到该班级
                //将该学生的数据制表（不要输出其他学生 其他班级的数据）

                    //格式依照上述需求
}