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
    printf("运动会成绩管理系统：\n");
    printf("选择您需要的操作(选择序号):\n");
    printf("1.按学院编号排序输出\n");
    printf("2.按学院总分排序输出\n");
    printf("3.按学院男生总分排序输出\n");
    printf("4.按学院女生总分排序输出\n");
    printf("5.查询某个学院成绩\n");
    printf("6.查询某个项目成绩\n");
    printf("7.结束\n\n");
    printf("请在上述序号中选择一项：");
    scanf("%d",&x);
    return x;
}
void Readcollege(CLO clo[],int n)
{
    int i;
    printf("请输入学院的编号和名称：\n");
    for(i=0;i<n;i++)
    {
        while(1)
        {
            scanf("%d %s",&clo[i].num,clo[i].name);
            if(clo[i].num>=1&&clo[i].num<=n)
                break;
            else
                printf("数据有误，请重新输入：\n");
        }
    }
}
void Readproject(PRO pro[],int m,int w,int n)
{
    int i,j;
    int flag=0;
    for(i=0;i<m+w;i++)
    {
        printf("请输入某项目的编号、名称以及积分名次依据(前三名或前五名)\n");
        while(1)
       {
        scanf("%d %s %d",&pro[i].num2,pro[i].name2,&pro[i].order);
        if((pro[i].num2>=1&&pro[i].num2<=m+w)&&(pro[i].order==3||pro[i].order==5))
            break;
        else
            printf("数据有误，请重新输入：\n");
       }
        if(pro[i].order==3)
        {
            printf("请输入该项目前三名学院编号:\n");
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
                    printf("数据有误，请重新输入：\n");
                else
                    break;
            }
        }
        if(pro[i].order==5)
        {
            printf("请输入该项目前五名学院编号:\n");
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
                    printf("数据有误，请重新输入：\n");
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
        printf("学院%d %s 总分%d 男生%d 女生%d\n",clo[i].num,clo[i].name,clo[i].score,clo[i].man,clo[i].woman);
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
        printf("学院%d %s 总分%d 男生%d 女生%d\n",clo[i].num,clo[i].name,clo[i].score,clo[i].man,clo[i].woman);
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
        printf("学院%d %s 总分%d 男生%d 女生%d\n",clo[i].num,clo[i].name,clo[i].score,clo[i].man,clo[i].woman);
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
        printf("学院%d %s 总分%d 男生%d 女生%d\n",clo[i].num,clo[i].name,clo[i].score,clo[i].man,clo[i].woman);
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
        printf("学院%d %s 总分%d 男生%d 女生%d\n",clo[i].num,clo[i].name,clo[i].score,clo[i].man,clo[i].woman);
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
    printf("输入你想查询的学院编号：");
    while(1)
    {
        scanf("%d",&x);
        if(x>=1&&x<=n)
            break;
        else
            printf("数据有误，请重新输入：");
    }
    printf("输入你想查询的项目编号：");
    while(1)
    {
        scanf("%d",&y);
        if(y>=1&&y<=m+w)
            break;
        else
            printf("数据有误，请重新输入：");
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m+w;j++)
            {
                if((clo[i].num==x)&&(pro[j].num2==y))
                    {
                        printf("学院%d  %s  项目%d  %s\n",clo[i].num,clo[i].name,pro[j].num2,pro[j].name2);
                        for(k=0;k<pro[j].order;k++)
                        {
                            if(pro[j].rank[k]==clo[i].num)
                                printf("获得第%d名\n\n",k+1);
                        }
                    }
            }
    }
}
void Searchbyproject(PRO pro[],int m,int w)
{
    int x,i,j;
    printf("输入你想查询的项目编号：");
    while(1)
    {
        scanf("%d",&x);
        if(x>=1&&x<=m+w)
            break;
        else
            printf("数据有误，请重新输入：");
    }
    for(i=0;i<m+w;i++)
    {
        if(pro[i].num2==x)
            {
                printf("项目%d  %s  前%d名学院编号为 :",pro[i].num2,pro[i].name2,pro[i].order);
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
                fprintf(fp,"学院%d %s 总分%d 男生%d 女生%d\n",clo[i].num,clo[i].name,clo[i].score,clo[i].man,clo[i].woman);
            }
            for(i=0;i<m+w;i++)
            {
                fprintf(fp,"项目%d  %s  前%d名学院编号为 ",pro[i].num2,pro[i].name2,pro[i].order);
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
    printf("请输入学院总数(小于20)：\n");
    while(1)
    {
        scanf("%d",&n);
        if(n>=1&&n<20)
            break;
        else
            printf("数据有误，请重新输入:\n");
    }
    printf("请输入男生项目个数(小于20)：\n");
    while(1)
    {
        scanf("%d",&m);
        if(m>=1&&m<20)
            break;
        else
            printf("数据有误，请重新输入：\n");
    }
    printf("请输入女生项目个数(小于20)：\n");
    while(1)
    {
        scanf("%d",&w);
        if(w>=1&&w<20)
            break;
        else
            printf("数据有误，请重新输入：\n");
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
            case 7:printf("程序结束！");
                        exit(0);
            default:printf("请输入正确数据!\n");
        }
    }
    return 0;
}
