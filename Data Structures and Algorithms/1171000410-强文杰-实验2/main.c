#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 50
/*二叉树的二叉链表结构*/
typedef struct node
{
    struct node *lchild;
    struct node *rchild;
    char data;
}BTREE;
/*栈的数组实现*/
typedef struct
{
    int top;
    BTREE *a[MAX_LEN]; //结构体数组，每个元素均为一个结点
}Stack;
/*队列的数组实现*/
typedef struct
{
    BTREE *a[MAX_LEN]; //结构体数组，每个元素均为一个结点
    int front;
    int rear;
}Queue;
/*为栈分配空间*/
Stack *Createstack()
{
    Stack *p;
    p = (Stack *)malloc(sizeof(Stack));
    p->top = -1;
    return p;
}
/*为队列分配空间*/
Queue *Createqueue()
{
    Queue *p;
    p = (Queue *)malloc(sizeof(Queue));
    p->front = 0;
    p->rear = 0;
    return p;
}
/*菜单*/
int Menu()
{
    int x;
    printf("\n\n");
    printf("1.先序遍历(递归)\n");
    printf("2.先序遍历(非递归)\n");
    printf("3.中序遍历(递归)\n");
    printf("4.中序遍历(非递归)\n");
    printf("5.后序遍历(递归)\n");
    printf("6.后序遍历(非递归)\n");
    printf("7.层序遍历\n");
    printf("8.判断其是否为完全二叉树\n");
    printf("9.求二叉树中任意两个结点的公共祖先\n");
    printf("10.退出\n\n");
    printf("请选择你要执行的操作：\n");
    scanf("%d",&x);
    return x;
}
/*先序遍历建立二叉树*/
void CreateBT(BTREE **T)
{
    char ch;
    scanf(" %c",&ch);
    if(ch=='#')
        *T = NULL;
    else
    {
        *T = (BTREE *)malloc(sizeof(BTREE));
        if(*T==NULL)
        {
            printf("No enough memory！\n");
            exit(0);
        }
        (*T)->data = ch;
        CreateBT(&((*T)->lchild));   //构造左子树
        CreateBT(&((*T)->rchild));   //构造右子树
    }
}
/*压栈*/
void Push(Stack *s,BTREE *p)
{
    s->top++;
    s->a[s->top] = p;
}
/*出栈*/
BTREE *Pop(Stack *s)
{
    BTREE *p;
    if (s->top == -1)
    {
    printf("栈空！\n");
    return NULL;
    }
    p = s->a[s->top];
    s->top--;
    return p;
}
/*栈顶*/
BTREE *Top(Stack *s)
{
    BTREE *p;
    if (s->top == -1)
    {
    printf("栈空！\n");
    return NULL;
    }
    p = s->a[s->top];
    return p;
}
/*输出结点数据*/
void Printdata(char ch)
{
    printf("%c  ",ch);
}
/*先序遍历二叉树递归算法*/
void Preorder(BTREE *T)
{
    if(T == NULL)
    {
        return;
    }
    Printdata(T->data);
    Preorder(T->lchild);
    Preorder(T->rchild);
}
/*中序遍历二叉树的递归算法*/
void Inorder(BTREE *T)
{
    if(T != NULL)
    {
        Inorder(T->lchild);
        Printdata(T->data);
        Inorder(T->rchild);
    }
}
/*后序遍历二叉树的递归算法*/
void Postorder(BTREE *T)
{
    if(T != NULL)
    {
        Postorder(T->lchild);
        Postorder(T->rchild);
        Printdata(T->data);
    }
}
/*先序遍历二叉树的非递归算法,栈顶保存当前结点的左子树*/
void NPreorder(BTREE *T)
{
     Stack *s;
     s = Createstack(); //创建一个栈
     while(T!=NULL||s->top!=-1)
     {
         while(T!=NULL)   //直到最左
         {
             Printdata(T->data);
             Push(s,T);
             T=T->lchild;
         }
         if(s->top!=-1)
         {
             T=Pop(s);
             T=T->rchild;
         }
     }
}
/*中序遍历二叉树的非递归算法*/
void NInorder(BTREE *T)
{
     Stack *s;
     s = Createstack(); //创建一个栈
     while(T!=NULL||s->top!=-1)
     {
         while(T!=NULL)
         {
             Push(s,T);
             T=T->lchild;
         }
         if(s->top!=-1)
         {
             T=Pop(s);
             Printdata(T->data); //输出位置不同，其余与先序非递归遍历一致
             T=T->rchild;
         }
     }
}
/*后序遍历的非递归算法，不设标志，设一变量*/
void NPostorder(BTREE *T)
{
    BTREE *p,*pr;
    Stack *s;
    s = Createstack(); //创建一个栈
    p = T;
    while(p!=NULL||s->top!=-1)
    {
        while(p!=NULL)
        {
            Push(s,p);
            pr = p->rchild;
            p = p->lchild;
            if(p==NULL)    //直到最底层，即后序遍历第一个
            p = pr;
        }
        p = Pop(s);
        Printdata(p->data);
        if(s->top!=-1&&Top(s)->lchild==p)
            p=Top(s)->rchild;  //遍历右子树
        else
            p=NULL;
    }
}
/*层序遍历，队列实现*/
void Levelorder(BTREE *T)
{
    Queue *p;
    p = Createqueue();  //创建一个队列
    if(T==NULL)
        return;
    p->rear++;   //二叉树非空，根指针入队
    p->a[p->rear]=T;
    while(p->front !=p->rear)  //循环直到队列不为空
    {
        p->front++;
        T=p->a[p->front];
        Printdata(T->data);
        if(T->lchild!=NULL) //若结点存在左孩子，将左孩子入队
        {
            p->rear++;
            p->a[p->rear]=T->lchild;
        }
        if(T->rchild!=NULL) //若结点存在右孩子，将右孩子入队
        {
            p->rear++;
            p->a[p->rear]=T->rchild;
        }
    }
}
/*判断二叉树是否为完全二叉树，采用层序遍历的方式*/
int CompleteTree(BTREE *T)
{
    Queue *p;
    p = Createqueue(); //创建队列
    if(T==NULL)
        return 0;
    p->rear++; //二叉树非空，根指针入队
    p->a[p->rear]=T;
    while(p->front !=p->rear)   //循环直到队列不空
    {
        if(T->lchild!=NULL&&T->rchild!=NULL) //若结点左右孩子都不为空，结点出队，左右孩子进队
        {
            p->front++;
            T=p->a[p->front];
            if(T->lchild!=NULL)
            {p->rear++;
            p->a[p->rear]=T->lchild;}
            if(T->rchild!=NULL)
            {p->rear++;
            p->a[p->rear]=T->rchild;}
        }
        if(T->lchild==NULL&&T->rchild!=NULL) //如果只有右子树没有左子树，不是
            return 0;
        if((T->lchild!=NULL&&T->rchild==NULL)||(T->lchild==NULL&&T->rchild==NULL))
            //左孩子不空右孩子空，或者左右都空,则该结点之后的所有结点必定是叶子结点
        {
            p->front++;
            while(p->front !=p->rear)
            {
                T=p->a[p->front];
                if(T->lchild==NULL&&T->rchild==NULL)
                    p->front++;
                else
                    return 0;
            }
            return 1;
        }
    }
    return 1;
}
/*先序递归遍历，寻找数据对应的结点*/
BTREE *Getnode(BTREE *m,char c)
{
    BTREE *ret=NULL;
    if(m == NULL)
        return NULL;
    if(m->data==c)
        return m;
    else
    {
        ret =Getnode(m->lchild,c);
        if(ret!=NULL)
        {
            if(ret->data==c) //进入下一层递归前判断，若返回地址是要找的地址，则不用向下进行
            return ret;
        }
        ret =Getnode(m->rchild,c);
    }
    return ret;
}
/*先序递归遍历，寻找结点对应的数据*/
char Getdata(BTREE *r,BTREE *T)
{
    if(T == NULL)
        return ' ';
    if(T==r)
        return T->data;
    Getdata(r,T->lchild);
    Getdata(r,T->rchild);
}
/*递归寻找两个结点的公共祖先*/
BTREE *Commonancestor(BTREE *T,BTREE *p,BTREE *q)
{
    BTREE *left=T,*right=T;
    if(T==NULL||p==NULL||q==NULL)
        return NULL;
    if(p==T||q==T)
        return T;
    left=Commonancestor(T->lchild,p,q);
    right=Commonancestor(T->rchild,p,q);
    if(left!=NULL&&right!=NULL) //如果左右子树都能找到，那么当前的结点就是最近公共祖先
        return T;
    if(left==NULL)  //左子树没有，返回右子树查找结构
        return right;
    else   //否则返回左子树查找结果
        return left;
}

