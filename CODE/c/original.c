#include "original.h"
int x1,y1,x2,y2;
int maxsumline(int *p,int size)
{
    int i;
    int sum,ans,tmp=0;
    sum=0;
    ans=-1000000;
    for(i=0;i<size;i++)
    {
        if(sum<0){sum=0;tmp=i;}
        sum+=p[i];
        if(ans<sum){ans=sum;y1=tmp;y2=i;}
    }
    return ans;
}
int maxsumcycle(int *p,int size)
{
    int i;
    int sum,ans,tmp,tmp1;
    sum=0;
    ans=maxsumline(p,size);
    for (i=0;i<size;i++)
    {
        sum+=p[i];
        p[i] = -p[i];
    }
    if ((tmp=(sum+maxsumline(p,size)))>ans)
    {
        tmp1=y1;
        y1=(y2+1)%size;
        y2=(tmp1-1+size)%size;
        printf("%d %d %d %d\n",x1,x2,y1,y2);
        for (i=0;i<size;i++)
        {
            sum+=p[i];
            p[i] = -p[i];
        }
        return tmp;
    }
    else
    {
        for (i=0;i<size;i++)
        {
            sum+=p[i];
            p[i] = -p[i];
        }
        maxsumline(p,size);
        return ans;
    }
}
int maxsumblock(int a[],int n,int m,int cycle,int expand)
{
    int i,j,k,tmp,totalmax=0,start;
    int sum[32][32];
    int t[32];
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            if (i!=0)
            {
                sum[i][j]=sum[i-1][j]+a[i*m+j];
            }
            else
            {
                sum[i][j]=a[i*m+j];
            }
        }
    }
    for (i=0;i<n;i++)
    {
        for (j=0;j<=i;j++)
        {
            for (k=0;k<m;k++)
            {
                t[k] = (j==0)?0:-sum[j-1][k];
                t[k] +=sum[i][k];
            }
            tmp = cycle?maxsumcycle(t,m):maxsumline(t,m);
            if (maxsumline(t,m)>tmp) {tmp=maxsumline(t,m);}
            if (tmp>totalmax)
            {
                totalmax= tmp;
                x1=j;x2=i;
            }
            if (expand)
            {
                for (k=0;k<m;k++)
                {
                    t[k]=sum[n-1][k]-sum[i][k]+sum[j][k];
                }
                tmp = cycle?maxsumcycle(t,m):maxsumline(t,m);
                if (tmp>totalmax)
                {
                    totalmax= tmp;
                    x1=i+1;x2=j;
                }
            }
        }
    }
    for (k=0;k<m;k++)
    {
        tmp=0;
        for (i=x1;;i=(i+1)%n)
        {
            tmp+=a[i*m+k];
            if (i==x2) {break;}
        }
        t[k]=tmp;
    }
    tmp = maxsumline(t,m);
    if (cycle)
    {
        if (maxsumcycle(t,m)>tmp)
        {
            tmp=maxsumcycle(t,m);
        }
        else
        {
            maxsumline(t,m);
        }

    }
    for (i=x1;;i=(i+1)%n)
    {
        for (j=y1;;j=(j+1)%m)
        {
            a[i*m+j]=-10001;
            if (j==y2) {break;}
        }
        if (i==x2) {break;}
    }
    return totalmax;
}
int main()
{
    int a[6]={1,-2,3,1,-2,3},i;
    printf("%d\n",maxsumblock(a,2,3,0,1));
    for (i=0;i<6;i++)
    {
        printf("%d ",a[i]);
    }
}
