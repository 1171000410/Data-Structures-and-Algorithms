#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_LEN 2000
typedef struct node
{
    int key;
    int value;
    struct node* next[];
}Node;

typedef struct list
{
    int level;
    struct node* head;
}List;

Node* CreateNode(int level,int key,int value)
{
    int i;
    Node *p=(Node*)malloc(sizeof(Node)+(level+1)*sizeof(Node*));
    if(p==NULL)
    {
        printf("No enough memory !\n");
        exit(0);
    }
    p->key=key;
    p->value=value;
    for(i=0;i<=level;i++)
        p->next[i]=NULL;

    return p;
}

List* Create()
{
    List *p;
    p=(List*)malloc(sizeof(List));
    if(p==NULL)
    {
        printf("No enough memory !\n");
        exit(0);
    }
    p->level=0;
    p->head=CreateNode(0,-1,-1);

    return p;
}

void Menu()
{
    printf(" \n\n跳跃表可执行操作如下\n");
    printf("1. 添加新节点\n");
    printf("2. 删除旧节点\n");
    printf("3. 查找节点\n");
    printf("4. 打印跳跃表\n");
    printf("5. 退出\n");
    printf("\n请输入执行的操作：\n");
}

int Random_Level(List* skiplist)
{
    int level=0;
    srand((int)time(0));
    while(rand()%2)
    {
        level++;
    }
    if(level>(skiplist->level))
        level=(skiplist->level)+1;

    return level;
}

void InsertNode(List* skiplist,int key,int value)
{
    int i=0,level=0,flag=0;
    Node *p=skiplist->head,*update[MAX_LEN],*q=NULL,*m=NULL;
    level=Random_Level(skiplist);
    if(level>(skiplist->level))
    {
        m=skiplist->head;
        skiplist->level=level;
        skiplist->head=CreateNode(level,-1,-1);
        for(i=0;i<=(skiplist->level-1);i++)(skiplist->head)->next[i]=m->next[i];
        free(m);
    }
    p=skiplist->head;
    for(i=skiplist->level;i>=0;i--)
    {
        q=p->next[i];
        while(q!=NULL&&(q->key)<key)
        {
            p=q;
            q=p->next[i];
        }
        update[i]=p;
    }
    if(q!=NULL&&q->key==key)
        flag = 1;
    if(!flag)
    {
        q=CreateNode(level,key,value);
        for(i=level;i>=0;i--)
        {
            q->next[i]=update[i]->next[i];
            update[i]->next[i]=q;
        }
    }
    else
        printf("结点重复，请重新输入！\n");
}
void PrintList(List *skiplist)
{
    printf("\n");
    int i=0;
    Node *p;
    for(i=skiplist->level;i>=0;i--)
    {
        p=skiplist->head;
        while(p!=NULL)
        {
            if(p->key!=-1)
                printf("%d ",p->key);
            p=p->next[i];
        }
        printf("\n");
    }
}
void DeleteNode(List *skiplist,int key)
{
    int i=0 , flag = 0 ;
    Node *p=skiplist->head,*update[MAX_LEN],*q=NULL;
    for(i=skiplist->level;i>=0;i--)
    {
        q=p->next[i];
        while(q!=NULL&&(q->key)<key)
        {
            p=q;
            q=p->next[i];
        }
        update[i]=p;
    }
    if((q==NULL)||(q->key!=key))
        flag=1;
    if(!flag)
    {
        for(i=skiplist->level;i>=0;i--)
        {
            if(update[i]->next[i] != NULL&&(update[i]->next[i])->key == key)
            {
                q=update[i]->next[i];
                update[i]->next[i]=q->next[i];
            }
            if((skiplist->head)->next[i]==NULL)
                skiplist->level--;
        }
        free(q);
    }
    else printf("节点不存在，请重新删除！\n");
}
int SearchNode(List *skiplist,int key)
{
    int flag=0,i=0;
    Node *p = skiplist->head,*q=NULL;
    for(i=skiplist->level;i>=0;i--)
    {
        q=p->next[i];
        while(q!=NULL&&q->key<key)
        {
            p=q;
            q=p->next[i];
        }
        if(q!=NULL&&q->key==key)
        {
            printf("查询节点的value值：%d\n",q->value);
            flag=1;
            break;
        }
    }
    if(!flag)
        printf("查找失败，不存在该节点！\n");
}
int main()
{
    int key = 0 , value = 0 , ch = 0;
    List *newlist;
    newlist=Create();
    while(1)
    {
        Menu();
        scanf("%d",&ch);
        if(ch==5)
            break;
        switch(ch)
        {
            case 1:
                printf("请输入添加节点的key值,value值 (示例：3 10)(输入key值为-1结束)：\n");
                while(scanf("%d %d",&key,&value))
                {
                    if(key==-1)
                        break;
                    InsertNode(newlist,key,value);
                }
                break;
            case 2:
                printf("请输入待删除节点的key值：\n");
                scanf("%d",&key);
                DeleteNode(newlist,key);
                break;
            case 3:
                printf("请输入待查询节点的key值：\n");
                scanf("%d",&key);
                SearchNode(newlist,key);
                break;
            case 4:
                printf("跳跃表如下：\n");
                PrintList(newlist);
        }
    }
    return 0;
}
