HOMEWORK-03
===================================
文件介绍
-----------------------------------
在EXE文件夹中的main.exe文件为本项目执行文件直接点击即可，CODE文件夹中的C文件夹中包含了算法部分的代码，其编译出的DLL文件在bin文件夹中，另外在CODE文件夹下的python文件为本项目GUI实现，其样本XML在UI文件夹中。
项目回顾
-----------------------------------
对于HOMEWORK-02，-a的模式进行了改进，(HOMEWORK-02参见[链接](http://www.cnblogs.com/yuzuka/p/3348333.html)<br />)由于图的规模不容易控制(如果是正负间隔的数据情况则无法使用并查集缩点)：
		4 4
		1 -2 3 -4 
		-5 6 -7 8
		9 -10 11 -12
		-13 14 -15 16
所以在这里我认为很难有一个合适的算法进行-a的操作，我选择使用SAA退火算法，退火时MaxS表示当前状态下选择的最优状态，而RanS表示随意扩展的一个状态，比较这两个状态来判断是否应该选取局部优解，而在大多数情况下该退火算法会得到最优解:
		
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

退火算法详情参见[链接](http://www.sciencedirect.com/science/article/pii/089571779390204C)<br />
通过五次相同的退火过程，在每次退火过程中设置1000*V(V表示点数)次初始温度，得到一个相当优的解，其很大程度上就是最优解。
然后对于这个较优解继续进行比较简单的提升通过patch()函数。
		
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

将其余有正收益的点不断选取，得到最后的一个局部不可扩充的最优解。
本算法基于时间上的考虑进行了一部分取舍，首先理想情况下应该是通过patch()操作之后得到状态RanS与MaxS，其次patch无法对以下情况进行扩充，以下的情况必须由SAA在退火过程中选取:
		
		3 3
		4 -100 100
		-5 100 100
		4 -100 100

两个价值为4的点都无法被patch()，但由于规模小可以在SAA的过程中被挑选出来，于是仍能得到最优解。
另外-v -h参数对-a参数来说只是建图的方式有所不同。
		
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
		                if (i==0&&a[(n-1)*m+j]>=0&&vertical){father[fatherfind(i,j)/m][fatherfind(i,j)%m]=father[fatherfind(n-1,j)/m][fatherfind(n-1,j)%m		];}
		                if (j>0&&a[i*m+j-1]>=0){father[fatherfind(i,j)/m][fatherfind(i,j)%m]=father[fatherfind(i,j-1)/m][fatherfind(i,j-1)%m];}
		                if (j==0&&a[i*m+m-1]>=0&&horizontal){father[fatherfind(i,j)/m][fatherfind(i,j)%m]=father[fatherfind(i,m-1)/m][fatherfind(i,m-1)%m		];}
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
		}

GUI构架简介
-----------------------------------
出于平台兼容性考虑使用的是pythonQT的GUI形式，其中表格部分为输入部分，取一个最小的能包含所有输入部分的矩形作为输入成分，其中没有输入的部分认为输入的0，一共有两个Tab卡可以进行两个矩阵的输入操作。OK键表示根据右侧选项check后将其提交运算，标黄的为选择的部分。RESET会将所有数字清空。
项目流程
-----------------------------------
首先通过C写算法部分的代码，而GUI部分则无需要特别好的实现效率，于是便使用了PYQT的高开发效率的特性。先使用ERIC4提供的QTdesigner绘制框架再通过ERIC4向python编译，再用自己写的窗口类继承setui后，完成GUI设计流程。