#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MAX_LEN 101
typedef struct  //��������
{
    int x;
    int y;
}point;
int maze[MAX_LEN][MAX_LEN]={0} ;   //��ǰ�Թ�
point pre[MAX_LEN][MAX_LEN]={{0,0}};  //�����������·���е�ǰһ��(��Ѱ�����·��)
typedef struct  //��������
{
    point data[MAX_LEN];
    int front,rear;
}Queue;
void InitQueue(Queue *Q) //��ʼ������
{
    Q->front = 0;
    Q->rear = 0;
}

void EnQueue(Queue *Q ,point x)  //���
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

point DeQueue(Queue *Q) //����
{
    point x;
    if(Q->front==Q->rear)
    {
        printf("���пգ�\n");
        return;
    }
    x = Q->data[Q->front];
    Q->front = (Q->front+1)%MAX_LEN;
    return x;
}

typedef struct  //ջ������ʵ��
{
    point data[MAX_LEN];
    int top;
}Stack;

Stack *Createstack()  //Ϊջ����ռ�
{
    Stack *p;
    p = (Stack *)malloc(sizeof(*p));
    p->top = -1;
    return p;
}

void Push(Stack *p,point x)  //ѹջ
{
    if(p->top == MAX_LEN - 1)
    {
        printf("ջ����p->top=%d\n",p->top);
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

point TOP(Stack *L) //ջ��
{
    point x;
    if (L->top == -1)
    {
        printf("ջ�գ�\n");
        return ;
    }
    x = L->data[L->top];
    return x;
}

int Empty(Stack *L) //�ж�ջ�Ƿ�Ϊ��
{
    return (L->top == -1);
}

void CreateMaze(int row,int column)  //��������Թ�
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
        maze[i][0] = maze[i][column+1] = 1; //��ʼ���Թ�����ǽΪ1
    for(j=0; j<=column+1; j++)
        maze[0][j] = maze[row+1][j] = 1; //��ʼ���Թ�����ǽΪ1
}

void PrintMaze(int row,int column)  //��ӡ�Թ�
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
    point move[8] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};  //�ƶ��˸�����
    if(row==1 && column==1)
        return 1;
    Queue q;      //�������У����ڹ����������
    InitQueue(&q);
    point now;           //��ǰλ��
    now.x = 1;
    now.y = 1;
    EnQueue(&q,now);//����ǰ��ѹ�����
    maze[1][1] = -1;//����ѷ���
    while(!QueueEmpty(q))
    {
        now = DeQueue(&q);  //����Ԫ�س���
        for(i=0;i<8;i++)
        {
            if(now.x+move[i].x==row &&now.y+move[i].y==column)  //�����յ�
                {
                    maze[row][column] = -1;
                    pre[row][column] = now;
                    return 1;
                }
            if(maze[now.x+move[i].x][now.y+move[i].y]==0)
                {
                    point next;  //��һ��λ��
                    next.x = now.x+move[i].x;
                    next.y = now.y+move[i].y;
                    EnQueue(&q,next);  //��һ��λ�ý���
                    maze[next.x][next.y] = -1;  //����ѷ���
                    pre[next.x][next.y] = now;
                }
        }
    }
    return 0;
}

void PrintPath(int row,int column)  //������·��
{
    point temp;         //����λ��
    Stack *s;     //����·������
    s = Createstack();  //����һ��ջ
    temp.x = row;
    temp.y = column;
    while(temp.x != 1 || temp.y != 1)
    {
        Push(s,temp);   //��·��ȫ������ѹջ
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
    int row,column;  //�Թ����к���
    while(1)
    {
        printf("�������Թ�������������:\n");
        scanf("%d%d",&row,&column);
        if(row<=0||column<=0)
        {
            printf("��������ȷ��������������\n");
            continue;
        }
        printf("��������Թ�����\n");
        CreateMaze(row,column);
        PrintMaze(row,column);
        printf("\nѰ·���:\n\n");
        if(BFS_path(row,column))
        {
            printf("���Թ����ͨ·Ϊ:\n");
            PrintPath(row,column);
        }
        else
            printf("���Թ���ͨ·��\n\n");
    }
    return 0;
}
