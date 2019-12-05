#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MAX_LEN 101
typedef struct  //横纵坐标
{
    int x;
    int y;
}point;
int maze[MAX_LEN][MAX_LEN]={0} ;   //当前迷宫
point pre[MAX_LEN][MAX_LEN]={{0,0}};  //保存任意点在路径中的前一步(以寻找最短路径)
typedef struct  //建立队列
{
    point data[MAX_LEN];
    int front,rear;
}Queue;
void InitQueue(Queue *Q) //初始化队列
{
    Q->front = 0;
    Q->rear = 0;
}

void EnQueue(Queue *Q ,point x)  //入队
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

point DeQueue(Queue *Q) //出队
{
    point x;
    if(Q->front==Q->rear)
    {
        printf("队列空！\n");
        return;
    }
    x = Q->data[Q->front];
    Q->front = (Q->front+1)%MAX_LEN;
    return x;
}

typedef struct  //栈的数组实现
{
    point data[MAX_LEN];
    int top;
}Stack;

Stack *Createstack()  //为栈分配空间
{
    Stack *p;
    p = (Stack *)malloc(sizeof(*p));
    p->top = -1;
    return p;
}

void Push(Stack *p,point x)  //压栈
{
    if(p->top == MAX_LEN - 1)
    {
        printf("栈满！p->top=%d\n",p->top);
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

point TOP(Stack *L) //栈顶
{
    point x;
    if (L->top == -1)
    {
        printf("栈空！\n");
        return ;
    }
    x = L->data[L->top];
    return x;
}

int Empty(Stack *L) //判断栈是否为空
{
    return (L->top == -1);
}

void CreateMaze(int row,int column)  //随机生成迷宫
{
    int i,j,num;
    time_t t;
    srand(time(&t));
    for(i=1;i<=row;i++)
        for(j=1;j<=column;j++)
        {
            maze[i][j]=rand()%2;
            if(!maze[i][j])
                num++;
        }
    if(num<row*column/2)
    {
        for(i=1;i<=row;i++)
            for(j=1;j<=column;j++)
                if(maze[i][j])
                maze[i][j]-=rand()%2;
    }
    maze[1][1]=0;
    maze[row][column]=0;
    for(i=0; i<=row+1; i++)
        maze[i][0] = maze[i][column+1] = 1; //初始化迷宫的外墙为1
    for(j=0; j<=column+1; j++)
        maze[0][j] = maze[row+1][j] = 1; //初始化迷宫的外墙为1
}

void PrintMaze(int row,int column)  //打印迷宫
{
    int i,j;
    for(i=1;i<=row;i++)
        for(j=1;j<=column;j++)
        {
            printf("%d ",maze[i][j]);
            if(j==column)
                printf("\n");
        }
}

int BFS_path(int row,int column)
{
	int i; 
    point move[8] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};  //移动八个方向
    if(row==1 && column==1)
        return 1;
    Queue q;      //创建队列，用于广度优先搜索
    InitQueue(&q);
    point now;           //当前位置
    now.x = 1;
    now.y = 1;
    EnQueue(&q,now);//将当前点压入队列
    maze[1][1] = -1;//标记已访问
    while(!QueueEmpty(q))
    {
        now = DeQueue(&q);  //队首元素出队
        for(i=0;i<8;i++)
        {
            if(now.x+move[i].x==row &&now.y+move[i].y==column)  //到达终点
                {
                    maze[row][column] = -1;
                    pre[row][column] = now;
                    return 1;
                }
            if(maze[now.x+move[i].x][now.y+move[i].y]==0)
                {
                    point next;  //下一个位置
                    next.x = now.x+move[i].x;
                    next.y = now.y+move[i].y;
                    EnQueue(&q,next);  //下一个位置进队
                    maze[next.x][next.y] = -1;  //标记已访问
                    pre[next.x][next.y] = now;
                }
        }
    }
    return 0;
}

void PrintPath(int row,int column)  //输出最短路径
{
    point temp;         //保存位置
    Stack *s;     //保存路径序列
    s = Createstack();  //创建一个栈
    temp.x = row;
    temp.y = column;
    while(temp.x != 1 || temp.y != 1)
    {
        Push(s,temp);   //把路径全部逆序压栈
        temp = pre[temp.x][temp.y];
    }
    printf("(1,1)\n");
    while(!Empty(s))
    {
        temp = TOP(s);
        printf("(%d,%d)\n",temp.x,temp.y);
        Pop(s);
    }
    printf("\n");
}

int main()
{
    int row,column;  //迷宫的行和列
    while(1)
    {
        printf("请输入迷宫的行数和列数:\n");
        scanf("%d%d",&row,&column);
        if(row<=0||column<=0)
        {
            printf("请输入正确的行数和列数！\n");
            continue;
        }
        printf("随机生成迷宫如下\n");
        CreateMaze(row,column);
        PrintMaze(row,column);
        printf("\n寻路结果:\n\n");
        if(BFS_path(row,column))
        {
            printf("此迷宫最近通路为:\n");
            PrintPath(row,column);
        }
        else
            printf("此迷宫无通路！\n\n");
    }
    return 0;
}
