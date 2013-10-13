#include "atype.h"
#include <stdio.h>
const int shifti[4]={1,-1,0,0};
const int shiftj[4]={0,0,1,-1};
int father2g[N*M];
struct link
{
    int s,t;
    struct link * next;
};
int shifter,totalmax=-10000;
int chosen[1024]={-1},holychosen[1024];
int m,n,holysum;
int a[1024],w[1024];
int father[N][M];
int value[1024];
int num=0;
struct link *g[1024];
int visited[1024]={0};
char h[1024][1024];
int q[1024],available[1024],topq;
int fatherfind(int x,int y)
{
    int result;
    result = x*m+y;
    if (father[x][y]!=x*m+y)
    {
        result = fatherfind(father[x][y]/m,father[x][y]%m);
        father[x][y] = result;
    }
    return result;
}
void setgraph(int vertical,int horizontal)
{
    int i1,j1,i,j,yes;
    struct link * p;
    num=0;
    for (i=0;i<n;i++){for (j=0;j<m;j++){father[i][j]=i*m+j;}}
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            h[i][j]=0;
            father2g[i*m+j]=-1;
            if (a[i*m+j]>=0)
            {
                if (i>0&&a[(i-1)*m+j]>=0){father[fatherfind(i,j)/m][fatherfind(i,j)%m]=father[fatherfind(i-1,j)/m][fatherfind(i-1,j)%m];}
                if (i==0&&a[(n-1)*m+j]>=0&&vertical){father[fatherfind(i,j)/m][fatherfind(i,j)%m]=father[fatherfind(n-1,j)/m][fatherfind(n-1,j)%m];}
                if (j>0&&a[i*m+j-1]>=0){father[fatherfind(i,j)/m][fatherfind(i,j)%m]=father[fatherfind(i,j-1)/m][fatherfind(i,j-1)%m];}
                if (j==0&&a[i*m+m-1]>=0&&horizontal){father[fatherfind(i,j)/m][fatherfind(i,j)%m]=father[fatherfind(i,m-1)/m][fatherfind(i,m-1)%m];}
            }
        }
    }
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            if (a[i*m+j]>0)
            {
                if (father2g[fatherfind(i,j)]==-1)
                {
                    father2g[fatherfind(i,j)]=num;
                    value[num]=a[i*m+j];
                    g[num]=NULL;
                    num++;
                }
                else{value[father2g[fatherfind(i,j)]]+=a[i*m+j];}
            }
            else
            {
                value[num]=a[i*m+j];
                father2g[i*m+j]=num;
                g[num]=NULL;
                num++;
            }
        }
    }
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            for (shifter=0;shifter<4;shifter++)
            {
                i1=i+shifti[shifter];
                j1=j+shiftj[shifter];
                if (i1<0||i1>=n)
                {
                    if (vertical) {i1=(i1+n)%n;}
                    else {continue;}
                }
                if (j1<0||j1>=m)
                {
                    if (horizontal) {j1=(j1+m)%m;}
                    else {continue;}
                }
                p=g[father2g[fatherfind(i,j)]];
                yes=1;
                while (p!=NULL)
                {
                    if (p->t==father2g[fatherfind(i1,j1)])
                    {
                        yes=0;
                        break;
                    }
                    p=p->next;
                }
                if (yes)
                {
                    p=(struct link*)malloc(sizeof(struct link));
                    p->next=g[father2g[fatherfind(i,j)]];
                    p->t=father2g[fatherfind(i1,j1)];
                    p->s=value[p->t]>=0?1:0;
                    g[father2g[fatherfind(i,j)]]=p;
                }
            }
        }
    }
    printG();
}
void printG()
{
    int i;
    struct link * p;
    for (i=0;i<num;i++)
    {
        p=g[i];
        printf("%d:%d\n",i,value[i]);
        while (p!=NULL)
        {
            printf("%d ",p->t);
            p=p->next;
        }
        printf("\n");
    }
}
void printS()
{
    int i;
    for (i=0;i<num;i++)
    {
        printf("%d %d\n",i,chosen[i]);
    }
    printf("\n");
}
int estimate(int v)
{
    int result=value[v];
    struct link * p;
    p=g[v];
    while (p!=NULL)
    {
        if (!visited[p->t]){result=value[p->t]>0?value[p->t]+result:result;}
        p=p->next;
    }
    return result;
}
int expand(int v)
{
    struct link * p;
    int t;
    int result;
    result=value[v];
    p=g[v];
    visited[v]=1;available[v]=0;
    t=0;
    while (p!=NULL)
    {
        if (!visited[p->t])
        {
            if (value[p->t]<0){available[p->t]=1;}
            else{visited[p->t]=1;result+=value[p->t];}
        }
        p=p->next;
    }
    return result;
}
void pseudoexpand(int v)
{
    struct link * p;
    int i;
    for (i=0;i<1024;i++)
    {
        chosen[i] = visited[i];
    }
    chosen[v]=1;
    p=g[v];
    while (p!=NULL)
    {
        if (value[p->t]>=0){chosen[p->t]=1;}
        p=p->next;
    }

}
void SAA(int v,float T,float r,float Tmin)
{
    int i,max,maxS=0,ranS,tmp,SMR,sum,ri,j;//State
    struct link * p;
    srand(time(0));
    sum=value[v];
    for(i=0;i<1024;i++){visited[i]=0;available[i]=0;}
    topq=0;p=g[v];visited[v]=1;
    while (p!=NULL)
    {
        if (!visited[p->t]){available[p->t]=1;}
        p=p->next;
    }
    while(1)
    {
        max=-10000000;
        ri=0;
        for (i=0;i<num;i++)
        {
            if (visited[i]) {continue;}
            if (available[i])
            {
                tmp=estimate(i);
                if (tmp>max)
                {
                    max=tmp;
                    maxS=i;
                }
                ri++;
            }
        }
        if (ri==0) {break;}
        ranS=rand()%ri+1;
        for (i=0;i<num;i++)
        {
            if (available[i]&&!visited[i])
            {
                ranS--;
                if (ranS==0)
                {
                    ranS=i;
                    break;
                }
            }
        }
        if (visited[ranS]||!available[ranS]) {return ;}
        SMR=0;
        tmp=estimate(maxS);
        if (sum+tmp>totalmax) {totalmax=sum+tmp;pseudoexpand(maxS);}
        if (tmp>0){SMR=1;}
        else
        {
            if (exp(tmp/T)>(rand()%10000)/10000.0){SMR=1;}
        }
        T*=r;
        tmp=SMR==1?estimate(maxS)-estimate(ranS):estimate(ranS);

        if (sum+estimate(ranS)>totalmax) {totalmax=sum+estimate(ranS);pseudoexpand(ranS);}
        if (exp(tmp/T)>(rand()%10000)/10000.0){SMR=2;}
        T*=r;
        switch(SMR)
        {
            case 1:sum+=expand(maxS);break;
            case 2:sum+=expand(ranS);break;
        }
        if (T<Tmin){break;}
        if (sum>totalmax) {totalmax=sum;printf("%d\n",totalmax);for (j=0;j<1024;j++){chosen[j]=visited[j];}}
    }
}
struct link * DFS(int v)
{
    struct link * p;
    struct link * q;
    struct link * tmp;
    int result=-100000;
    p = g[v];
    visited[v] = 1;
    q = (struct link *)malloc(sizeof(struct link));
    q->next = NULL;q->s = value[v];q->t = v;
    while (p!=NULL)
    {
        //printf("%d %d %d\n",p->t,visited[p->t],chosen[p->t]);
        if (chosen[p->t])
        {
            visited[v] = 0;
            q->next = NULL;q->s = value[v];q->t = v;
            return q;
        }
        if (visited[p->t]||value[p->t]>0)
        {
            p=p->next;
            continue;
        }
        if (value[p->t]<0&&!chosen[p->t])
        {
            tmp = DFS(p->t);
            if (tmp!=NULL&&result<tmp->s+value[v])
            {
                result = tmp->s+value[v];
                q->next = tmp;
                q->s=tmp->s+value[v];
            }
        }
        p = p->next;
    }
    visited[v] = 0;
    if (q->next!=NULL) return q;
    return NULL;
}
void patch()
{
    int i,j,sum,yes;
    struct link * p,*q;
    while(1)
    {
        yes = 0;
        for (i=0;i<num;i++)
        {
            if (value[i]>0&&!chosen[i])
            {
                for (j=0;j<1024;j++) {visited[j]=0;}
                q = DFS(i);
                p = q;
                if (p==NULL)
                {
                    continue;
                }
                sum = p->s;
                if (sum>=0)
                {
                    yes = 1;
                    while (q!=NULL)
                    {
                        chosen[q->t] = 1;
                        q = q->next;
                    }
                }
            }
        }
        if (yes==0) {break;}
    }
}
int deal(int o,int p,int c[],int vertical,int horizontal)
{
    int i,j,z;
    float x=100;
    m=p;
    n=o;
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            a[i*m+j]=c[i*m+j];
        }
    }
    setgraph(vertical,horizontal);
    holysum = 0;
    for(z=0;z<5;z++)
    {
        for (i=0;i<num;i++)
    	{
    	    if (value[i]>0)
    	    {
    	        x=20000;
    	        for (j=0;j<num*1000;j++)
    	        {
    	            x*=0.5;
    	            SAA(i,x,0.99,0.00001);
    	        }
    	    }
    	}
    	patch();
    	totalmax = 0;
    	for (i=0;i<num;i++)
    	{
    	    if(chosen[i])
    	    {
    	        totalmax+=value[i];
    	    }
    	}
    	if (totalmax>holysum)
        {
            holysum = totalmax;
            for (i=0;i<num;i++)
            {
                holychosen[i] = chosen[i];
            }
        }
    }
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            if (holychosen[father2g[fatherfind(i,j)]])
            {
                c[i*m+j]=-10001;
            }
        }
    }
    return holysum;
}
int main()
{
    int m,n,i,a,v,h;
    int c[1024];
    FILE * fin =  fopen("input.txt","r");
    fscanf(fin,"%d%d%d%d%d",&m,&n,&a,&v,&h);
    for (i=0;i<m*n;i++)
    {
        fscanf(fin,"%d",&c[i]);
    }
    printf("%d",deal(m,n,c,v,h));
    return 0;
}
