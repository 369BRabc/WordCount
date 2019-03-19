#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
#define Name_Max 30    //文件名最大长度
#define Word_Max 60    //每个单词最大长度

typedef struct word        //连表 单词结构
{
    char w[Word_Max];    //单词
    int count;                //个数
    struct word *next;
}link;

link *head=NULL;    //连表头
FILE *fp;            //文件指针
int count=0;

int isnotWord(char a)        //判断是否为字母
{
    if(a <= 'z' && a >= 'a')
    {
        return 0;
    }
    else if(a <= 'Z' && a >= 'A')
    {
        return 0;
    }
    else
        return 1;
}

void addWord(char *w1)        //添加单词
{
    link *p1,*p2;
    if(w1[0] <= 'Z' && w1[0] >= 'A')    //转成小写字母
    {
        w1[0]+=32;
    }
    for(p1=head;p1!=NULL;p1=p1->next)    //判断单词在连表中是否存在
    {
        if(!strcmp(p1->w,w1))
        {
            p1->count++;            //存在就个书加1
            return;
        }
    }
                                    
    p1=(struct word *)malloc(sizeof(word));//不存在添加新单词
    strcpy(p1->w,w1);
    p1->count=1;
    p1->next=NULL;
    count++;

    if(head==NULL)
    {
        head=p1;
    }
    else
    {
        for(p2=head;p2->next!=NULL;p2=p2->next);
        p2->next=p1;
    }
}

void wordCount()    //统计单词
{
    int i=0,j=0;
    char word[Word_Max],c;
    while(!feof(fp))
    {
        fscanf(fp,"%c",&c);
        if(isnotWord(c))
        {
            word[j]='\0';
            if(j>0)
            {
                addWord(word);
            }
            j=0;
        }
        else
        {
            word[j]=c;
            j++;
        }
        i++;
    }
}

void readWord()        //读取文件中的单词
{
    char name[Name_Max];
    printf("请输入要读取的单词文件名[如：test.txt]：");
    scanf("%s",name);
    getchar();
    fp=fopen(name,"r");
    wordCount();
    fclose(fp);
}

void showWord(int a,int b)        //显示单词统计情况
{
    link *p;
    printf("个数\t单词\n");
    for(p=head;p!=NULL;p=p->next)
    {
        if((p->count > a)&&(p->count < b))
            printf("%d\t%s\n",p->count,p->w);
    }
}

int main()
{
    readWord();
    int a,b;
    printf("请输入阈值a和b[如：2 10]：");
    scanf("%d %d",&a,&b);
    getchar();
    showWord(a,b);
    getchar();
}