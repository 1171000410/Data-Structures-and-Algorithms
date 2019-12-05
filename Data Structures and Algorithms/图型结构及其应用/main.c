#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 20
int visited[MAX_LEN];  //记录顶点是否访问过
typedef struct node  //边表结点
{
    int adjvex;  //下标
    struct node *next;
}EdgeNode;
typedef struct   //顶点表结点
{
    char vertexdata; //顶点数据域
    EdgeNode * firstedge;//边链表头指针
}VertexNode;
typedef struct  //图的邻接表
{
    VertexNode verlist[MAX_LEN];
    int n,e;    //顶点数和边数
}AdjGraph;

typedef struct   //顶点
{
    char value;
}Vertexdata;
typedef struct  //图的邻接矩阵
{
    Vertexdata verlist[MAX_LEN];
    int edges[MAX_LEN][MAX_LEN];
	int n,e;//顶点数和边数
}MTGraph;

typedef struct  //建立队列
{
    int data[MAX_LEN];
    int front,rear;
}Queue;

typedef struct  //栈的数组实现
{
    int data[MAX_LEN];
    int top;
}Stack;

Stack *Createstack()  //为栈分配空间
{
    Stack *p;
    p = (Stack *)malloc(sizeof(*p));
    p->top = -1;
    return p;
}

void Push(Stack *p,int x)  //压栈
{
    if (p->top == MAX_LEN - 1)
    {
        printf("栈满！\n");
        return ;
    }
    p->top++;
    p->data[p->top] = x;
}

void Pop(Stack *L)  //出栈
{
    if (L->top == -1)
    {
        printf("栈空！\n");
        return ;
    }
    L->top--;
}

int TOP(Stack *L) //栈顶
{
    int x;
    if (L->top == -1)
    {
        printf("栈空！\n");
        return -1;
    }
    x = L->data[L->top];
    return x;
}

int Empty(Stack *L) //判断栈是否为空
{
    return (L->top == -1);
}

void InitQueue(Queue *Q) //初始化队列
{
    Q->front = 0;
    Q->rear = 0;
}

void EnQueue(Queue *Q ,int x)  //入队
{
    if((Q->rear+1)%MAX_LEN==Q->front)
    {
        printf("队列满！\n");
        return;
    }
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear+1)%MAX_LEN;
}

int QueueEmpty(Queue Q) //判断队列是否为空
{
    if(Q.front==Q.rear)
        return 1;
    else
        return 0;
}

int DeQueue(Queue *Q) //出队
{
    int x;
    if(Q->front==Q->rear)
    {
        printf("队列空！\n");
        return;
    }
    x = Q->data[Q->front];
    Q->front = (Q->front+1)%MAX_LEN;
    return x;
}

