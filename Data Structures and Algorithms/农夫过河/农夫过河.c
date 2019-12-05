#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 30

typedef struct   //����
{
    int farmer;
	int wolf;
	int sheep;
	int vegetable;
}Vertexdata;

int visited[MAX_LEN] = {0};  //���÷���״̬
int path[MAX_LEN] = {0};  //����DFS��������·��������Ԫ�ص�ֵΪ�����ŵ���һ״̬

typedef struct  //�ڽӾ���
{
    Vertexdata verlist[MAX_LEN];
    int edges[MAX_LEN][MAX_LEN];
	int vertexnum;//�������
}MTGraph;

void Creategraph(MTGraph *G)  //�������а�ȫ��ͼ�Ķ���
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

    G->vertexnum = i ;   //��ȫ�Ķ������
    for(i=0;i<G->vertexnum;i++)
    {
        for(j=0;j<G->vertexnum;j++)
        {
            if(Cancross(G,i,j))
            {
                G->edges[i][j]=1;   //����ͼ
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

int Safe(int f,int w,int s,int v) //�ж�ĳ״̬�Ƿ�ȫ
{
    if((f!=s)&&(s==w||s==v))   //��ũ�򲻺�����һ�𣬲�������ǻ����һ��
        return 0;
    else
        return 1;
}

int Cancross(MTGraph *G, int i, int j)  //�ж�����״̬�Ƿ���л�
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

int Location(MTGraph *G,int f,int w,int s,int v) //����ĳ�����ڶ�����е�λ��
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

void DFS(MTGraph *G, int start ,int end)  //�����������
{
    int m=0;
    visited[start]=1;
    for(m=0;m<G->vertexnum;m++)
    {
        if(G->edges[start][m] && !visited[m] && !visited[end]) //������߿�ת������һ������δ�����ʹ�,ֱ���յ�
        {
            path[start]=m;  //��ʱmΪstart����һ��״̬
            DFS(G,m,end);
        }
    }
}

void Printpath(MTGraph G,int start,int end)  //��ӡ·��
{
    int p=start;
    while(p!=end)
    {
        printf("���������ũ��%d ��%d ��%d ��%d\n",G.verlist[p].farmer,G.verlist[p].wolf,\
               G.verlist[p].sheep,G.verlist[p].vegetable);
        p = path[p];
    }
    printf("���������ũ��%d ��%d ��%d ��%d\n",G.verlist[p].farmer,G.verlist[p].wolf,\
               G.verlist[p].sheep,G.verlist[p].vegetable);
}

int main()
{
    int start,end;
    MTGraph G;
    Creategraph(&G);
    start = Location(&G,0,0,0,0); //��ʼ״̬
    end = Location(&G,1,1,1,1); //�յ�״̬
    printf("ũ�����������ϸ���裺(0��ʾ�ںӱ˰���1��ʾ�ںӶ԰�)\n");
    DFS(&G,start,end);
    if(visited[end])
        Printpath(G,start,end);
    return 0;
}
