#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int begin[100], end[100],father[100],bridgenum,islandnum;
double bridge[5000];
void Sort()  //对桥的长度进行升序排序
{
    int i,j;
    double temp;
    for(i=0;i<bridgenum;i++)
        for(j=i+1;j<bridgenum;j++)
    {
        if(bridge[j]<bridge[i])
        {
            temp = bridge[j];
            bridge[j] = bridge[i];
            bridge[i] =temp;
        }
    }
}
double Kruskal(void)
{
    int i;
    double path=0;
    for(int i=0; i<=islandnum;i++)
    {
        father[i] = i;
    }
    Sort();
    for(i = 0; i < bridgenum; i++)
    {
        int x = find(begin[i]);
        int y = find(end[i]);
        if(x != y)
        {
            path += bridge[i];
            father[x] = y;
        }
    }
    return path;
}

int find(int n)  //找祖先
{
    if(n != father[n])
        father[n] = find(father[n]);
    return father[n];
}

int main()
{
    FILE *fp;
    int visit[100],x[100],y[100];  //是否访问，横纵坐标
    int sample,i,j,flag=0;
    double distance;  //距离
    fp=fopen("island.txt","r");
    if(fp==NULL)
    {
        printf("读取文件island.txt失败！\n");
        exit(0);
    }
    printf("样例已从文件中读入！\n");
    fscanf(fp," %d",&sample);
    printf("样例个数：%d\n\n",sample);
    while(sample--)
    {
        bridgenum=0;
        memset(visit,0,sizeof(visit));
        fscanf(fp," %d",&islandnum);
        printf("岛的数量：%d\n",islandnum);
        for(i=0;i<islandnum;i++)
        {
            fscanf(fp," %d %d", &x[i], &y[i]);
            printf("岛的坐标(%d,%d)\n",x[i],y[i]);
        }
        for(i=0;i<islandnum-1;i++)
            for(j=i+1;j<islandnum;j++)
            {
                distance = sqrt((x[j]-x[i])*(x[j]-x[i])+(y[j]-y[i])*(y[j]-y[i]));
                if(distance>=10&&distance<=1000)
                {
                    begin[bridgenum] = i;
                    end[bridgenum] = j;
                    bridge[bridgenum] =distance;
                    visit[i] = 1;
                    visit[j] = 1;
                    bridgenum++;
                }
            }
        for(i = 0; i < islandnum; i++)
        {
            if(visit[i] == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag)
            printf("no.\n\n");
        else
            printf("建桥最小花费：%lf 元\n\n",Kruskal()*100);
    }
}
