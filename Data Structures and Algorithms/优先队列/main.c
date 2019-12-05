#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 10
typedef struct
{
    int pri[MAX_LEN];  //优先级
    int num[MAX_LEN]; //进程服务号
    int n;
}Heap;
/*向大根堆中插入一个元素*/
void Insert(Heap *heap,int x,int y)
{
    int i;
    if(heap->n!=MAX_LEN-1)
    {
        heap->n++;
        i=heap->n;
        //当插入的元素优先级更大，或者优先级相同服务号更小，循环
        while((i !=1)&&((x>heap->pri[i/2])||(x==heap->pri[i/2]&&y<heap->num[i/2])))
        {
            heap->pri[i]=heap->pri[i/2];
            heap->num[i]=heap->num[i/2];
            i=i/2;
        }
        heap->pri[i]=x;
        heap->num[i]=y;
    }
}
/*删除堆中最大元素*/
void Delete(Heap *heap)
{
    int parent=1,child=2,pri,num,tmp1,tmp2;
    if(heap->n==0)
    {
        printf("堆空！\n");
        return;
    }
    pri = heap->pri[1];
    num = heap->num[1];
    printf("进程优先级%d  服务号%d\n",pri,num);
    tmp1 = heap->pri[heap->n];
    tmp2 = heap->num[heap->n];
    heap->n--;
    while(child<=heap->n)
    {
        if((child<heap->n)&&((heap->pri[child]<heap->pri[child+1])\
            ||(heap->pri[child]==heap->pri[child+1]&&heap->num[child]>heap->num[child+1])))
            child++;
        if((tmp1>heap->pri[child])||(tmp1==heap->pri[child]&&tmp2<heap->num[child]))
            break;
        heap->pri[parent]=heap->pri[child];
        heap->num[parent]=heap->num[child];
        parent=child;
        child*=2;
    }
    heap->pri[parent]=tmp1;
    heap->num[parent]=tmp2;
}
/*输入进程*/
void Readfile(Heap *heap)//从task.txt中读入数据
{
    FILE *fp;
    int x,y,i;
    fp=fopen("task.txt","r");
    if(fp==NULL)
    {
        printf("读取文件task.txt失败！\n");
        exit(0);
    }
    printf("从文件中读取数据如下:\n");
    for(i=0;i<5;i++)
    {
        fscanf(fp," %d",&x);
        fscanf(fp," %d",&y);
        printf("进程服务号%d  优先级%d\n",x,y);
        Insert(heap,y,x);
    }
    fclose(fp);
}
int main()
{
    Heap heap;
    heap.n=0; //创建一个空堆
    Readfile(&heap);
    printf("\n进程排序后:\n");
    while(heap.n!=0)
    {
        Delete(&heap);
    }
    return 0;
}
