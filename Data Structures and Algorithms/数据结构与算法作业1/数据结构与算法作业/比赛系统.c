#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 15
#define RESULT_LEN 5
typedef struct college
{
    char name[MAX_LEN];
    int num;
    int score;
    int man;
    int woman;
}CLO;
typedef struct project
{
    int num2;
    char name2[MAX_LEN];
    int rank[RESULT_LEN];
    int order;
}PRO;
int Menu()
{
    int x;
    printf("�˶���ɼ�����ϵͳ��\n");
    printf("ѡ������Ҫ�Ĳ���(ѡ�����):\n");
    printf("1.��ѧԺ����������\n");
    printf("2.��ѧԺ�ܷ��������\n");
    printf("3.��ѧԺ�����ܷ��������\n");
    printf("4.��ѧԺŮ���ܷ��������\n");
    printf("5.��ѯĳ��ѧԺ�ɼ�\n");
    printf("6.��ѯĳ����Ŀ�ɼ�\n");
    printf("7.����\n\n");
    printf("�������������ѡ��һ�");
    scanf("%d",&x);
    return x;
}
void Readcollege(CLO clo[],int n)
{
    int i;
    printf("������ѧԺ�ı�ź����ƣ�\n");
    for(i=0;i<n;i++)
    {
        while(1)
        {
            scanf("%d %s",&clo[i].num,clo[i].name);
            if(clo[i].num>=1&&clo[i].num<=n)
                break;
            else
                printf("�����������������룺\n");
        }
    }
}
void Readproject(PRO pro[],int m,int w,int n)
{
    int i,j;
    int flag=0;
    for(i=0;i<m+w;i++)
    {
        printf("������ĳ��Ŀ�ı�š������Լ�������������(ǰ������ǰ����)\n");
        while(1)
       {
        scanf("%d %s %d",&pro[i].num2,pro[i].name2,&pro[i].order);
        if((pro[i].num2>=1&&pro[i].num2<=m+w)&&(pro[i].order==3||pro[i].order==5))
            break;
        else
            printf("�����������������룺\n");
       }
        if(pro[i].order==3)
        {
            printf("���������Ŀǰ����ѧԺ���:\n");
            while(1)
            {
                flag=0;
                for(j=0;j<3;j++)
                {
                    scanf("%d",&pro[i].rank[j]);
                    if(pro[i].rank[j]<1||pro[i].rank[j]>n)
                        flag=1;
                }
                if(flag)
                    printf("�����������������룺\n");
                else
                    break;
            }
        }
        if(pro[i].order==5)
        {
            printf("���������Ŀǰ����ѧԺ���:\n");
            while(1)
           {
                flag=0;
                for(j=0;j<5;j++)
                {
                    scanf("%d",&pro[i].rank[j]);
                    if(pro[i].rank[j]<1||pro[i].rank[j]>n)
                        flag=1;
                }
                if(flag)
                    printf("�����������������룺\n");
                else
                    break;
            }
        }
    }
}
void Readscore(CLO clo[],PRO pro[],int n,int m,int w)
{
    int i,j;
    for(i=0;i<m+w;i++)
    {
        if(pro[i].order==3)
        {
            for(j=0;j<n;j++)
            {
                if(clo[j].num==pro[i].rank[0])
                {
                    clo[j].score+=5;
                    if(i+1<=m)
                    clo[j].man+=5;
                    else
                    clo[j].woman+=5;
                }
                if(clo[j].num==pro[i].rank[1])
                {
                    clo[j].score+=3;
                    if(i+1<=m)
                    clo[j].man+=3;
                    else
                    clo[j].woman+=3;
                }
                if(clo[j].num==pro[i].rank[2])
                {
                    clo[j].score+=2;
                    if(i+1<=m)
                    clo[j].man+=2;
                    else
                    clo[j].woman+=2;
                }
            }
        }
        if(pro[i].order==5)
        {
            for(j=0;j<n;j++)
            {
                if(clo[j].num==pro[i].rank[0])
                {
                    clo[j].score+=7;
                    if(i+1<=m)
                    clo[j].man+=7;
                    else
                    clo[j].woman+=7;
                }
                if(clo[j].num==pro[i].rank[1])
                {
                    clo[j].score+=5;
                    if(i+1<=m)
                    clo[j].man+=5;
                    else
                    clo[j].woman+=5;
                }
                if(clo[j].num==pro[i].rank[2])
                {
                    clo[j].score+=3;
                    if(i+1<=m)
                    clo[j].man+=3;
                    else
                    clo[j].woman+=3;
                }
                if(clo[j].num==pro[i].rank[3])
                {
                    clo[j].score+=2;
                    if(i+1<=m)
                    clo[j].man+=2;
                    else
                    clo[j].woman+=2;
                }
                if(clo[j].num==pro[i].rank[4])
                {
                    clo[j].score+=1;
                    if(i+1<=m)
                    clo[j].man+=1;
                    else
                    clo[j].woman+=1;
                }
            }
        }
    }
}
void Sortbynumber(CLO clo[],int n)
{
    int i,j,k;
    for(i=0;i<n-1;i++)
    {
        k=i;
        for(j=i+1;j<n;j++)
        {
            if(clo[j].num<clo[k].num)
                k=j;
        }
        if(k!=i)
        {
            Swapchar(clo[k].name,clo[i].name);
            Swapint(&clo[k].score,&clo[i].score);
            Swapint(&clo[k].man,&clo[i].man);
            Swapint(&clo[k].woman,&clo[i].woman);
            Swapint(&clo[k].num,&clo[i].num);
        }
    }
    for(i=0;i<n;i++)
    {
        printf("ѧԺ%d %s �ܷ�%d ����%d Ů��%d\n",clo[i].num,clo[i].name,clo[i].score,clo[i].man,clo[i].woman);
    }
}
void Sortbyscore(CLO clo[],int n)
{
   int i,j,k;
    for(i=0;i<n-1;i++)
    {
        k=i;
        for(j=i+1;j<n;j++)
        {
            if(clo[j].score>clo[k].score)
                k=j;
        }
        if(k!=i)
        {
            Swapchar(clo[k].name,clo[i].name);
            Swapint(&clo[k].score,&clo[i].score);
            Swapint(&clo[k].man,&clo[i].man);
            Swapint(&clo[k].woman,&clo[i].woman);
            Swapint(&clo[k].num,&clo[i].num);
        }
    }
    for(i=0;i<n;i++)
    {
        printf("ѧԺ%d %s �ܷ�%d ����%d Ů��%d\n",clo[i].num,clo[i].name,clo[i].score,clo[i].man,clo[i].woman);
    }
    printf("\n\n");
}
void Sortbyman(CLO clo[],int n)
{
   int i,j,k;
    for(i=0;i<n-1;i++)
    {
        k=i;
        for(j=i+1;j<n;j++)
        {
            if(clo[j].man>clo[k].man)
                k=j;
        }
        if(k!=i)
        {
            Swapchar(clo[k].name,clo[i].name);
            Swapint(&clo[k].score,&clo[i].score);
            Swapint(&clo[k].man,&clo[i].man);
            Swapint(&clo[k].woman,&clo[i].woman);
            Swapint(&clo[k].num,&clo[i].num);
        }
    }
    for(i=0;i<n;i++)
    {
        printf("ѧԺ%d %s �ܷ�%d ����%d Ů��%d\n",clo[i].num,clo[i].name,clo[i].score,clo[i].man,clo[i].woman);
    }
    printf("\n\n");
}
void Sortbywoman(CLO clo[],int n)
{
   int i,j,k;
    for(i=0;i<n-1;i++)
    {
        k=i;
        for(j=i+1;j<n;j++)
        {
            if(clo[j].woman>clo[k].woman)
                k=j;
        }
        if(k!=i)
        {
            Swapchar(clo[k].name,clo[i].name);
            Swapint(&clo[k].score,&clo[i].score);
            Swapint(&clo[k].man,&clo[i].man);
            Swapint(&clo[k].woman,&clo[i].woman);
            Swapint(&clo[k].num,&clo[i].num);
        }
    }
    for(i=0;i<n;i++)
    {
        printf("ѧԺ%d %s �ܷ�%d ����%d Ů��%d\n",clo[i].num,clo[i].name,clo[i].score,clo[i].man,clo[i].woman);
    }
    printf("\n\n");
}
void Sortbyname(CLO clo[],int n)
{
    int i,j,k;
    for(i=0;i<n-1;i++)
    {
        k=i;
        for(j=i+1;j<n;j++)
        {
            if(strcmp(clo[j].name,clo[k].name)<0)
                k=j;
        }
        if(k!=i)
        {
            Swapchar(clo[k].name,clo[i].name);
            Swapint(&clo[k].score,&clo[i].score);
            Swapint(&clo[k].man,&clo[i].man);
            Swapint(&clo[k].woman,&clo[i].woman);
            Swapint(&clo[k].num,&clo[i].num);
        }
    }
    for(i=0;i<n;i++)
    {
        printf("ѧԺ%d %s �ܷ�%d ����%d Ů��%d\n",clo[i].num,clo[i].name,clo[i].score,clo[i].man,clo[i].woman);
    }
    printf("\n\n");
}
void Swapchar(char x[],char y[])
{
    char temp[MAX_LEN];
    strcpy(temp,x);
    strcpy(x,y);
    strcpy(y,temp);
}
void Swapint(int *x,int *y)
{
    long temp;
    temp=*x;
    *x=*y;
    *y=temp;
}
void Searchbycollege(CLO clo[],PRO pro[],int n,int m,int w)
{
    int x,y,i,j,k;
    printf("���������ѯ��ѧԺ��ţ�");
    while(1)
    {
        scanf("%d",&x);
        if(x>=1&&x<=n)
            break;
        else
            printf("�����������������룺");
    }
    printf("���������ѯ����Ŀ��ţ�");
    while(1)
    {
        scanf("%d",&y);
        if(y>=1&&y<=m+w)
            break;
        else
            printf("�����������������룺");
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m+w;j++)
            {
                if((clo[i].num==x)&&(pro[j].num2==y))
                    {
                        printf("ѧԺ%d  %s  ��Ŀ%d  %s\n",clo[i].num,clo[i].name,pro[j].num2,pro[j].name2);
                        for(k=0;k<pro[j].order;k++)
                        {
                            if(pro[j].rank[k]==clo[i].num)
                                printf("��õ�%d��\n\n",k+1);
                        }
                    }
            }
    }
}
void Searchbyproject(PRO pro[],int m,int w)
{
    int x,i,j;
    printf("���������ѯ����Ŀ��ţ�");
    while(1)
    {
        scanf("%d",&x);
        if(x>=1&&x<=m+w)
            break;
        else
            printf("�����������������룺");
    }
    for(i=0;i<m+w;i++)
    {
        if(pro[i].num2==x)
            {
                printf("��Ŀ%d  %s  ǰ%d��ѧԺ���Ϊ :",pro[i].num2,pro[i].name2,pro[i].order);
                for(j=0;j<pro[i].order;j++)
                {
                    printf("%d ",pro[i].rank[j]);
                }
                printf("\n\n");
            }
    }
}
int Storage(CLO clo[],PRO pro[],int n,int m,int w)
{
    FILE *fp;
    int i,j;
    fp=fopen("d:\\test.txt","w");
    if(fp==NULL)
        {
            printf("create file failed\n");
            return -1;
        }
    else
        {
            for(i=0;i<n;i++)
            {
                fprintf(fp,"ѧԺ%d %s �ܷ�%d ����%d Ů��%d\n",clo[i].num,clo[i].name,clo[i].score,clo[i].man,clo[i].woman);
            }
            for(i=0;i<m+w;i++)
            {
                fprintf(fp,"��Ŀ%d  %s  ǰ%d��ѧԺ���Ϊ ",pro[i].num2,pro[i].name2,pro[i].order);
                 for(j=0;j<pro[i].order;j++)
                {
                    fprintf(fp,"%d ",pro[i].rank[j]);
                }
                fprintf(fp,"\n");
            }
        }
    fclose(fp);
    return 0;
}
int main()
{
    char ch;
    int n,m,w,i;
    printf("������ѧԺ����(С��20)��\n");
    while(1)
    {
        scanf("%d",&n);
        if(n>=1&&n<20)
            break;
        else
            printf("������������������:\n");
    }
    printf("������������Ŀ����(С��20)��\n");
    while(1)
    {
        scanf("%d",&m);
        if(m>=1&&m<20)
            break;
        else
            printf("�����������������룺\n");
    }
    printf("������Ů����Ŀ����(С��20)��\n");
    while(1)
    {
        scanf("%d",&w);
        if(w>=1&&w<20)
            break;
        else
            printf("�����������������룺\n");
    }
    CLO clo[n];
    PRO pro[m+w];
    for(i=0;i<n;i++)
    {
        clo[i].man=0;
        clo[i].num=0;
        clo[i].score=0;
        clo[i].woman=0;
    }
    Readcollege(clo,n);
    Readproject(pro,m,w,n);
    Readscore(clo,pro,n,m,w);
    Storage(clo,pro,n,m,w);
    while(1)
    {
        ch = Menu();
        switch(ch)
        {
            case 1:Sortbynumber(clo,n);
            break;
            case 2:Sortbyscore(clo,n);
            break;
            case 3:Sortbyman(clo,n);
            break;
            case 4:Sortbywoman(clo,n);
            break;
            case 5:Searchbycollege(clo,pro,n,m,w);
            break;
            case 6:Searchbyproject(pro,m,w);
            break;
            case 7:printf("���������");
                        exit(0);
            default:printf("��������ȷ����!\n");
        }
    }
    return 0;
}
