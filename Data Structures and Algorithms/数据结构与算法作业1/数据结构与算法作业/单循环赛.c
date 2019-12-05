#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 5
typedef struct player
{
    char name[MAX_LEN];
    int score;
}PLAYER;
int main()
{
    int n,i,j,k,temp;
    char t,s[MAX_LEN];
    printf("How many players?\n");
    scanf("%d",&n);
    PLAYER player[n];
    printf("Input player's name:\n");
    for(i=0;i<n;i++)
    {
        scanf("%s",player[i].name);
        player[i].score=0;
    }
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            printf("Please input match results between %s and %s:(w=win,l=lose)\n",player[i].name,player[j].name);
            getchar();
            scanf("%c",&t);
            if(t=='w')
                {
                    player[i].score++;
                    player[j].score--;
                }
            else if(t=='l')
                {
                    player[i].score--;
                    player[j].score++;
                }
            else
                {
                    printf("Please input correct results:\n");
                    j--;
                }
        }
    }
    for(i=0;i<n-1;i++)
    {
        k=i;
        for(j=i+1;j<n;j++)
        {
            if(player[j].score>player[i].score)
                k=j;
        }
        if(k!=i)
        {
            temp=player[i].score;
            player[i].score=player[k].score;
            player[k].score=temp;
            strcpy(s,player[i].name);
            strcpy(player[i].name,player[k].name);
            strcpy(player[k].name,s);
        }
    }
    printf("The new order by score is:\n");
    for(i=0;i<n;i++)
    {
        printf("%s  %d\n",player[i].name,player[i].score);
    }
    return 0;
}