void ReadMatrix(MTGraph *G)//从graph_read.txt中读入邻接矩阵
{
    FILE *fp;
    int i,x,y;
    fp=fopen("graph_read.txt","r");
    if(fp==NULL)
    {
        printf("读取文件graph_read.txt失败！\n");
        exit(0);
    }
    memset(G->edges,0,sizeof(G->edges)); //邻接矩阵元素初始化为0
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

void ReadList(AdjGraph *L)//从graph_read.txt中读入邻接表
{
    FILE *fp;
    int i,x,y;
    VertexNode *vertex;
    EdgeNode *edge,*p;
    fp=fopen("graph_read.txt","r");
    if(fp==NULL)
    {
        printf("读取文件graph_read.txt失败！\n");
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
        if( L->verlist[x-1].firstedge==NULL)  //头插法
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

void PrintMatrix(MTGraph G) //打印邻接矩阵
{
    int i,j;
    printf("图的邻接矩阵如下:\n");
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

void PrintList(AdjGraph *L) //打印邻接表
{
    int i;
    printf("图的邻接表如下：\n");
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

void DFS_recursive_Matrix(MTGraph G) //邻接矩阵深度遍历(递归)主算法
{
    int i;
    FILE *fp;
    fp=fopen("graph_write.txt","a+");   //文件结尾添加内容用append
    if(fp==NULL)
    {
        printf("写入文件graph_write.txt失败！\n");
        return -1;
    }
    fprintf(fp,"邻接矩阵深度遍历(递归)结果为:  ");
    for(i=0;i<G.n;i++)
        visited[i] = 0;
    for ( int i = 0; i < G.n; i++ )
    {
        if (!visited[i])
            DFS_Matrix1(fp,G,i);
    }
    printf("\n结果已成功写入文件！\n");
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

void DFS_recursive_List(AdjGraph *L)  //邻接表深度遍历(递归)主算法
{
    int i;
    FILE *fp;
    fp=fopen("graph_write.txt","a+");
    if(fp==NULL)
    {
        printf("写入文件graph_write.txt失败！\n");
        return -1;
    }
    fprintf(fp,"邻接表深度遍历(递归)结果为:  ");
    for(i=0;i<L->n;i++)
        visited[i] = 0;
    for ( int i = 0; i < L->n; i++ )
    {
        if (!visited[i])
            DFS_List1(fp,L,i);
    }
    printf("\n结果已成功写入文件！\n");
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
            DFS_List1(fp,L,p->adjvex); //递归深度遍历
        }
        p= p->next;
    }
}

void BFS_Matrix(MTGraph G)  //邻接矩阵广度遍历主算法
{
    int i;
    FILE *fp;
    fp=fopen("graph_write.txt","a+");   //文件结尾添加内容用append
    if(fp==NULL)
    {
        printf("写入文件graph_write失败！\n");
        return -1;
    }
    fprintf(fp,"邻接矩阵广度遍历结果为:  ");
    for(i=0;i<G.n;i++)
        visited[i] = 0;
    for ( int i = 0; i < G.n; i++ )
    {
        if (!visited[i])
            BFS1(fp,G,i);
    }
    printf("\n结果已成功写入文件！\n");
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
    visited[i] = 1;   //访问过则做标记，并且进队
    EnQueue(&Q,i);
    while(!QueueEmpty(Q))
    {
        j = DeQueue(&Q);
        for(k=0;k<G.n;k++)  //依次搜索j的邻接点
        {
            if(G.edges[j][k]==1&& !visited[k]) //如果k没访问过 ， 访问并入队
            {
                printf("%c ",G.verlist[k].value);
                fprintf(fp,"%c ",G.verlist[k].value);
                visited[k]=1;
                EnQueue(&Q,k);
            }
        }
    }
}

void BFS_List(AdjGraph *L)  //邻接表广度遍历主算法
{
    int i;
    FILE *fp;
    fp=fopen("graph_write.txt","a+");   //文件结尾添加内容用append
    if(fp==NULL)
    {
        printf("写入文件graph_write.txt失败！\n");
        return -1;
    }
    fprintf(fp,"邻接表广度遍历结果为:  ");
    for(i=0;i<L->n;i++)
        visited[i] = 0;
    for ( int i = 0; i < L->n; i++ )
    {
        if (!visited[i])
            BFS2(fp,L,i);
    }
    printf("\n结果已成功写入文件！\n");
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
    visited[i] = 1;   //访问过则做标记，并且进队
    EnQueue(&Q,i);
    while(!QueueEmpty(Q))
    {
        j = DeQueue(&Q);
        p =L->verlist[j].firstedge;  //取头指针
        while(p)  //直到某个顶点所有邻接点访问完
        {
            if(!visited[p->adjvex])
            {
                printf("%c ",L->verlist[p->adjvex].vertexdata);
                fprintf(fp,"%c ",L->verlist[p->adjvex].vertexdata);
                visited[p->adjvex] = 1;   //访问过则做标记，并且进队
                EnQueue(&Q,p->adjvex);
            }
            p=p->next;
        }
    }
}

void DFS_non_recursive_Matrix(MTGraph G)  //邻接矩阵深度遍历(非递归)主算法
{
    int i;
    FILE *fp;
    fp=fopen("graph_write.txt","a+");   //文件结尾添加内容用append
    if(fp==NULL)
    {
        printf("写入文件graph_write失败！\n");
        return -1;
    }
    fprintf(fp,"邻接矩阵深度遍历(非递归)结果为:  ");
    for(i=0;i<G.n;i++)
        visited[i] = 0;
    for ( int i = 0; i < G.n; i++ )
    {
        if (!visited[i])
            DFS_Matrix2(fp,G,i);
    }
    printf("\n结果已成功写入文件！\n");
    fprintf(fp,"\n");
    fclose(fp);
}

void DFS_Matrix2(FILE *fp,MTGraph G, int i)
{
    int data,j;
    Stack *s;
    s = Createstack();  //创建一个栈
    printf("%c ",G.verlist[i].value);
    fprintf(fp,"%c ",G.verlist[i].value);
    visited[i]=1;
    Push(s,i);
    while(!Empty(s))
    {
        data = TOP(s);  //反复取栈顶
        for(j=0;j<G.n;j++)
        {
            if(G.edges[data][j] && !visited[j])
            {
                printf("%c ",G.verlist[j].value);  //访问并压栈
                fprintf(fp,"%c ",G.verlist[j].value);
                visited[j]=1;
                Push(s,j);
                break;  //直接去取栈顶
            }
        }
        if(j==G.n)
            Pop(s);  //如果data相邻的结点都访问结束了 ，就弹出data
    }
}

void DFS_non_recursive_List(AdjGraph *L)  //邻接表深度遍历(非递归)主算法
{
    int i;
    FILE *fp;
    fp=fopen("graph_write.txt","a+");   //文件结尾添加内容用append
    if(fp==NULL)
    {
        printf("写入文件graph_write失败！\n");
        return -1;
    }
    fprintf(fp,"邻接表深度遍历(非递归)结果为:  ");
    for(i=0;i<L->n;i++)
        visited[i] = 0;
    for ( int i = 0; i < L->n; i++ )
    {
        if (!visited[i])
            DFS_List2(fp,L,i);
    }
    printf("\n结果已成功写入文件！\n");
    fprintf(fp,"\n");
    fclose(fp);
}

void DFS_List2(FILE *fp,AdjGraph *L,int i)
{
    int data;
    EdgeNode *p;
    Stack *s;
    s = Createstack();  //创建一个栈
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
                visited[p->adjvex]=1;  //访问并压栈
                printf("%c ",L->verlist[p->adjvex].vertexdata);
                fprintf(fp,"%c ",L->verlist[p->adjvex].vertexdata);
                Push(s,p->adjvex);
                data = TOP(s);
                p = L->verlist[data].firstedge; //再次取栈顶序号对应的头指针
            }
            else
                p = p->next;
        }
        if(p==NULL)
            Pop(s);
    }
}

int Menu()  //菜单
{
    int x;
    printf("\n\n");
    printf("1.图的邻接矩阵\n");
    printf("2.图的邻接表\n");
    printf("3.邻接矩阵的深度优先搜索(递归)\n");
    printf("4.邻接矩阵的深度优先搜索(非递归)\n");
    printf("5.邻接矩阵的广度优先搜索\n");
    printf("6.邻接表的深度优先搜索(递归)\n");
    printf("7.邻接表的深度优先搜索(非递归)\n");
    printf("8.邻接表的广度优先搜索\n");
    printf("9.退出\n\n");
    printf("请选择你要执行的操作：\n");
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
    printf("文件已成功读入邻接矩阵！\n");
    ReadList(L);
    printf("文件已成功读入邻接表！\n");
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
                printf("邻接矩阵深度遍历(递归)结果为:\n");
                DFS_recursive_Matrix(G);
            break;
            case 4:
                printf("邻接矩阵深度遍历(非递归)结果为:\n");
                DFS_non_recursive_Matrix(G);
            break;
            case 5:
                printf("邻接矩阵广度遍历结果为:\n");
                BFS_Matrix(G);
            break;
            case 6:
                printf("邻接表深度遍历(递归)结果为:\n");
                DFS_recursive_List(L);
            break;
            case 7:
                printf("邻接表深度遍历(非递归)结果为:\n");
                DFS_non_recursive_List(L);
            break;
            case 8:
                printf("邻接表深度广度遍历结果为:\n");
                BFS_List(L);
            break;
            case 9:exit(0);
            default:printf("请输入正确序号！\n");
        }
    }
    return 0;
}
