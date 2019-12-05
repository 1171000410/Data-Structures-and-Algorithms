#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 5
int Mystrcmp(char str[],char dst[])
{
    int i;
    for(i=0;str[i]==dst[i];i++)
    {
        if(str[i]=='\0')
            return -1;
    }
    if(str[i]=='\0')
        {
            return -1;
        }
    if(dst[i]=='\0')
        {
            return 1;
        }
    if(str[i]<58&&dst[i]>58)
        {
            return 1;
        }
    if(dst[i]<58&&str[i]>58)
        {
            return -1;
        }
    else
    return (str[i]-dst[i]);
}
int main()
{
    char name[][MAX_LEN]={"PAB","5C","PABC","CXY","CRSI","7","B899","B9"};
    int n=8,i,j;
    char temp[MAX_LEN];
    printf("Primitive order:");
    for(i=0;i<n;i++)
    {
        printf("%s ",name[i]);
    }
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(Mystrcmp(name[i],name[j])>0)
            {
                strcpy(temp,name[i]);
                strcpy(name[i],name[j]);
                strcpy(name[j],temp);
            }
        }
    }
    printf("\nNew order:");
    for(i=0;i<n;i++)
    {
        printf("%s ",name[i]);
    }
    return 0;
}
/*
  �����洢��ʾ��Ϊ���ݽ���������
  ɢ�д洢��ʾ���������ݵĹؼ�����ɢ�к�������������ݵĴ洢��ַ��
  ������Բ��õĴ洢�ṹ��˳��ṹ������
  �Ա����ִ洢�ṹ��1.����洢�ṹ���ڴ��ַ��һ���������ģ���˳��洢�ṹ���ڴ��ַһ���������ģ�
  2.��ʽ�洢�������ڽ�Ƶ���ز��롢ɾ��������Ԫ��ʱ����˳��洢�ṹ������Ƶ����ѯʱʹ�á�
  ���ݱ�����ص㣬ѡ����˳��洢�ṹ���������ַ�������洢���ݡ�
*/
