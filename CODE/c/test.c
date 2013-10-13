#include <stdio.h>
#include <string.h>
int main()
{
    FILE * fout;
    char s[10];
    int i,j,k,t=21318,m=233;
    for (i=0;i<10;i++)
    {
        sprintf(s,"%d",i);
        strcat(s,"input.txt");
        printf("%s",s);
        fout=fopen(s,"w");
        fprintf(fout,"32 32\n");
        for (j=0;j<32;j++)
        {
            for (k=0;k<32;k++)
            {
                m=(m*m)%t;
                if (m%10<5)
                {
                    fprintf(fout,"-");
                }
                fprintf(fout,"%d ",m);
            }
            fprintf(fout,"\n");
        }

    }


}
