#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 50
/*�������Ķ�������ṹ*/
typedef struct node
{
    struct node *lchild;
    struct node *rchild;
    char data;
}BTREE;
/*ջ������ʵ��*/
typedef struct
{
    int top;
    BTREE *a[MAX_LEN]; //�ṹ�����飬ÿ��Ԫ�ؾ�Ϊһ�����
}Stack;
/*���е�����ʵ��*/
typedef struct
{
    BTREE *a[MAX_LEN]; //�ṹ�����飬ÿ��Ԫ�ؾ�Ϊһ�����
    int front;
    int rear;
}Queue;
/*Ϊջ����ռ�*/
Stack *Createstack()
{
    Stack *p;
    p = (Stack *)malloc(sizeof(Stack));
    p->top = -1;
    return p;
}
/*Ϊ���з���ռ�*/
Queue *Createqueue()
{
    Queue *p;
    p = (Queue *)malloc(sizeof(Queue));
    p->front = 0;
    p->rear = 0;
    return p;
}
/*�˵�*/
int Menu()
{
    int x;
    printf("\n\n");
    printf("1.�������(�ݹ�)\n");
    printf("2.�������(�ǵݹ�)\n");
    printf("3.�������(�ݹ�)\n");
    printf("4.�������(�ǵݹ�)\n");
    printf("5.�������(�ݹ�)\n");
    printf("6.�������(�ǵݹ�)\n");
    printf("7.�������\n");
    printf("8.�ж����Ƿ�Ϊ��ȫ������\n");
    printf("9.��������������������Ĺ�������\n");
    printf("10.�˳�\n\n");
    printf("��ѡ����Ҫִ�еĲ�����\n");
    scanf("%d",&x);
    return x;
}
/*�����������������*/
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
            printf("No enough memory��\n");
            exit(0);
        }
        (*T)->data = ch;
        CreateBT(&((*T)->lchild));   //����������
        CreateBT(&((*T)->rchild));   //����������
    }
}
/*ѹջ*/
void Push(Stack *s,BTREE *p)
{
    s->top++;
    s->a[s->top] = p;
}
/*��ջ*/
BTREE *Pop(Stack *s)
{
    BTREE *p;
    if (s->top == -1)
    {
    printf("ջ�գ�\n");
    return NULL;
    }
    p = s->a[s->top];
    s->top--;
    return p;
}
/*ջ��*/
BTREE *Top(Stack *s)
{
    BTREE *p;
    if (s->top == -1)
    {
    printf("ջ�գ�\n");
    return NULL;
    }
    p = s->a[s->top];
    return p;
}
/*����������*/
void Printdata(char ch)
{
    printf("%c  ",ch);
}
/*��������������ݹ��㷨*/
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
/*��������������ĵݹ��㷨*/
void Inorder(BTREE *T)
{
    if(T != NULL)
    {
        Inorder(T->lchild);
        Printdata(T->data);
        Inorder(T->rchild);
    }
}
/*��������������ĵݹ��㷨*/
void Postorder(BTREE *T)
{
    if(T != NULL)
    {
        Postorder(T->lchild);
        Postorder(T->rchild);
        Printdata(T->data);
    }
}
/*��������������ķǵݹ��㷨,ջ�����浱ǰ����������*/
void NPreorder(BTREE *T)
{
     Stack *s;
     s = Createstack(); //����һ��ջ
     while(T!=NULL||s->top!=-1)
     {
         while(T!=NULL)   //ֱ������
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
/*��������������ķǵݹ��㷨*/
void NInorder(BTREE *T)
{
     Stack *s;
     s = Createstack(); //����һ��ջ
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
             Printdata(T->data); //���λ�ò�ͬ������������ǵݹ����һ��
             T=T->rchild;
         }
     }
}
/*��������ķǵݹ��㷨�������־����һ����*/
void NPostorder(BTREE *T)
{
    BTREE *p,*pr;
    Stack *s;
    s = Createstack(); //����һ��ջ
    p = T;
    while(p!=NULL||s->top!=-1)
    {
        while(p!=NULL)
        {
            Push(s,p);
            pr = p->rchild;
            p = p->lchild;
            if(p==NULL)    //ֱ����ײ㣬�����������һ��
            p = pr;
        }
        p = Pop(s);
        Printdata(p->data);
        if(s->top!=-1&&Top(s)->lchild==p)
            p=Top(s)->rchild;  //����������
        else
            p=NULL;
    }
}
/*�������������ʵ��*/
void Levelorder(BTREE *T)
{
    Queue *p;
    p = Createqueue();  //����һ������
    if(T==NULL)
        return;
    p->rear++;   //�������ǿգ���ָ�����
    p->a[p->rear]=T;
    while(p->front !=p->rear)  //ѭ��ֱ�����в�Ϊ��
    {
        p->front++;
        T=p->a[p->front];
        Printdata(T->data);
        if(T->lchild!=NULL) //�����������ӣ����������
        {
            p->rear++;
            p->a[p->rear]=T->lchild;
        }
        if(T->rchild!=NULL) //���������Һ��ӣ����Һ������
        {
            p->rear++;
            p->a[p->rear]=T->rchild;
        }
    }
}
/*�ж϶������Ƿ�Ϊ��ȫ�����������ò�������ķ�ʽ*/
int CompleteTree(BTREE *T)
{
    Queue *p;
    p = Createqueue(); //��������
    if(T==NULL)
        return 0;
    p->rear++; //�������ǿգ���ָ�����
    p->a[p->rear]=T;
    while(p->front !=p->rear)   //ѭ��ֱ�����в���
    {
        if(T->lchild!=NULL&&T->rchild!=NULL) //��������Һ��Ӷ���Ϊ�գ������ӣ����Һ��ӽ���
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
        if(T->lchild==NULL&&T->rchild!=NULL) //���ֻ��������û��������������
            return 0;
        if((T->lchild!=NULL&&T->rchild==NULL)||(T->lchild==NULL&&T->rchild==NULL))
            //���Ӳ����Һ��ӿգ��������Ҷ���,��ý��֮������н��ض���Ҷ�ӽ��
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
/*����ݹ������Ѱ�����ݶ�Ӧ�Ľ��*/
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
            if(ret->data==c) //������һ��ݹ�ǰ�жϣ������ص�ַ��Ҫ�ҵĵ�ַ���������½���
            return ret;
        }
        ret =Getnode(m->rchild,c);
    }
    return ret;
}
/*����ݹ������Ѱ�ҽ���Ӧ������*/
char Getdata(BTREE *r,BTREE *T)
{
    if(T == NULL)
        return ' ';
    if(T==r)
        return T->data;
    Getdata(r,T->lchild);
    Getdata(r,T->rchild);
}
/*�ݹ�Ѱ���������Ĺ�������*/
BTREE *Commonancestor(BTREE *T,BTREE *p,BTREE *q)
{
    BTREE *left=T,*right=T;
    if(T==NULL||p==NULL||q==NULL)
        return NULL;
    if(p==T||q==T)
        return T;
    left=Commonancestor(T->lchild,p,q);
    right=Commonancestor(T->rchild,p,q);
    if(left!=NULL&&right!=NULL) //����������������ҵ�����ô��ǰ�Ľ����������������
        return T;
    if(left==NULL)  //������û�У��������������ҽṹ
        return right;
    else   //���򷵻����������ҽ��
        return left;
}

int main()
{
    BTREE *T,*p,*q,*r;
    char ch,a,b,c;
    int flag;
    printf("������������ķ�ʽ���������(��������'#'��ʾ)��\n");
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
                printf("�ö���������ȫ��������\n");
            else
                printf("�ö�����������ȫ��������\n");
            break;
            case 9:
            printf("�������һ���������ݣ�\n");
            scanf(" %c",&a);
            printf("������ڶ����������ݣ�\n");
            scanf(" %c",&b);
            p=Getnode(T,a);   //�ҵ����ݶ�Ӧ�Ľ��
            q=Getnode(T,b);
            r=Commonancestor(T,p,q);
            printf("������������ǣ�%c\n",r->data);
            break;
            case 10:exit(0);
            default:printf("��������ȷ���!\n");
        }
    }
    return 0;
}
