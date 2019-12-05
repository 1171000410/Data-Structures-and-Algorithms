#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
typedef struct //�������ŵĽṹ��
{
    char c;  //�ַ�
    unsigned int count;  //���ִ���
    unsigned char huffcode[300]  //����
}struct_symbol;

typedef struct  //�ļ��ַ��Ľṹ��
{
   struct_symbol symbol_array[128];  //�����ַ�
   unsigned char number;  //�ַ��������
}struct_file;

typedef struct node //����������̬��������
{
    struct_symbol symbol;
    int lchild;
    int rchild;
    int parent;
}HTNODE;

struct_file symbol_file;

void InitHT(HTNODE *HT)  //��ʼ��
{
    for(int i=0;i<(2*symbol_file.number-1);i++)
    {
        HT[i].lchild=-1;
        HT[i].rchild=-1;
        HT[i].parent=-1;
    }
}

void Input(HTNODE *HT)  //����Ҷ�ڵ�Ȩֵ
{
    for(int i=0;i<symbol_file.number;i++)
    {
        HT[i].symbol.c = symbol_file.symbol_array[i].c;
        HT[i].symbol.count = symbol_file.symbol_array[i].count;
    }
}

void SelectMin(HTNODE *HT,int n,int *p1,int *p2)  //��������СȨֵ
{
    int i,j;
    for(i=0;i<=n;i++)
        if(HT[i].parent==-1)
    {
        *p1 = i;
        break;
    }
    for(j=i+1;j<=n;j++)
        if(HT[j].parent==-1)
    {
        *p2 = j;
        break;
    }
    for(i=0;i<=n;i++)
        if((HT[*p1].symbol.count>HT[i].symbol.count)&&(HT[i].parent=-1)&&(*p2!=i))
        *p1=i;
    for(j=0;j<=n;j++)
        if((HT[*p2].symbol.count>HT[j].symbol.count)&&(HT[j].parent=-1)&&(*p1!=j))
        *p2=j;
}

void ReadCompress()   //�����ѹ���ļ�
{
    FILE *fp;
    char ch;
    int flag,i,counter=0;
    fp=fopen("Compress_read.txt","rb");
    if(fp==NULL)
    {
        printf("Compress_read.txt can not be read!\n");
        exit(0);
    }
    printf("�ɹ������ѹ���ļ���\n\n");
    symbol_file.number = 0;
    while(1)    //�����ļ���ͳ�Ƹ��ַ�����
    {
        fscanf(fp,"%c",&ch);
        counter++;
        flag = 0;
        if(ch=='#')
            break;
        /*if(ch=='\r')
            continue;*/
        for(i=0;i<symbol_file.number;i++)
        {
            if(ch ==symbol_file.symbol_array[i].c)
            {
                symbol_file.symbol_array[i].count++;
                flag = 1;
                break;
            }
        }
        if(!flag)
        {
            symbol_file.symbol_array[symbol_file.number].c = ch;
            symbol_file.symbol_array[symbol_file.number].count = 1;
            symbol_file.number++;
        }
    }
    fclose(fp);
    for(int i=0;i<symbol_file.number;i++)
        printf("�ַ�%c    ���ִ���%d\n",symbol_file.symbol_array[i].c\
               ,symbol_file.symbol_array[i].count);
    printf("\n��ѹ���ļ����ֽ���Ϊ��%d\n",counter);
}

void CreatHT(HTNODE *HT)
{
    int i,p1,p2;
    InitHT(HT);
    Input(HT);
    for(i=symbol_file.number;i<(2*symbol_file.number-1);i++)
    {
        SelectMin(HT,i-1,&p1,&p2);
        HT[p1].parent = HT[p2].parent = i;
        HT[i].lchild = p1;
        HT[i].rchild = p2;
        HT[i].symbol.count = HT[p1].symbol.count + HT[p2].symbol.count;
        HT[p1].symbol.count = INT_MAX;  //����Ǹô����ʹ���
        HT[p2].symbol.count = INT_MAX;
    }
}

