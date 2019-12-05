#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_LEN 2000
typedef struct celltype
{
    int data;
    struct celltype *lchild,*rchild;
}BSTNode;

typedef struct  //队列
{
    BSTNode *a[MAX_LEN]; //结构体数组，每个元素均为一个结点
    int front;
    int rear;
}Queue;

Queue *Createqueue() /*为队列分配空间*/
{
    Queue *p;
    p = (Queue *)malloc(sizeof(Queue));
    p->front = 0;
    p->rear = 0;
    return p;
}

BSTNode *Creatnode()  //生成新的结点
{
    BSTNode *p;
    p = (BSTNode*)malloc(sizeof(BSTNode));
    if(p==NULL)
    {
        printf("NO enough memory!\n");
        exit(0);
    }
    p->lchild = NULL;
    p->rchild = NULL;
    p->data = -1;
    return p;
}

void Insert_BST(BSTNode *F,int data) //非递归插入
{
    BSTNode *q;
    q = Creatnode();
    q->data = data;
    if(F->data==-1)
        F->data=data ;
    else
    {while(F!=NULL)
    {
        if(data<F->data)
        {
            if(F->lchild) F = F->lchild;
            else{
                F->lchild = q;
            return;
            }
        }
        else
        {
            if(F->rchild) F = F->rchild;
            else{
                F->rchild = q;
            return;
            }
        }
    }}
    return;
}

void Delete(BSTNode **F,int data) //直接修改指针，需要传入指针的地址
{
    BSTNode *p;
    if((*F)!=NULL)
        if(data<(*F)->data)
            Delete(&((*F)->lchild),data);
        else if(data>(*F)->data)
            Delete(&((*F)->rchild),data);
        else  //查找成功
        if((*F)->lchild==NULL)
                (*F) = (*F)->rchild;
        else if((*F)->rchild==NULL)
            (*F) = (*F)->lchild;
        else  //有两棵子树
            (*F)->data = Deletemin(&((*F)->rchild));
        /*用右子树中关键字最小的元素继承*/
}

int Deletemin(BSTNode **F) /*删除关键字最小的结点，并返回其中数据*/
{
    int temp;
    BSTNode *p;
    if((*F)->lchild==NULL)
    {
        p = *F;
        temp = (*F)->data;
        (*F) =(*F)->rchild;
        free(p);
        return temp;
    }
    else /*查找最左的结点*/
        return(Deletemin(&((*F)->lchild)));
}

void Readfile(BSTNode *F)  //从文件中读入待排序序列
{
    FILE *fp;
    int i,data;
    fp = fopen("BST.txt","rb");
    if(fp==NULL)
    {
        printf("读入文件BST.txt失败！\n");
        return -1;
    }
    for(i=0;i<15;i++)
    {
        fscanf(fp,"%d",&data);
        Insert_BST(F,data);
    }
    fclose(fp);
}

float Search(BSTNode *F,int data)  //迭代查找，方便找成功的ASL
{
    BSTNode *p;
    float counter=1;  //计数器
    p = F;
    while(p!=NULL&&p->data!=data)
    {
        if(data<p->data)
            p = p->lchild;
        else
            p = p->rchild;
        counter++;
    }
    if(p!=NULL)
        return counter;
    else
        return -1;
}

float SearchFail(BSTNode *T)  //层序遍历找失败的ASL
{
    Queue *p;
    float counter=0;
    int level=1,last;   //层数和每层最后一个结点
    p = Createqueue();  //创建一个队列
    if(T==NULL)
        return;
    p->rear++;   //二叉树非空，根指针入队
    p->a[p->rear]=T;
    last = p->rear;
    while(p->front !=p->rear)  //循环直到队列不为空
    {
        p->front++;
        T=p->a[p->front];
        if(T->lchild!=NULL) //若结点存在左孩子，将左孩子入队
        {
            p->rear++;
            p->a[p->rear]=T->lchild;
        }
        else
            counter+=level;
        if(T->rchild!=NULL) //若结点存在右孩子，将右孩子入队
        {
            p->rear++;
            p->a[p->rear]=T->rchild;
        }
        else
            counter+=level;
        if(p->front ==last)
        {
            last =p->rear;  //更新last
            level++;
        }
    }
    return counter;
}

