#include <stdio.h>
#include <stdlib.h>
#define LEN 100
int main()
{
    double maxvalue,num[LEN];
    int i;
    printf("Input 100 numbers:\n");
    for (i=0;i<LEN;i++)
    {
        scanf("%lf",&num[i]);
    }
    maxvalue=num[0];
    for (i=0;i<LEN;i++)
    {
        if(maxvalue<num[i])
            maxvalue=num[i];
    }
    printf("maxvalue=%lf\n",maxvalue);
    printf("position: ");
    for (i=0;i<LEN;i++)
     {
         if(num[i]==maxvalue)
            printf("%d\t",i+1);
     }
     return 0;
}
/*
  ������Բ��õĴ洢�ṹ��˳��ṹ������
  �Ա����ִ洢�ṹ��1.����洢�ṹ���ڴ��ַ��һ���������ģ���˳��洢�ṹ���ڴ��ַһ���������ģ�
  2.��ʽ�洢�������ڽ�Ƶ���ز��롢ɾ��������Ԫ��ʱ����˳��洢�ṹ������Ƶ����ѯʱʹ�á�
  �ۺ�����������˳��ṹ������洢���ӷ��㡣
*/
