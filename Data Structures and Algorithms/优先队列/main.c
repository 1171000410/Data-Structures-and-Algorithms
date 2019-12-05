#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 10
typedef struct
{
    int pri[MAX_LEN];  //���ȼ�
    int num[MAX_LEN]; //���̷����
    int n;
}Heap;
/*�������в���һ��Ԫ��*/
void Insert(Heap *heap,int x,int y)
{
    int i;
    if(heap->n!=MAX_LEN-1)
    {
        heap->n++;
        i=heap->n;
        //�������Ԫ�����ȼ����󣬻������ȼ���ͬ����Ÿ�С��ѭ��
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
/*ɾ���������Ԫ��*/
void Delete(Heap *heap)
{
    int parent=1,child=2,pri,num,tmp1,tmp2;
    if(heap->n==0)
    {
        printf("�ѿգ�\n");
        return;
    }
    pri = heap->pri[1];
    num = heap->num[1];
    printf("�������ȼ�%d  �����%d\n",pri,num);
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
/*�������*/
void Readfile(Heap *heap)//��task.txt�ж�������
{
    FILE *fp;
    int x,y,i;
    fp=fopen("task.txt","r");
    if(fp==NULL)
    {
        printf("��ȡ�ļ�task.txtʧ�ܣ�\n");
        exit(0);
    }
    printf("���ļ��ж�ȡ��������:\n");
    for(i=0;i<5;i++)
    {
        fscanf(fp," %d",&x);
        fscanf(fp," %d",&y);
        printf("���̷����%d  ���ȼ�%d\n",x,y);
        Insert(heap,y,x);
    }
    fclose(fp);
}
int main()
{
    Heap heap;
    heap.n=0; //����һ���ն�
    Readfile(&heap);
    printf("\n���������:\n");
    while(heap.n!=0)
    {
        Delete(&heap);
    }
    return 0;
}