void HuffmanEncoding(HTNODE *HT)  //���벢�浽symbol.huffcode��
{
    int c,p,i,j;
    int start;
    for(i=0;i<symbol_file.number;i++)  //��ʼ��
        for(j=0;j<300;j++)
    {
        HT[i].symbol.huffcode[j] ='\0';
    }
    for(i=0;i<symbol_file.number;i++)
    {
        c = i;
        start = symbol_file.number;
        while((p=HT[c].parent)>=0)
        {
            HT[i].symbol.huffcode[--start] = (HT[p].lchild==c)?'0':'1';
            c = p;  //��������
        }
    }
}

void WriteCompress(HTNODE *HT)  //ѹ����д���ļ�
{
    FILE *fp_read,*fp_write;
    unsigned char ch,buffer=0;
    int i,j,index=7,counter=0;
    fp_read=fopen("Compress_read.txt","rb");
    fp_write=fopen("Compress_write.txt","wb");
    if(fp_read==NULL)
    {
        printf("�����ļ�Compress_read.txtʧ�ܣ�\n");
        return -1;
    }
    if(fp_write==NULL)
    {
        printf("д���ļ�Compress_write.txtʧ�ܣ�\n");
        return -1;
    }
    while(1)
    {
        fscanf(fp_read,"%c",&ch);
        if(ch=='#')
        {
            fprintf(fp_write,"%c",buffer);
            counter++;
            break;
        }
        /*if(ch=='\r')
            continue;*/
        for(i=0;i<symbol_file.number;i++)
        {
            if(HT[i].symbol.c==ch)
            {
                for(j=0;j<300;j++)
                    if(HT[i].symbol.huffcode[j]!='\0')
                    {
                        buffer |=(HT[i].symbol.huffcode[j]-'0')<<index;
                        index--;
                        if(index==-1)
                        {
                            fprintf(fp_write,"%c",buffer);
                            buffer = 0;
                            index = 7;
                            counter++;
                        }
                    }
            }
        }
    }
    printf("�ļ��ѳɹ�ѹ����\n\n");
    printf("ѹ���ļ����ֽ���Ϊ%d\n",counter);
    fclose(fp_write);
    fclose(fp_read);
}

void Decompress(HTNODE *HT)  //��ѹ�ļ�
{
    unsigned char ch;
    FILE *fp_read,*fp_write;
    int i,j,index,count,child,parent;
    printf("\n��ѹ�����ַ�������%d\n",HT[(2*symbol_file.number-2)].symbol.count);
    fp_read=fopen("Compress_write.txt","rb");
    fp_write=fopen("Decompress_write.txt","wb");
    if(fp_read==NULL)
    {
        printf("�����ļ�Compress_write.txtʧ�ܣ�\n");
        return -1;
    }
    if(fp_write==NULL)
    {
        printf("д���ļ�Decompress_write.txtʧ�ܣ�\n");
        return -1;
    }
    index = 7;  //��ʼƫ����
    parent =2*symbol_file.number-2;  //����λ��
    count = HT[parent].symbol.count;  //�ַ�����
    while(1)
    {
        fscanf(fp_read,"%c",&ch);
        index = 7;
        while(index!=-1)
        {
            if(((ch>>index)&1)==0)
                child = HT[parent].lchild;
            else
                child = HT[parent].rchild;
            if(HT[child].lchild<0&&HT[child].rchild<0)  //Ҷ�ڵ�
            {
                fprintf(fp_write,"%c",HT[child].symbol.c);
                parent =2*symbol_file.number-2;
                count --;
            }
            else
                parent = child;
            index--;
            if(count ==0)
            {
                printf("�ļ��ѳɹ���ѹ��\n");
                fclose(fp_write);
                fclose(fp_read);
                return;
            }
        }
    }
}

int main()
{
    HTNODE *HT;
    ReadCompress();
    HT=(HTNODE*)malloc((2*symbol_file.number-1)*sizeof(HTNODE));
    CreatHT(HT);
    HuffmanEncoding(HT);
    WriteCompress(HT);  //ѹ��
    Decompress(HT); //�ļ���ѹ��
    return 0;
}
