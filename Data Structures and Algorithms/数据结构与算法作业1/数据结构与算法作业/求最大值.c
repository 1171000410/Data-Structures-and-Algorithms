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
  本题可以采用的存储结构有顺序结构或链表。
  对比两种存储结构：1.链表存储结构的内存地址不一定是连续的，但顺序存储结构的内存地址一定是连续的；
  2.链式存储适用于在较频繁地插入、删除、更新元素时，而顺序存储结构适用于频繁查询时使用。
  综合来看，采用顺序结构的数组存储更加方便。
*/
