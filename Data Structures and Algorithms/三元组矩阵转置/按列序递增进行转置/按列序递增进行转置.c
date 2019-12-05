#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 100
/*按列序递增进行转置的思想就是：对于原矩阵的某一列一次扫描，按行序从大到小存到三元组，
这样可以实现，在新的矩阵中，行序递增（原矩阵列序），且某一行的列序递增。*/
typedef struct
{
    int r,c,value;
}Tri;
typedef struct
{
    Tri data[MAX_LEN+1]; /*结构体数组，三元组，数组中的每个元素有其行号、列号和值*/
    int row,col,number;
}Tsmatrix;
void Create_Matrix(Tsmatrix *S)
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
int Transpose (Tsmatrix *A, Tsmatrix *B)
{
	int i, j, k;
	B->row= A->col;
	B->col = A->row;
	B->number = A->number;
	if (B->number >0)
	{
		k = 1;
		for (i = 1; i <= A->col; i++) // A的列数就是B的行数，对应要循环找几次B的行号
		{
			for (j = 1; j <= A->number; j++)
			{
				if (A->data[j].c == i) // 每次将列号为i的元素赋给B
				{
					B->data[k].r = A->data[j].c;
					B->data[k].c = A->data[j].r;
					B->data[k].value = A->data[j].value;
					k++;
				}
				if (k > A->number)
					break;
			}
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