int main()
{
    BTREE *T,*p,*q,*r;
    char ch,a,b,c;
    int flag;
    printf("请以先序遍历的方式输入二叉树(空子树以'#'表示)：\n");
    CreateBT(&T);
    while(1)
    {
        getchar();
        ch = Menu();
        switch(ch)
        {
            case 1:Preorder(T);
            break;
            case 2:NPreorder(T);
            break;
            case 3:Inorder(T);
            break;
            case 4:NInorder(T);
            break;
            case 5:Postorder(T);
            break;
            case 6:NPostorder(T);
            break;
            case 7:Levelorder(T);
            break;
            case 8:flag = CompleteTree(T);
            if(flag)
                printf("该二叉树是完全二叉树！\n");
            else
                printf("该二叉树不是完全二叉树！\n");
            break;
            case 9:
            printf("请输入第一个结点的数据：\n");
            scanf(" %c",&a);
            printf("请输入第二个结点的数据：\n");
            scanf(" %c",&b);
            p=Getnode(T,a);   //找到数据对应的结点
            q=Getnode(T,b);
            r=Commonancestor(T,p,q);
            printf("最近公共祖先是：%c\n",r->data);
            break;
            case 10:exit(0);
            default:printf("请输入正确序号!\n");
        }
    }
    return 0;
}
