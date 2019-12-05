#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 100
/*�������������ת�õ�˼����ǣ�����ԭ�����ĳһ��һ��ɨ�裬������Ӵ�С�浽��Ԫ�飬
��������ʵ�֣����µľ����У����������ԭ�������򣩣���ĳһ�е����������*/
typedef struct
{
    int r,c,value;
}Tri;
typedef struct
{
    Tri data[MAX_LEN+1]; /*�ṹ�����飬��Ԫ�飬�����е�ÿ��Ԫ�������кš��кź�ֵ*/
    int row,col,number;
}Tsmatrix;
void Create_Matrix(Tsmatrix *S)
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
int Transpose (Tsmatrix *A, Tsmatrix *B)
{
	int i, j, k;
	B->row= A->col;
	B->col = A->row;
	B->number = A->number;
	if (B->number >0)
	{
		k = 1;
		for (i = 1; i <= A->col; i++) // A����������B����������ӦҪѭ���Ҽ���B���к�
		{
			for (j = 1; j <= A->number; j++)
			{
				if (A->data[j].c == i) // ÿ�ν��к�Ϊi��Ԫ�ظ���B
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
