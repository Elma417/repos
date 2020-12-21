#include "Stack.h"
#include "Tree.h"
void Init(Tree *a,SqStack *b)
{
    InitStack(b);
    InitTree(a);
}
void CopyAtoB(Tree *a,Tree *b)
{
    (*b).data = (*a).data;
    (*b).father = (*a).father;
    (*b).child = (*a).child;
    (*b).next = (*a).next;
}
void Catch(char S[100])
{
    
}