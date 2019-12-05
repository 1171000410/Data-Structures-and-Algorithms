#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 20
int visited[MAX_LEN];  //��¼�����Ƿ���ʹ�
typedef struct node  //�߱���
{
    int adjvex;  //�±�
    struct node *next;
}EdgeNode;
typedef struct   //�������
{
    char vertexdata; //����������
    EdgeNode * firstedge;//������ͷָ��
}VertexNode;
typedef struct  //ͼ���ڽӱ�
{
    VertexNode verlist[MAX_LEN];
    int n,e;    //�������ͱ���
}AdjGraph;

typedef struct   //����
{
    char value;
}Vertexdata;
typedef struct  //ͼ���ڽӾ���
{
    Vertexdata verlist[MAX_LEN];
    int edges[MAX_LEN][MAX_LEN];
	int n,e;//�������ͱ���
}MTGraph;

typedef struct  //��������
{
    int data[MAX_LEN];
    int front,rear;
}Queue;

typedef struct  //ջ������ʵ��
{
    int data[MAX_LEN];
    int top;
}Stack;

Stack *Createstack()  //Ϊջ����ռ�
{
    Stack *p;
    p = (Stack *)malloc(sizeof(*p));
    p->top = -1;
    return p;
}

void Push(Stack *p,int x)  //ѹջ
{
    if (p->top == MAX_LEN - 1)
    {
        printf("ջ����\n");
        return ;
    }
    p->top++;
    p->data[p->top] = x;
}

void Pop(Stack *L)  //��ջ
{
    if (L->top == -1)
    {
        printf("ջ�գ�\n");
        return ;
    }
    L->top--;
}

int TOP(Stack *L) //ջ��
{
    int x;
    if (L->top == -1)
    {
        printf("ջ�գ�\n");
        return -1;
    }
    x = L->data[L->top];
    return x;
}

int Empty(Stack *L) //�ж�ջ�Ƿ�Ϊ��
{
    return (L->top == -1);
}

void InitQueue(Queue *Q) //��ʼ������
{
    Q->front = 0;
    Q->rear = 0;
}

void EnQueue(Queue *Q ,int x)  //���
{
    if((Q->rear+1)%MAX_LEN==Q->front)
    {
        printf("��������\n");
        return;
    }
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear+1)%MAX_LEN;
}

int QueueEmpty(Queue Q) //�ж϶����Ƿ�Ϊ��
{
    if(Q.front==Q.rear)
        return 1;
    else
        return 0;
}

int DeQueue(Queue *Q) //����
{
    int x;
    if(Q->front==Q->rear)
    {
        printf("���пգ�\n");
        return;
    }
    x = Q->data[Q->front];
    Q->front = (Q->front+1)%MAX_LEN;
    return x;
}

void ReadMatrix(MTGraph *G)//��graph_read.txt�ж����ڽӾ���
{
    FILE *fp;
    int i,x,y;
    fp=fopen("graph_read.txt","r");
    if(fp==NULL)
    {
        printf("��ȡ�ļ�graph_read.txtʧ�ܣ�\n");
        exit(0);
    }
    memset(G->edges,0,sizeof(G->edges)); //�ڽӾ���Ԫ�س�ʼ��Ϊ0
    fscanf(fp,"%d",&G->n);
    fscanf(fp,"%d",&G->e);
    for(i=0;i<G->n;i++)
    {
        fscanf(fp," %c",&G->verlist[i].value);
    }
    for(i=0;i<G->e;i++)
    {
        fscanf(fp,"%d,%d",&x,&y);
        G->edges[x-1][y-1]=1;
    }
    fclose(fp);
}

void ReadList(AdjGraph *L)//��graph_read.txt�ж����ڽӱ�
{
    FILE *fp;
    int i,x,y;
    VertexNode *vertex;
    EdgeNode *edge,*p;
    fp=fopen("graph_read.txt","r");
    if(fp==NULL)
    {
        printf("��ȡ�ļ�graph_read.txtʧ�ܣ�\n");
        exit(0);
    }
    fscanf(fp,"%d",&L->n);
    fscanf(fp,"%d",&L->e);
    for(i=0;i<L->n;i++)
    {
        fscanf(fp," %c",&L->verlist[i].vertexdata);
        L->verlist[i].firstedge=NULL;
    }
    for(i=0;i<L->e;i++)
    {
        edge = (EdgeNode*)malloc(sizeof(EdgeNode));
        edge->adjvex=0;
        fscanf(fp,"%d,%d",&x,&y);
        if( L->verlist[x-1].firstedge==NULL)  //ͷ�巨
        {
            L->verlist[x-1].firstedge=edge;
            edge->next=NULL;
            edge->adjvex=y-1;
        }
        if(L->verlist[x-1].firstedge->next==NULL)
        {
            L->verlist[x-1].firstedge->next=edge;
            edge->next=NULL;
            edge->adjvex=y-1;
        }
        else
        {
            p=L->verlist[x-1].firstedge->next;
            L->verlist[x-1].firstedge->next=edge;
            edge->adjvex=y-1;
            edge->next=p;
        }
    }
    fclose(fp);
}

