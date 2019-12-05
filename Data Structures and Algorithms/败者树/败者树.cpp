#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
using namespace std;
#define LEN 10			//���鲢�γ� 
#define MINKEY -1     //Ĭ��ȫΪ����
#define MAXKEY 1000    //���ֵ,��һ����ȫ�������ĸ�ֵ
 
struct Array
{
	int arr[LEN];
	int length;  //˳������ 
	int current; //��ǰ˳��ɨ���λ�� 
}*A;
 
int *LoserTree,*leave;
int k,count;
 
void Adjust(int s)
/*��Ҷ�ӽ��leave[s]�������ĸ����LoserTree[0]����������*/
{
	int t=(s+k)/2;  //t��leave[s]���ڵ��ڰ��������±� 
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
	for(i=0;i<k;i++)LoserTree[i]=k; //���ε������� 
	for(i=k-1;i>=0;i--)Adjust(i);
}
 
void K_Merge()
{
	int i,p;
	for(i=0;i<k;i++)
	{
		p = A[i].current;  //�ֱ��ȡk��˳���ĵ�һ������ 
		leave[i]=A[i].arr[p];
		//cout<<leave[i]<<"  ";
		A[i].current++;
	}
	CreateLoserTree();
	int flag = 0;
	while(flag<count)
	{
		p=LoserTree[0];  //pΪ��ǰ��С�ؼ������ڵ�˳�� 
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
	freopen("losertree.txt","r",stdin);  //����������� 
	int i,j;
	count=0;
	cin>>k;    //˳���ĸ��� 
	A=(Array *)malloc(sizeof(Array)*k);
	for(i=0;i<k;i++)
	{
		cin>>A[i].length;  //˳������ĳ��� 
		count=count+A[i].length;  //�������� 
		for(j=0;j<A[i].length;j++)
		{
			cin>>A[i].arr[j];  //˳����Ԫ�� 
		}
		A[i].current=0;
	}
	LoserTree=(int *)malloc(sizeof(int)*k);
	leave=(int *)malloc(sizeof(int)*(k+1));
 	printf("��·�鲢��������\n");
	K_Merge();
 
	return 0;
}

