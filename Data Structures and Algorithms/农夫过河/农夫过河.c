#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 30

typedef struct   //顶点
{
    int farmer;
	int wolf;
	int sheep;
	int vegetable;
}Vertexdata;

int visited[MAX_LEN] = {0};  //设置访问状态
int path[MAX_LEN] = {0};  //保存DFS搜索到的路径，数组元素的值为数组编号的下一状态

typedef struct  //邻接矩阵
{
    Vertexdata verlist[MAX_LEN];
    int edges[MAX_LEN][MAX_LEN];
	int vertexnum;//顶点个数
}MTGraph;

void Creategraph(MTGraph *G)  //生成所有安全的图的顶点
{
    int i=0,j=0,f,w,s,v;
    for(f=0;f<=1;f++)
    {
        for(w=0;w<=1;w++)
        {
            for(s=0;s<=1;s++)
            {
                for(v=0;v<=1;v++)
                {
                    if(Safe(f,w,s,v))
                    {
                        G->verlist[i].farmer=f;
                        G->verlist[i].wolf=w;
                        G->verlist[i].sheep=s;
                        G->verlist[i].vegetable=v;
                        i++;
                    }
                }
            }
        }
    }

    G->vertexnum = i ;   //安全的顶点个数
    for(i=0;i<G->vertexnum;i++)
    {
        for(j=0;j<G->vertexnum;j++)
        {
            if(Cancross(G,i,j))
            {
                G->edges[i][j]=1;   //无向图
                G->edges[j][i]=1;
            }
            else
            {
                G->edges[i][j]=0;
                G->edges[j][i]=0;
            }
        }
    }
}

int Safe(int f,int w,int s,int v) //判断某状态是否安全
{
    if((f!=s)&&(s==w||s==v))   //当农夫不和羊在一起，并且羊和狼或菜在一起
        return 0;
    else
        return 1;
}

int Cancross(MTGraph *G, int i, int j)  //判断两种状态是否可切换
{
    int flag=0;
    if(G->verlist[i].wolf!=G->verlist[j].wolf)
        flag ++;
    if(G->verlist[i].sheep!=G->verlist[j].sheep)
        flag ++;
    if(G->verlist[i].vegetable!=G->verlist[j].vegetable)
        flag ++;
    if(G->verlist[i].farmer!=G->verlist[j].farmer&&flag<=1)
        return 1;
    else
        return 0;
}

int Location(MTGraph *G,int f,int w,int s,int v) //查找某顶点在顶点表中的位置
{
    int i;
    for(i=0;i<G->vertexnum;i++)
    {
        if(G->verlist[i].farmer== f&&G->verlist[i].sheep==s \
           &&G->verlist[i].vegetable ==v &&G->verlist[i].wolf==w)
            return i;
    }
    return -1;
}

void DFS(MTGraph *G, int start ,int end)  //深度优先搜索
{
    int m=0;
    visited[start]=1;
    for(m=0;m<G->vertexnum;m++)
    {
        if(G->edges[start][m] && !visited[m] && !visited[end]) //如果二者可转换且另一个顶点未被访问过,直到终点
        {
            path[start]=m;  //此时m为start的下一种状态
            DFS(G,m,end);
        }
    }
}

void Printpath(MTGraph G,int start,int end)  //打印路径
{
    int p=start;
    while(p!=end)
    {
        printf("过河情况：农夫%d 狼%d 羊%d 菜%d\n",G.verlist[p].farmer,G.verlist[p].wolf,\
               G.verlist[p].sheep,G.verlist[p].vegetable);
        p = path[p];
    }
    printf("过河情况：农夫%d 狼%d 羊%d 菜%d\n",G.verlist[p].farmer,G.verlist[p].wolf,\
               G.verlist[p].sheep,G.verlist[p].vegetable);
}

int main()
{
    int start,end;
    MTGraph G;
    Creategraph(&G);
    start = Location(&G,0,0,0,0); //起始状态
    end = Location(&G,1,1,1,1); //终点状态
    printf("农夫过河问题详细步骤：(0表示在河彼岸，1表示在河对岸)\n");
    DFS(&G,start,end);
    if(visited[end])
        Printpath(G,start,end);
    return 0;
}