void PrintMatrix(MTGraph G) //��ӡ�ڽӾ���
{
    int i,j;
    printf("ͼ���ڽӾ�������:\n");
    printf("  ");
    for(i=0;i<G.n;i++)
        printf("%c ",G.verlist[i].value);
    printf("\n");
    for(i=0;i<G.n;i++)
    {
        printf("%c ",G.verlist[i].value);
        for(j=0;j<G.n;j++)
        {
            printf("%d ",G.edges[i][j]);
        }
        printf("\n");
    }
}

void PrintList(AdjGraph *L) //��ӡ�ڽӱ�
{
    int i;
    printf("ͼ���ڽӱ����£�\n");
    for(i=0;i<L->n;i++)
    {
        printf("%c->",L->verlist[i].vertexdata);
        while(L->verlist[i].firstedge!=NULL)
        {
            printf("%c->",L->verlist[L->verlist[i].firstedge->adjvex].vertexdata);
            if(L->verlist[i].firstedge->next!=NULL)
            {L->verlist[i].firstedge = L->verlist[i].firstedge->next;}
            else
                break;
        }
        printf("#\n");
    }
}

void DFS_recursive_Matrix(MTGraph G) //�ڽӾ�����ȱ���(�ݹ�)���㷨
{
    int i;
    FILE *fp;
    fp=fopen("graph_write.txt","a+");   //�ļ���β���������append
    if(fp==NULL)
    {
        printf("д���ļ�graph_write.txtʧ�ܣ�\n");
        return -1;
    }
    fprintf(fp,"�ڽӾ�����ȱ���(�ݹ�)���Ϊ:  ");
    for(i=0;i<G.n;i++)
        visited[i] = 0;
    for ( int i = 0; i < G.n; i++ )
    {
        if (!visited[i])
            DFS_Matrix1(fp,G,i);
    }
    printf("\n����ѳɹ�д���ļ���\n");
    fprintf(fp,"\n");
    fclose(fp);
}

void DFS_Matrix1(FILE *fp,MTGraph G, int i)
{
    int j;
    visited[i] = 1;
    printf("%c ", G.verlist[i].value);
    fprintf(fp,"%c ",G.verlist[i].value);
    for (j=0; j<G.n; j++)
    {
        if (G.edges[i][j] !=0  &&  !visited[j])
            DFS_Matrix1(fp,G, j);
    }
}

void DFS_recursive_List(AdjGraph *L)  //�ڽӱ���ȱ���(�ݹ�)���㷨
{
    int i;
    FILE *fp;
    fp=fopen("graph_write.txt","a+");
    if(fp==NULL)
    {
        printf("д���ļ�graph_write.txtʧ�ܣ�\n");
        return -1;
    }
    fprintf(fp,"�ڽӱ���ȱ���(�ݹ�)���Ϊ:  ");
    for(i=0;i<L->n;i++)
        visited[i] = 0;
    for ( int i = 0; i < L->n; i++ )
    {
        if (!visited[i])
            DFS_List1(fp,L,i);
    }
    printf("\n����ѳɹ�д���ļ���\n");
    fprintf(fp,"\n");
    fclose(fp);
}

void DFS_List1(FILE *fp,AdjGraph *L, int i)
{
    int j;
    EdgeNode *p;
    visited[i] = 1;
    printf("%c ", L->verlist[i].vertexdata);
    fprintf(fp,"%c ",L->verlist[i].vertexdata);
    p = L->verlist[i].firstedge;
    while(p)
    {
        if(!visited[p->adjvex])
        {
            DFS_List1(fp,L,p->adjvex); //�ݹ���ȱ���
        }
        p= p->next;
    }
}

