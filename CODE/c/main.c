#include "original.h"
#include <string.h>
#include <stdio.h>
int m,n,a[1024];
void init(int p)
{
    int i,j;
    FILE * fin;
    char t[10];
    t[0]=p+48;
    t[1]=0;
    strcat(t,"input.txt");
    fin = fopen(t,"r");
    fscanf(fin,"%d%d",&n,&m);
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            fscanf(fin,"%d",&a[i*m+j]);
        }
    }
}
int main(int argc,char * argv[])
{
    int i,p,j,cycle=0,expand=0,amorphous=0;
    for (i=1;i<argc;i++)
    {
        printf("%s\n",argv[i]);
        if (argv[i][1]=='v')
        {
            expand=1;
        }
        if (argv[i][1]=='h')
        {
            cycle=1;
        }
        if (argv[i][1]='a')
        {
            amorphous=1;
        }
    }
    printf("%d\n",expand);
    for (p=0;p<1;p++)
    {
        init(p);
        printf("%d\n",maxsumblock(a,n,m,cycle,expand));
        for (i=0;i<n;i++)
        {
            for (j=0;j<m;j++)
            {
                printf("%d ",a[i*m+j]);
            }
            printf("\n");
        }
    }

    return 0;
}
