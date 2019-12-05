#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 30
typedef struct node  //�߱���
{
    int adjvex;   //�±�
    int weight;  //Ȩֵ
    char letter;  //��Ŀ���
    struct node *next;
}EdgeNode;
typedef struct   //�������
{
    int vertexdata; //����������
    int in;   //�������
    EdgeNode * firstedge;//������ͷָ��
}VertexNode;

void CreatGraph(FILE *fp,VertexNode *G,int vertexnum,int edgenum)  //����ͼ���ڽӱ�
{
    int i;
    int begin,end,edgevalue;
    char pro;
    EdgeNode *p;
    for(i=0;i<vertexnum;i++)  //��ʼ��
    {
        G[i].in = 0;
        G[i].firstedge = NULL;
    }
    printf("����ֵ:\n");
    for(i=0;i<vertexnum;i++)
    {
        fscanf(fp," %d",&G[i].vertexdata);
        printf("%d  ",G[i].vertexdata);
    }
    printf("\n�ߵ���ʼ�㡢�յ㡢��Ŀ��ź���Ŀ����\n");
    for(i=0;i<edgenum;i++)
    {
        p=(EdgeNode*)malloc(sizeof(EdgeNode));
        fscanf(fp," %d,%d,%d,%c",&begin,&end,&edgevalue,&pro);
        printf("%d  %d  %c  %d\n",begin,end,pro,edgevalue);
        p->adjvex = end-1;
        p->weight = edgevalue;
        p->letter = pro;
        p->next = G[begin-1].firstedge;
        G[begin-1].firstedge = p;  //ͷ��
        G[end-1].in++;
    }
}

void LeastDay(VertexNode *G,int vertexnum,int edgenum) //��ؼ�·��
{
    int i=0,j=0,k=0,n=0,days=0,quantity;
    int key[vertexnum]; //�ؼ�·���Ķ���
    int front,rear,*Queue;
    front = rear=-1;
    int ve[MAX_LEN]={0}; //�������緢��ʱ��
    int vl[MAX_LEN]={0};  //����������ʱ��
    int ee[MAX_LEN]={0};  //����緢��ʱ��
    int el[MAX_LEN]={0};  //�������ʱ��
    EdgeNode *p;
    Queue = (int*)malloc(vertexnum*sizeof(int));
    for(i=0;i<vertexnum;i++)
    {
        if(G[i].in ==0)   //���Ϊ0�Ķ������
            Queue[++rear]=i;
        quantity++;
    }
    while(front!=rear)  //�ȹ������ve
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
        printf("��ͼ�л�·���޷�����ؼ�·����\n");
        return;
    }
    days = ve[vertexnum-1];  //������
    for(i=0;i<vertexnum;i++)
        vl[i] = days;
    for(i=vertexnum-2;i>=0;i--)  //���˽׶���vl
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
            ee[++i]=ve[j];   //��ee ��E(i)=VE(j)
            el[i]=vl[k]-p->weight;  //��el �� L(i)=VL(k)-ACT(ai)
            if(el[i]==ee[i])
            {
                printf("�ؼ��:\n ");
                printf("��� %d   �յ� %d  ",G[j].vertexdata ,G[k].vertexdata);
                if(G[j].firstedge->adjvex==G[k].vertexdata-1)
                    printf("��Ŀ���%c\n",G[j].firstedge->letter);
                else
                    printf("��Ŀ���%c\n",G[j].firstedge->next->letter);
                key[n]=G[j].vertexdata;
                n++;
            }
            p=p->next;
        }
    }
    key[n] = G[vertexnum-1].vertexdata;
    printf("�ؼ�·��Ϊ��\n");
    for(i=0;i<=n;i++)
    {
        printf("%d",key[i]);
        if(key[i]!=G[vertexnum-1].vertexdata)
            printf("--->");
    }
    printf("\n");
    printf("�����������ʱ�䣺 %d��\n",days);
}

int main()
{
    FILE *fp;
    int vertexnum,edgenum;
    VertexNode *G;
    fp=fopen("project.txt","r");
    if(fp==NULL)
    {
        printf("��ȡ�ļ�project.txtʧ�ܣ�\n");
        exit(0);
    }
    printf("�����Ѵ��ļ��ж��룡\n");
    fscanf(fp," %d",&vertexnum);
    fscanf(fp," %d",&edgenum);
    printf("������%d  ����%d\n",vertexnum,edgenum);
    G=(VertexNode*)malloc(vertexnum*sizeof(VertexNode));
    CreatGraph(fp,G,vertexnum,edgenum);
    LeastDay(G,vertexnum,edgenum);
    return 0;
}
