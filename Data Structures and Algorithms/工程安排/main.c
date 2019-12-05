#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 30
typedef struct node  //边表结点
{
    int adjvex;   //下标
    int weight;  //权值
    char letter;  //项目序号
    struct node *next;
}EdgeNode;
typedef struct   //顶点表结点
{
    int vertexdata; //顶点数据域
    int in;   //顶点入度
    EdgeNode * firstedge;//边链表头指针
}VertexNode;

void CreatGraph(FILE *fp,VertexNode *G,int vertexnum,int edgenum)  //生成图的邻接表
{
    int i;
    int begin,end,edgevalue;
    char pro;
    EdgeNode *p;
    for(i=0;i<vertexnum;i++)  //初始化
    {
        G[i].in = 0;
        G[i].firstedge = NULL;
    }
    printf("顶点值:\n");
    for(i=0;i<vertexnum;i++)
    {
        fscanf(fp," %d",&G[i].vertexdata);
        printf("%d  ",G[i].vertexdata);
    }
    printf("\n边的起始点、终点、项目序号和项目天数\n");
    for(i=0;i<edgenum;i++)
    {
        p=(EdgeNode*)malloc(sizeof(EdgeNode));
        fscanf(fp," %d,%d,%d,%c",&begin,&end,&edgevalue,&pro);
        printf("%d  %d  %c  %d\n",begin,end,pro,edgevalue);
        p->adjvex = end-1;
        p->weight = edgevalue;
        p->letter = pro;
        p->next = G[begin-1].firstedge;
        G[begin-1].firstedge = p;  //头插
        G[end-1].in++;
    }
}

void LeastDay(VertexNode *G,int vertexnum,int edgenum) //求关键路径
{
    int i=0,j=0,k=0,n=0,days=0,quantity;
    int key[vertexnum]; //关键路径的顶点
    int front,rear,*Queue;
    front = rear=-1;
    int ve[MAX_LEN]={0}; //顶点最早发生时间
    int vl[MAX_LEN]={0};  //顶点最晚发生时间
    int ee[MAX_LEN]={0};  //活动最早发生时间
    int el[MAX_LEN]={0};  //活动最晚发生时间
    EdgeNode *p;
    Queue = (int*)malloc(vertexnum*sizeof(int));
    for(i=0;i<vertexnum;i++)
    {
        if(G[i].in ==0)   //入度为0的顶点入队
            Queue[++rear]=i;
        quantity++;
    }
    while(front!=rear)  //先广遍历求ve
    {
        j = Queue[++front];
        quantity++;
        p = G[j].firstedge;
        while(p)
        {
            k = p->adjvex;
            G[k].in--;
            if((ve[j]+p->weight)>ve[k])
                ve[k] = ve[j]+p->weight;
            if(G[k].in ==0)
                Queue[++rear] = k;
            p=p->next;
        }
    }
    if(quantity<vertexnum)
    {
        printf("此图有回路，无法计算关键路径！\n");
        return;
    }
    days = ve[vertexnum-1];  //总天数
    for(i=0;i<vertexnum;i++)
        vl[i] = days;
    for(i=vertexnum-2;i>=0;i--)  //回退阶段求vl
    {
        j = Queue[i];
        p = G[j].firstedge;
        while(p)
        {
            k = p->adjvex;
            if((vl[k]-p->weight)<vl[j])
                vl[j] = vl[k]-p->weight;
            p=p->next;
        }
    }
    i = -1;
    for(j=0;j<vertexnum;j++)
    {
        p = G[j].firstedge;
        while(p)
        {
            k = p->adjvex;
            ee[++i]=ve[j];   //求ee ，E(i)=VE(j)
            el[i]=vl[k]-p->weight;  //求el ， L(i)=VL(k)-ACT(ai)
            if(el[i]==ee[i])
            {
                printf("关键活动:\n ");
                printf("起点 %d   终点 %d  ",G[j].vertexdata ,G[k].vertexdata);
                if(G[j].firstedge->adjvex==G[k].vertexdata-1)
                    printf("项目序号%c\n",G[j].firstedge->letter);
                else
                    printf("项目序号%c\n",G[j].firstedge->next->letter);
                key[n]=G[j].vertexdata;
                n++;
            }
            p=p->next;
        }
    }
    key[n] = G[vertexnum-1].vertexdata;
    printf("关键路径为：\n");
    for(i=0;i<=n;i++)
    {
        printf("%d",key[i]);
        if(key[i]!=G[vertexnum-1].vertexdata)
            printf("--->");
    }
    printf("\n");
    printf("工程所需最短时间： %d天\n",days);
}

int main()
{
    FILE *fp;
    int vertexnum,edgenum;
    VertexNode *G;
    fp=fopen("project.txt","r");
    if(fp==NULL)
    {
        printf("读取文件project.txt失败！\n");
        exit(0);
    }
    printf("数据已从文件中读入！\n");
    fscanf(fp," %d",&vertexnum);
    fscanf(fp," %d",&edgenum);
    printf("顶点数%d  边数%d\n",vertexnum,edgenum);
    G=(VertexNode*)malloc(vertexnum*sizeof(VertexNode));
    CreatGraph(fp,G,vertexnum,edgenum);
    LeastDay(G,vertexnum,edgenum);
    return 0;
}
