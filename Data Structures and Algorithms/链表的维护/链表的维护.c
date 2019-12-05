#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 15
typedef struct product
{
    char name[N];
    char brand[N];
    int amount;
    double price;
    struct product *next;
}PRO;
/*生成一个新的节点，并为该节点赋初值，返回指向新节点的指针*/
PRO *Createnode()
{
    PRO *p;
    p=(PRO *)malloc(sizeof(PRO));
    if(p==NULL)
    {
        printf("NO enough memory!\n");
        exit(0);
    }
    p->next=NULL;
    strcpy(p->name," ");
    strcpy(p->brand," ");
    p->amount =0;
    p->price=1;
    return p;
}
void Insertdata(PRO *head)//用于进货，同时考虑到进同一商品的问题
{
    PRO *p = head,*s = head,*q;
    p = Createnode();
    printf("请输入进货的名称、品牌、价格和数量：\n");
    scanf("%s %s %lf %d",p->name,p->brand,&p->price,&p->amount);
    if(head->next ==NULL)
    {
        head->next = p;
    }
    else
    {
        while((p->price)<(s->next->price))
        {
            s=s->next;
            if(s->next==NULL)
            {break;}
        }
        if(s->next !=NULL)
        {
            if(strcmp(p->name,s->next->name)==0&&strcmp(p->brand,s->next->brand)==0)
        {
            s->next->amount+=p->amount;
        }
        else
            {
                q = s->next;
                s->next = p;
                p->next = q;
            }
        }
        else
        {
             s->next = p;
            p->next = NULL;
        }
    }
}
void Deletedata(PRO *head)//用于提货，同时考虑到库存不够的问题
{
    PRO *q = head,*p = head,*s,*r;
    p = Createnode();
    printf("请输入取货的名称、品牌、价格、数量：\n");
    scanf("%s %s %lf %d",p->name,p->brand,&p->price,&p->amount);
    if(head->next==NULL)
    {
        printf("暂无库存！\n");
    }
    else
        {
        while(strcmp(q->next->brand,p->brand)!=0||strcmp(q->next->name,p->name)!=0)
            {
                q = q->next;
                if(q->next ==NULL)
                    {break;}
            }
        if(q->next !=NULL)
            {if(q->next->amount == p->amount)
                {
                    if(q->next->next==NULL)
                    {
                        s = q->next;
                        q->next=NULL;
                        free(s);
                    }
                    else
                    {
                        s = q->next->next;
                        r = q->next;
                        q->next = s;
                        free(r);
                    }
                }
                else
                {
                    if(q->next->amount <p->amount)
                        printf("库存不够！请重新选择操作！\n\n");
                    else
                        q->next->amount -=p->amount;
                }
                }
            else
            {
                if(p->amount==q->amount)
                {
                    free(q);
                }
                else
                q->amount -=p->amount;
            }
        }
}
void Printdata(PRO *head)//打印库存商品信息
{
    PRO *p=head->next;
    printf("名称\t品牌\t单价\t\t数量:\n");
    while(p!=NULL)
    {
        printf("%s\t%s\t%lf\t%d\n",p->name,p->brand,p->price,p->amount);
        p = p->next;
    }
    printf("\n\n");
}
void Updatedata(PRO *head)
{
    PRO *p,*q=head,*s;
    p = Createnode();
    printf("请输入变动产品的名称、品牌、现价和数量：\n");
    scanf("%s %s %lf %d",p->name,p->brand,&p->price,&p->amount);
    while(strcmp(q->next->brand,p->brand)!=0||strcmp(q->next->name,p->name)!=0)
    {
        q=q->next;
    }
    if(q->next->next==NULL)
    {
        s = q->next;
        q->next = p;
        p->next = NULL;
        free(s);
    }
    else
    {
        s = q->next;
        p->next = s->next;
        q->next = p;
        free(s);
    }
}
int Menu()
{
    int x;
    printf("家电营业系统：\n");
    printf("1.营业开始\n");
    printf("2.进货\n");
    printf("3.提货\n");
    printf("4.更新信息\n");
    printf("5.查询信息\n");
    printf("6.退出系统\n\n");
    printf("请选择你要执行的操作：\n");
    scanf("%d",&x);
    return x;
}
void Readfile(PRO *head)//从List.txt中读入数据
{
    FILE *fp;
    PRO *p=head,*q;
    q=Createnode();
    char name[N],brand[N];
    int price=0,amount=0;
    fp=fopen("List.txt","r");
    if(fp==NULL)
    {
        printf("读取文件List.txt失败！\n");
        exit(0);
    }
    fseek(fp,22,0);
    while(fscanf(fp,"%s",q->name)!=EOF)
    {
        fscanf(fp,"%s",q->brand);
        fscanf(fp,"%lf",&q->price);
        fscanf(fp,"%d\n",&q->amount);
        p->next=q;
        p=q;
        q=Createnode();
    }
    p->next=NULL;
    fclose(fp);
}
int Savefile(PRO *head)//保存数据
{
    FILE *fp;
    PRO *p=head->next;
    fp=fopen("List.txt","w");
    if(fp==NULL)
    {
        printf("写入文件List.txt失败！\n");
        return -1;
    }
    fprintf(fp,"名称\t 品牌\t 价格\t 数量\n");
    while(p!=NULL)
    {
        fprintf(fp,"%s\t %s\t %lf\t %d\n",p->name,p->brand,p->price,p->amount);
        p=p->next;
    }
    fprintf(fp,"\n");
    fclose(fp);
    return 0;
}
void Createlist(PRO *head)
{
    Readfile(head);
    printf("营业开始，请继续选择需要执行的操作：\n");
}
int main()
{
    PRO *head;
    char ch;
    head=Createnode();
    printf("注意：首次进入系统必须选择1号！\n");
    while(1)
    {
        ch = Menu();
        switch(ch)
        {
            case 1:Createlist(head);
            break;
            case 2:Insertdata(head);
            break;
            case 3:Deletedata(head);
            break;
            case 4:Updatedata(head);
            break;
            case 5:Printdata(head);
            break;
            case 6:printf("营业结束！数据已保存至文件！");
            Savefile(head);
            exit(0);
            default:printf("请输入正确序号!\n");
        }
    }
    return 0;
}
