#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_LEN 2000
typedef struct celltype
{
    int data;
    struct celltype *lchild,*rchild;
}BSTNode;

typedef struct  //����
{
    BSTNode *a[MAX_LEN]; //�ṹ�����飬ÿ��Ԫ�ؾ�Ϊһ�����
    int front;
    int rear;
}Queue;

Queue *Createqueue() /*Ϊ���з���ռ�*/
{
    Queue *p;
    p = (Queue *)malloc(sizeof(Queue));
    p->front = 0;
    p->rear = 0;
    return p;
}

BSTNode *Creatnode()  //�����µĽ��
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

void Insert_BST(BSTNode *F,int data) //�ǵݹ����
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

void Delete(BSTNode **F,int data) //ֱ���޸�ָ�룬��Ҫ����ָ��ĵ�ַ
{
    BSTNode *p;
    if((*F)!=NULL)
        if(data<(*F)->data)
            Delete(&((*F)->lchild),data);
        else if(data>(*F)->data)
            Delete(&((*F)->rchild),data);
        else  //���ҳɹ�
        if((*F)->lchild==NULL)
                (*F) = (*F)->rchild;
        else if((*F)->rchild==NULL)
            (*F) = (*F)->lchild;
        else  //����������
            (*F)->data = Deletemin(&((*F)->rchild));
        /*���������йؼ�����С��Ԫ�ؼ̳�*/
}

int Deletemin(BSTNode **F) /*ɾ���ؼ�����С�Ľ�㣬��������������*/
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
    else /*��������Ľ��*/
        return(Deletemin(&((*F)->lchild)));
}

void Readfile(BSTNode *F)  //���ļ��ж������������
{
    FILE *fp;
    int i,data;
    fp = fopen("BST.txt","rb");
    if(fp==NULL)
    {
        printf("�����ļ�BST.txtʧ�ܣ�\n");
        return -1;
    }
    for(i=0;i<15;i++)
    {
        fscanf(fp,"%d",&data);
        Insert_BST(F,data);
    }
    fclose(fp);
}

float Search(BSTNode *F,int data)  //�������ң������ҳɹ���ASL
{
    BSTNode *p;
    float counter=1;  //������
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

float SearchFail(BSTNode *T)  //���������ʧ�ܵ�ASL
{
    Queue *p;
    float counter=0;
    int level=1,last;   //������ÿ�����һ�����
    p = Createqueue();  //����һ������
    if(T==NULL)
        return;
    p->rear++;   //�������ǿգ���ָ�����
    p->a[p->rear]=T;
    last = p->rear;
    while(p->front !=p->rear)  //ѭ��ֱ�����в�Ϊ��
    {
        p->front++;
        T=p->a[p->front];
        if(T->lchild!=NULL) //�����������ӣ����������
        {
            p->rear++;
            p->a[p->rear]=T->lchild;
        }
        else
            counter+=level;
        if(T->rchild!=NULL) //���������Һ��ӣ����Һ������
        {
            p->rear++;
            p->a[p->rear]=T->rchild;
        }
        else
            counter+=level;
        if(p->front ==last)
        {
            last =p->rear;  //����last
            level++;
        }
    }
    return counter;
}

void Inorder(BSTNode *F)  //�������
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
    printf("1.BST����\n");
    printf("2.BSTɾ��\n");
    printf("3.BST����\n");
    printf("4.BST����\n");
    printf("5.����BST����һ\n");
    printf("6.����BST���ݶ�\n");
    printf("7.�۰����\n");
    printf("8.�˳�\n");
    printf("��ѡ����Ҫִ�еĲ���:\n");
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
    printf("�Ѵ��ļ��ж�ȡ����������,������BST\n");
    while(1)
    {
        x = Menu();
        switch(x)
        {
            case 1:
                printf("��������Ҫ�����Ԫ��:\n");
                scanf("%d",&data);
                Insert_BST(F,data);
                printf("Ԫ���ѳɹ����룡\n\n");
                break;
            case 2:
                printf("��������Ҫɾ����Ԫ��:\n");
                scanf("%d",&data);
                Delete(&F,data);
                printf("Ԫ���ѳɹ�ɾ����\n\n");
                break;
            case 3:
                printf("��������Ҫ���ҵ�Ԫ��:\n");
                scanf("%d",&data);
                counter=0;
                counter = Search(F,data);
                if(counter!=-1)
                    printf("���ҳɹ������ҳ���Ϊ=%f\n\n",counter);
                else
                    printf("����ʧ�ܣ�\n\n");
                break;
            case 4:
                printf("������Ϊ��\n");
                Inorder(F);
                printf("\n\n");
                break;
            case 5:
                printf("����BST����һ��\n");
                T1=Creatnode();
                counter=0;
                for(i=1;i<=2048;i=i+2)
                     Insert_BST(T1,i);
                for(i=1;i<=2048;i=i+2)
                    counter+=Search(T1,i);
                printf("���ҳɹ� ASL=%f\n",counter/1024);
                counter = SearchFail(T1);
                printf("����ʧ�� ASL=%f\n\n",counter/1025);
                break;
            case 6:
                T2=Creatnode();
                printf("����BST���ݶ�:\n");
                counter=0;
                for(i=0;i<1024;i++)
                    a[i] = 2*i+1;
                for(i=0;i<1024;i++)
                {
                    j = (int)(sqrt(pow(i,3))+pow(i,2)+i*1999)%1024;  //�����֤����ԭλ�����
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;    //ͨ��������������������
                }
                for(i=0;i<1024;i++)
                     Insert_BST(T2,a[i]);
                for(i=0;i<1024;i++)
                    counter+=Search(T2,a[i]);
                printf("���ҳɹ� ASL=%f\n",counter/1024);
                counter = SearchFail(T2);
                printf("����ʧ�� ASL=%f\n\n",counter/1025);
                break;
            case 7:
                T3=Creatnode();
                printf("�۰���Ҳ���:\n");
                counter=0;
                for(i=0;i<1024;i++)
                    a[i] = 2*i+1;
                CreatBinTree(T3,0,1023,a);
                for(i=0;i<1024;i++)
                    counter+=Search(T3,a[i]);
                printf("���ҳɹ� ASL=%f\n",counter/1024); 
                counter = SearchFail(T3);
                printf("����ʧ�� ASL=%f\n\n",counter/1025);
                break;
            case 8:
                exit(0);
            default:
                printf("��������ȷ��ţ�\n");
        }
    }
}
