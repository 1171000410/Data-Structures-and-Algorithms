#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 4
#define MAX_LEN 100

typedef struct strand
{
    int length;
    char data[MAX];
    struct strand *next;
}STR;
void* Create()  //申请空间
{
    void *p=malloc(sizeof(STR));
    if(p==NULL)
    {
        printf("No enough memory！\n");
        exit(0);
    }
    return p;
}
void Insert(STR *str1,STR *str2) //插入节点
{
    str1->next=str2;
}

void PrintResult(int x) //打印结果
{
    if(x)
        printf("比较结果：模式串是主串的子串！\n");
    else
        printf("比较结果：模式串不是主串的子串！\n");
}
void Def(STR *str1,STR *str2,int *len1,int *len2) //输入字符串，并在节点中4个一存
{
    char a;
    int num=0,i;
    STR *node,*p;
    node=(STR*)Create();
    node->next=NULL;
    Insert(str1,node);
    printf("请输入主串(以'#'结尾)：\n");
    while(scanf(" %c",&a))
    {
        if(a=='#')break;
        (*len1)++;
        if(num>=4)
        {
            node->length=num;
            p=node;
            node=(STR*)Create();
            node->next=NULL;
            Insert(p,node);
            num=0;
        }
        node->data[num]=a;
        num++;
    }
    node->length=num;
    num=0;
    node=(STR*)Create();
    node->next=NULL;
    Insert(str2,node);
    printf("请输入模式串(以'#'结尾)：\n");
    while(scanf(" %c",&a))
    {
        if(a=='#')break;
        (*len2)++;
        if(num>=4)
        {
            node->length=num;
            p=node;
            node=(STR*)Create();
            node->next=NULL;
            Insert(p,node);
            num=0;
        }
        node->data[num]=a;
        num++;
    }
    node->length=num;
}

void Get_next(STR *str2,int next[],int len2)
{
    STR *p=str2->next;
    STR *q=str2->next;
    int i=0,j=-1,k=0,pro=1;
    next[0]=-1;
    while(i<len2)
    {
        if(j==-1||p->data[i%4]==q->data[j%4])
        {
            i++;
            j++;
            for(k=pro;k<=i/4;k++)
            {
                pro++;
                p=p->next;
            }
            q=str2->next;
            for(k=1;k<=j/4;k++)q=q->next;
            next[i]=j;
        }
        else {
            j=next[j];
            q=str2->next;
            for(k=1;k<=j/4;k++)q=q->next;
        }
    }
}

int Index_kmp(STR *str1,STR *str2,int len1,int len2)
{
    int i=0,j=0,k=0,pro=1;
    int next[MAX_LEN]={0};
    STR *p=str1->next;
    STR *q=str2->next;
    Get_next(str2,next,len2);
    while(i<len1&&j<len2)
    {
        if(j==-1||p->data[i%4]==q->data[j%4])
        {
            i++;
            j++;
            for(k=pro;k<=i/4;k++)
            {
                pro++;
                p=p->next;
            }
            q=str2->next;
            for(k=1;k<=j/4;k++)
                q=q->next;
        }
        else
        {
            j=next[j];
            q=str2->next;
            for(k=1;k<=j/4;k++)
                q=q->next;
        }
    }
    if(j==len2)
        return 1;
    else
        return 0;
}

int main()
{
    STR *pa,*child;
    int x=0,len1=0,len2=0;
    pa=(STR*)Create();
    child=(STR*)Create();
    pa->next=NULL;
    child->next=NULL;
    Def(pa,child,&len1,&len2);
    x=Index_kmp(pa,child,len1,len2);
    PrintResult(x);
    return 0;
}
