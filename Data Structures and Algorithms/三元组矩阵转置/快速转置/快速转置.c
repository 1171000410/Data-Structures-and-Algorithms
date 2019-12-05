#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 100
/*����ת�õ�˼�������ȷ��ԭ����ÿ�У�ת�ú�����ÿ�У��м���Ԫ�أ�Ҳ��ȷ���˸���Ԫ��
���õ�λ�ã����ɨ��һ�鼴�ɰ�����ȫ������*/
typedef struct
{
    int r,c,value;
}Tri;
typedef struct
{
    Tri data[MAX_LEN+1]; /*�ṹ������*/
    int row,col,number;
}Tsmatrix;
void Create_Matrix(Tsmatrix *S)  //����ԭ����
{
    int i=0;
    printf("������ԭ�����������������\n");
    scanf("%d %d",&S->row,&S->col);
    printf("������ԭ�����Ԫ�ظ�����\n");
    scanf("%d",&S->number);
    printf("������ԭ�����Ԫ�ص��кš��кź�ֵΪ��\n");
    for(i=1;i<=S->number;i++)
    {
        scanf("%d %d %d",&S->data[i].r,&S->data[i].c,&S->data[i].value);
    }
}
int Transpose(Tsmatrix *S,Tsmatrix *P)
{
    int i=0,j = 0,col=0;
    int num[MAX_LEN+1]={0},cpot[MAX_LEN+1];
    /*num[col]:�洢ԭ�����i�з���Ԫ�صĸ���
       cpot[col]:�洢ԭ�����i�е�һ��������Ԫ�����¾����е�λ��*/
    P->row=S->col;
    P->col=S->row;
    P->number=S->number;
    if(P->number>0)
    {
        for(col=1;col<=S->col;col++)
        {
            num[col]=0;
            cpot[col]=0;
        }
        for(i=1;i<=S->number;i++)
        {
            num[S->data[i].c]++;
        }
        cpot[1]=1;
        for(col=2;col<=S->col;col++)
        {
            cpot[col]=num[col-1]+cpot[col-1];
        }
        for(i=1;i<=S->number;i++)
        {
            col=S->data[i].c;
            j=cpot[col];
            P->data[j].c=S->data[i].r;
            P->data[j].r=S->data[i].c;
            P->data[j].value=S->data[i].value;
            cpot[col]++;
        }
        return 1;
    }
    else
        return 0;
}
void Printresult(Tsmatrix *P , int a) //��ӡ���
{
    int i = 0;
    if(a = 0)
        printf("ԭ���󲻴��ڷ���Ԫ�أ�����\n");
    else {
        printf("ת�ú�ľ���������������ֱ�Ϊ��\n");
        printf("%d %d\n",P->row,P->col);
        printf("ת�ú�ľ����Ԫ�ظ���Ϊ��\n");
        printf("%d\n",P->number);
        printf("ת�ú�ľ����Ԫ�ص��кš��кź�ֵΪ��\n");
        for(i=1;i<=P->number;i++)
        {
            printf("%d %d %d\n",P->data[i].r,P->data[i].c,P->data[i].value);
        }
    }
}
int main()
{
    int flag=0;
    Tsmatrix S,P;
    Create_Matrix(&S);
    flag=Transpose(&S,&P);
    Printresult(&P,flag);
    return 0;
}
