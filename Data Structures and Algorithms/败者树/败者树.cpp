#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
using namespace std;
#define LEN 10			//最大归并段长 
#define MINKEY -1     //默认全为正数
#define MAXKEY 1000    //最大值,当一个段全部输出后的赋值
 
struct Array
{
	int arr[LEN];
	int length;  //顺串长度 
	int current; //当前顺串扫描的位置 
}*A;
 
int *LoserTree,*leave;
int k,count;
 
void Adjust(int s)
/*从叶子结点leave[s]到根结点的父结点LoserTree[0]调整败者树*/
{
	int t=(s+k)/2;  //t是leave[s]父节点在败者树的下标 
	int temp;
	while(t>0)
	{
		if(leave[s] > leave[LoserTree[t]])
		{
			temp = s;
			s = LoserTree[t];
			LoserTree[t]=temp;
		}
		t=t/2;
	}
	LoserTree[0]=s;
}
 
void CreateLoserTree()
{
	leave[k]=MINKEY;
	int i;
	for(i=0;i<k;i++)LoserTree[i]=k; //依次调整败者 
	for(i=k-1;i>=0;i--)Adjust(i);
}
 
void K_Merge()
{
	int i,p;
	for(i=0;i<k;i++)
	{
		p = A[i].current;  //分别读取k个顺串的第一个数据 
		leave[i]=A[i].arr[p];
		//cout<<leave[i]<<"  ";
		A[i].current++;
	}
	CreateLoserTree();
	int flag = 0;
	while(flag<count)
	{
		p=LoserTree[0];  //p为当前最小关键字所在的顺串 
		cout<<leave[p]<<"  ";
		flag++;
		if(A[p].current>=A[p].length)leave[p]=MAXKEY;
		else 
		{
			leave[p]=A[p].arr[A[p].current];
			A[p].current++;
		}
		Adjust(p);
	}
	cout<<endl;
}
 
int main()
{
	freopen("losertree.txt","r",stdin);  //代替键盘输入 
	int i,j;
	count=0;
	cin>>k;    //顺串的个数 
	A=(Array *)malloc(sizeof(Array)*k);
	for(i=0;i<k;i++)
	{
		cin>>A[i].length;  //顺串数组的长度 
		count=count+A[i].length;  //数据总数 
		for(j=0;j<A[i].length;j++)
		{
			cin>>A[i].arr[j];  //顺串各元素 
		}
		A[i].current=0;
	}
	LoserTree=(int *)malloc(sizeof(int)*k);
	leave=(int *)malloc(sizeof(int)*(k+1));
 	printf("多路归并排序结果：\n");
	K_Merge();
 
	return 0;
}

