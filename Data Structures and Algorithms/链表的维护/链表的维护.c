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
/*����һ���µĽڵ㣬��Ϊ�ýڵ㸳��ֵ������ָ���½ڵ��ָ��*/
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
void Insertdata(PRO *head)//���ڽ�����ͬʱ���ǵ���ͬһ��Ʒ������
{
    PRO *p = head,*s = head,*q;
    p = Createnode();
    printf("��������������ơ�Ʒ�ơ��۸��������\n");
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
void Deletedata(PRO *head)//���������ͬʱ���ǵ���治��������
{
    PRO *q = head,*p = head,*s,*r;
    p = Createnode();
    printf("������ȡ�������ơ�Ʒ�ơ��۸�������\n");
    scanf("%s %s %lf %d",p->name,p->brand,&p->price,&p->amount);
    if(head->next==NULL)
    {
        printf("���޿�棡\n");
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
                        printf("��治����������ѡ�������\n\n");
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
void Printdata(PRO *head)//��ӡ�����Ʒ��Ϣ
{
    PRO *p=head->next;
    printf("����\tƷ��\t����\t\t����:\n");
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
    printf("������䶯��Ʒ�����ơ�Ʒ�ơ��ּۺ�������\n");
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
    printf("�ҵ�Ӫҵϵͳ��\n");
    printf("1.Ӫҵ��ʼ\n");
    printf("2.����\n");
    printf("3.���\n");
    printf("4.������Ϣ\n");
    printf("5.��ѯ��Ϣ\n");
    printf("6.�˳�ϵͳ\n\n");
    printf("��ѡ����Ҫִ�еĲ�����\n");
    scanf("%d",&x);
    return x;
}
void Readfile(PRO *head)//��List.txt�ж�������
{
    FILE *fp;
    PRO *p=head,*q;
    q=Createnode();
    char name[N],brand[N];
    int price=0,amount=0;
    fp=fopen("List.txt","r");
    if(fp==NULL)
    {
        printf("��ȡ�ļ�List.txtʧ�ܣ�\n");
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
int Savefile(PRO *head)//��������
{
    FILE *fp;
    PRO *p=head->next;
    fp=fopen("List.txt","w");
    if(fp==NULL)
    {
        printf("д���ļ�List.txtʧ�ܣ�\n");
        return -1;
    }
    fprintf(fp,"����\t Ʒ��\t �۸�\t ����\n");
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
    printf("Ӫҵ��ʼ�������ѡ����Ҫִ�еĲ�����\n");
}
int main()
{
    PRO *head;
    char ch;
    head=Createnode();
    printf("ע�⣺�״ν���ϵͳ����ѡ��1�ţ�\n");
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
            case 6:printf("Ӫҵ�����������ѱ������ļ���");
            Savefile(head);
            exit(0);
            default:printf("��������ȷ���!\n");
        }
    }
    return 0;
}