void Inorder(BSTNode *F)  //中序遍历
{
    if(F==NULL)
        return;
    else
    {
        Inorder(F->lchild);
        printf("%d ",F->data);
        Inorder(F->rchild);
    }
}

int Menu()
{
    int x;
    printf("1.BST插入\n");
    printf("2.BST删除\n");
    printf("3.BST查找\n");
    printf("4.BST排序\n");
    printf("5.测试BST数据一\n");
    printf("6.测试BST数据二\n");
    printf("7.折半查找\n");
    printf("8.退出\n");
    printf("请选择你要执行的操作:\n");
    scanf("%d",&x);
    return x;
}

void CreatBinTree(BSTNode *T,int low,int up,int a[1024])
{
    int mid=0;
    if(low<up)
    {
        mid = (low+up)/2;
        Insert_BST(T,a[mid]);
        CreatBinTree(T,low,mid-1,a);
        CreatBinTree(T,mid+1,up,a);
    }
}

int main()
{
    BSTNode *F,*T1,*T2,*T3;
    int x,data,i,j,a[1024],temp;
    float counter=0;
    F = Creatnode();
    Readfile(F);
    printf("已从文件中读取待排序序列,并建立BST\n");
    while(1)
    {
        x = Menu();
        switch(x)
        {
            case 1:
                printf("请输入你要插入的元素:\n");
                scanf("%d",&data);
                Insert_BST(F,data);
                printf("元素已成功插入！\n\n");
                break;
            case 2:
                printf("请输入你要删除的元素:\n");
                scanf("%d",&data);
                Delete(&F,data);
                printf("元素已成功删除！\n\n");
                break;
            case 3:
                printf("请输入你要查找的元素:\n");
                scanf("%d",&data);
                counter=0;
                counter = Search(F,data);
                if(counter!=-1)
                    printf("查找成功！查找长度为=%f\n\n",counter);
                else
                    printf("查找失败！\n\n");
                break;
            case 4:
                printf("排序结果为：\n");
                Inorder(F);
                printf("\n\n");
                break;
            case 5:
                printf("测试BST数据一：\n");
                T1=Creatnode();
                counter=0;
                for(i=1;i<=2048;i=i+2)
                     Insert_BST(T1,i);
                for(i=1;i<=2048;i=i+2)
                    counter+=Search(T1,i);
                printf("查找成功 ASL=%f\n",counter/1024);
                counter = SearchFail(T1);
                printf("查找失败 ASL=%f\n\n",counter/1025);
                break;
            case 6:
                T2=Creatnode();
                printf("测试BST数据二:\n");
                counter=0;
                for(i=0;i<1024;i++)
                    a[i] = 2*i+1;
                for(i=0;i<1024;i++)
                {
                    j = (int)(sqrt(pow(i,3))+pow(i,2)+i*1999)%1024;  //求余后保证不和原位置相等
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;    //通过随机交换产生随机序列
                }
                for(i=0;i<1024;i++)
                     Insert_BST(T2,a[i]);
                for(i=0;i<1024;i++)
                    counter+=Search(T2,a[i]);
                printf("查找成功 ASL=%f\n",counter/1024);
                counter = SearchFail(T2);
                printf("查找失败 ASL=%f\n\n",counter/1025);
                break;
            case 7:
                T3=Creatnode();
                printf("折半查找测试:\n");
                counter=0;
                for(i=0;i<1024;i++)
                    a[i] = 2*i+1;
                CreatBinTree(T3,0,1023,a);
                for(i=0;i<1024;i++)
                    counter+=Search(T3,a[i]);
                printf("查找成功 ASL=%f\n",counter/1024); 
                counter = SearchFail(T3);
                printf("查找失败 ASL=%f\n\n",counter/1025);
                break;
            case 8:
                exit(0);
            default:
                printf("请输入正确序号！\n");
        }
    }
}
