#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 100
/*快速转置的思想就是先确定原矩阵每列（转置后矩阵的每行）有几个元素，也就确定了各个元素
放置的位置，因此扫描一遍即可把它们全部填入*/
typedef struct
{
    int r,c,value;
}Tri;
typedef struct
{
    Tri data[MAX_LEN+1]; /*结构体数组*/
    int row,col,number;
}Tsmatrix;
void Create_Matrix(Tsmatrix *S)  //输入原矩阵
{
    int i=0;
    printf("请输入原矩阵的行数、列数：\n");
    scanf("%d %d",&S->row,&S->col);
    printf("请输入原矩阵的元素个数：\n");
    scanf("%d",&S->number);
    printf("请输入原矩阵各元素的行号、列号和值为：\n");
    for(i=1;i<=S->number;i++)
    {
        scanf("%d %d %d",&S->data[i].r,&S->data[i].c,&S->data[i].value);
    }
}
int Transpose(Tsmatrix *S,Tsmatrix *P)
{
    int i=0,j = 0,col=0;
    int num[MAX_LEN+1]={0},cpot[MAX_LEN+1];
    /*num[col]:存储原矩阵第i列非零元素的个数
       cpot[col]:存储原矩阵第i列第一个非零三元组在新矩阵中的位置*/
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
void Printresult(Tsmatrix *P , int a) //打印结果
{
    int i = 0;
    if(a = 0)
        printf("原矩阵不存在非零元素！！！\n");
    else {
        printf("转置后的矩阵的行数和列数分别为：\n");
        printf("%d %d\n",P->row,P->col);
        printf("转置后的矩阵的元素个数为：\n");
        printf("%d\n",P->number);
        printf("转置后的矩阵各元素的行号、列号和值为：\n");
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