void BFS_Matrix(MTGraph G)  //�ڽӾ����ȱ������㷨
{
    int i;
    FILE *fp;
    fp=fopen("graph_write.txt","a+");   //�ļ���β���������append
    if(fp==NULL)
    {
        printf("д���ļ�graph_writeʧ�ܣ�\n");
        return -1;
    }
    fprintf(fp,"�ڽӾ����ȱ������Ϊ:  ");
    for(i=0;i<G.n;i++)
        visited[i] = 0;
    for ( int i = 0; i < G.n; i++ )
    {
        if (!visited[i])
            BFS1(fp,G,i);
    }
    printf("\n����ѳɹ�д���ļ���\n");
    fprintf(fp,"\n");
    fclose(fp);
}

void BFS1(FILE *fp, MTGraph G , int i)
{
    int j,k;
    Queue Q;
    InitQueue(&Q);
    printf("%c ",G.verlist[i].value);
    fprintf(fp,"%c ",G.verlist[i].value);
    visited[i] = 1;   //���ʹ�������ǣ����ҽ���
    EnQueue(&Q,i);
    while(!QueueEmpty(Q))
    {
        j = DeQueue(&Q);
        for(k=0;k<G.n;k++)  //��������j���ڽӵ�
        {
            if(G.edges[j][k]==1&& !visited[k]) //���kû���ʹ� �� ���ʲ����
            {
                printf("%c ",G.verlist[k].value);
                fprintf(fp,"%c ",G.verlist[k].value);
                visited[k]=1;
                EnQueue(&Q,k);
            }
        }
    }
}

void BFS_List(AdjGraph *L)  //�ڽӱ��ȱ������㷨
{
    int i;
    FILE *fp;
    fp=fopen("graph_write.txt","a+");   //�ļ���β���������append
    if(fp==NULL)
    {
        printf("д���ļ�graph_write.txtʧ�ܣ�\n");
        return -1;
    }
    fprintf(fp,"�ڽӱ��ȱ������Ϊ:  ");
    for(i=0;i<L->n;i++)
        visited[i] = 0;
    for ( int i = 0; i < L->n; i++ )
    {
        if (!visited[i])
            BFS2(fp,L,i);
    }
    printf("\n����ѳɹ�д���ļ���\n");
    fprintf(fp,"\n");
    fclose(fp);
}

void BFS2(FILE *fp,AdjGraph *L,int i)
{
    int j;
    EdgeNode *p;
    Queue Q;
    InitQueue(&Q);
    printf("%c ",L->verlist[i].vertexdata);
    fprintf(fp,"%c ",L->verlist[i].vertexdata);
    visited[i] = 1;   //���ʹ�������ǣ����ҽ���
    EnQueue(&Q,i);
    while(!QueueEmpty(Q))
    {
        j = DeQueue(&Q);
        p =L->verlist[j].firstedge;  //ȡͷָ��
        while(p)  //ֱ��ĳ�����������ڽӵ������
        {
            if(!visited[p->adjvex])
            {
                printf("%c ",L->verlist[p->adjvex].vertexdata);
                fprintf(fp,"%c ",L->verlist[p->adjvex].vertexdata);
                visited[p->adjvex] = 1;   //���ʹ�������ǣ����ҽ���
                EnQueue(&Q,p->adjvex);
            }
            p=p->next;
        }
    }
}

void DFS_non_recursive_Matrix(MTGraph G)  //�ڽӾ�����ȱ���(�ǵݹ�)���㷨
{
    int i;
    FILE *fp;
    fp=fopen("graph_write.txt","a+");   //�ļ���β���������append
    if(fp==NULL)
    {
        printf("д���ļ�graph_writeʧ�ܣ�\n");
        return -1;
    }
    fprintf(fp,"�ڽӾ�����ȱ���(�ǵݹ�)���Ϊ:  ");
    for(i=0;i<G.n;i++)
        visited[i] = 0;
    for ( int i = 0; i < G.n; i++ )
    {
        if (!visited[i])
            DFS_Matrix2(fp,G,i);
    }
    printf("\n����ѳɹ�д���ļ���\n");
    fprintf(fp,"\n");
    fclose(fp);
}

void DFS_Matrix2(FILE *fp,MTGraph G, int i)
{
    int data,j;
    Stack *s;
    s = Createstack();  //����һ��ջ
    printf("%c ",G.verlist[i].value);
    fprintf(fp,"%c ",G.verlist[i].value);
    visited[i]=1;
    Push(s,i);
    while(!Empty(s))
    {
        data = TOP(s);  //����ȡջ��
        for(j=0;j<G.n;j++)
        {
            if(G.edges[data][j] && !visited[j])
            {
                printf("%c ",G.verlist[j].value);  //���ʲ�ѹջ
                fprintf(fp,"%c ",G.verlist[j].value);
                visited[j]=1;
                Push(s,j);
                break;  //ֱ��ȥȡջ��
            }
        }
        if(j==G.n)
            Pop(s);  //���data���ڵĽ�㶼���ʽ����� ���͵���data
    }
}

