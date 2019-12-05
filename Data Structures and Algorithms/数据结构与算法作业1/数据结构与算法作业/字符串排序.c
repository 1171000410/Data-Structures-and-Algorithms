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
  索引存储表示：为数据建立索引表。
  散列存储表示：根据数据的关键码用散列函数计算出该数据的存储地址。
  本题可以采用的存储结构有顺序结构或链表。
  对比两种存储结构：1.链表存储结构的内存地址不一定是连续的，但顺序存储结构的内存地址一定是连续的；
  2.链式存储适用于在较频繁地插入、删除、更新元素时，而顺序存储结构适用于频繁查询时使用。
  根据本题的特点，选择了顺序存储结构。并且用字符串数组存储数据。
*/