void DFS_non_recursive_List(AdjGraph *L)  //�ڽӱ���ȱ���(�ǵݹ�)���㷨
{
    int i;
    FILE *fp;
    fp=fopen("graph_write.txt","a+");   //�ļ���β���������append
    if(fp==NULL)
    {
        printf("д���ļ�graph_writeʧ�ܣ�\n");
        return -1;
    }
    fprintf(fp,"�ڽӱ���ȱ���(�ǵݹ�)���Ϊ:  ");
    for(i=0;i<L->n;i++)
        visited[i] = 0;
    for ( int i = 0; i < L->n; i++ )
    {
        if (!visited[i])
            DFS_List2(fp,L,i);
    }
    printf("\n����ѳɹ�д���ļ���\n");
    fprintf(fp,"\n");
    fclose(fp);
}

void DFS_List2(FILE *fp,AdjGraph *L,int i)
{
    int data;
    EdgeNode *p;
    Stack *s;
    s = Createstack();  //����һ��ջ
    printf("%c ",L->verlist[i].vertexdata);
    fprintf(fp,"%c ",L->verlist[i].vertexdata);
    visited[i]=1;
    Push(s,i);
    while(!Empty(s))
    {
        data = TOP(s);
        p = L->verlist[data].firstedge;
        while(p)
        {
            if(!visited[p->adjvex])
            {
                visited[p->adjvex]=1;  //���ʲ�ѹջ
                printf("%c ",L->verlist[p->adjvex].vertexdata);
                fprintf(fp,"%c ",L->verlist[p->adjvex].vertexdata);
                Push(s,p->adjvex);
                data = TOP(s);
                p = L->verlist[data].firstedge; //�ٴ�ȡջ����Ŷ�Ӧ��ͷָ��
            }
            else
                p = p->next;
        }
        if(p==NULL)
            Pop(s);
    }
}

int Menu()  //�˵�
{
    int x;
    printf("\n\n");
    printf("1.ͼ���ڽӾ���\n");
    printf("2.ͼ���ڽӱ�\n");
    printf("3.�ڽӾ���������������(�ݹ�)\n");
    printf("4.�ڽӾ���������������(�ǵݹ�)\n");
    printf("5.�ڽӾ���Ĺ����������\n");
    printf("6.�ڽӱ�������������(�ݹ�)\n");
    printf("7.�ڽӱ�������������(�ǵݹ�)\n");
    printf("8.�ڽӱ�Ĺ����������\n");
    printf("9.�˳�\n\n");
    printf("��ѡ����Ҫִ�еĲ�����\n");
    scanf("%d",&x);
    return x;
}

int main()
{
    char ch;
    MTGraph G;
    AdjGraph *L;
    L = (AdjGraph*)malloc(sizeof(AdjGraph));
    ReadMatrix(&G);
    printf("�ļ��ѳɹ������ڽӾ���\n");
    ReadList(L);
    printf("�ļ��ѳɹ������ڽӱ�\n");
    while(1)
    {
        ch = Menu();
        switch(ch)
        {
            case 1:PrintMatrix(G);
            break;
            case 2:PrintList(L);
            break;
            case 3:
                printf("�ڽӾ�����ȱ���(�ݹ�)���Ϊ:\n");
                DFS_recursive_Matrix(G);
            break;
            case 4:
                printf("�ڽӾ�����ȱ���(�ǵݹ�)���Ϊ:\n");
                DFS_non_recursive_Matrix(G);
            break;
            case 5:
                printf("�ڽӾ����ȱ������Ϊ:\n");
                BFS_Matrix(G);
            break;
            case 6:
                printf("�ڽӱ���ȱ���(�ݹ�)���Ϊ:\n");
                DFS_recursive_List(L);
            break;
            case 7:
                printf("�ڽӱ���ȱ���(�ǵݹ�)���Ϊ:\n");
                DFS_non_recursive_List(L);
            break;
            case 8:
                printf("�ڽӱ���ȹ�ȱ������Ϊ:\n");
                BFS_List(L);
            break;
            case 9:exit(0);
            default:printf("��������ȷ��ţ�\n");
        }
    }
    return 0;
}
