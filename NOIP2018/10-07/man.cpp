#include<bits/stdc++.h>
#define re register
using namespace std;

struct xhb
{
    int u,v,w;
    friend bool operator < (const xhb& x, const xhb& y)
    {
        return x.w>y.w;
    }
}wzr[200010];
struct hk
{
    int  to,next,wi;
}yzp[200010];
int f[100010];
int tot;
int first[200010],book[100010];
int dep[100012];
int ff[100012][22];
int minn[100012][22];

inline int read()
{
    re int res=0;
    re bool f=1;
    re char ch=getchar();
    while (ch<'0'||ch>'9')
    {
        if(ch=='-') f=0;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        res=(res<<3)+(res<<1)+(ch&15);
        ch=getchar();
    }
    return f?res:-res;
}

inline int min(re int x,re int y)
{
    return x>y?y:x;
}

int xuanxue(re int x)//寻找祖先节点的玄学操作 
{
    /*if(f[x]==x) return x;
    else return xuanxue(f[x]);cqx dalao 要我不要这样写*/
    return f[x]==x?x:f[x]=xuanxue(f[x]);
}

void lcac(re int u,re int father)
{
    book[u]=1;
    dep[u]=dep[father]+1;
    for(register int i=0;i<20;++i)
    {
        ff[u][i+1]=ff[ff[u][i]][i];
        minn[u][i+1]=min(minn[u][i],minn[ff[u][i]][i]); 
    }
    for(register int e=first[u];e;e=yzp[e].next)
    {
        re int q=yzp[e].to;
        if(q==father) continue;
        ff[q][0]=u;
        minn[q][0]=yzp[e].wi;
        lcac(q,u);
    }
}

inline int LCA(re int x,re int y)
{
    
    if(xuanxue(x)^xuanxue(y)) return -1;
    
    int ans=0x7ffffff;
    if(dep[x]<dep[y]) swap(x,y);
    
    for(register int i=19;i^-1;--i)
    {
        if(dep[ff[x][i]]>=dep[y])
        {	
            ans=min(ans,minn[x][i]);
            x=ff[x][i];
        }
    }
    //printf("ans=%d x=%d y=%d\n",ans,x,y);
    if(x==y) return ans;
    for(register int i=19;i^-1;--i)
    {
        if(ff[x][i]^ff[y][i])
        {
            ans=min(ans,min(minn[x][i],minn[y][i]));
            x=ff[x][i];
            y=ff[y][i];
        }
    }
    //printf("ans=%d x=%d y=%d\n",ans,x,y);
    return min(ans,min(minn[x][0],minn[y][0]));
}

inline void addedge(re int u1,re int v1,re int w1)
{
    yzp[++tot].to=v1;
    yzp[tot].wi=w1;
    yzp[tot].next=first[u1];
    first[u1]=tot;
}

inline void merge(re int x,re int y)//合并节点 
{
    re int xx=xuanxue(x);
    re int yy=xuanxue(y);
    if(xx!=yy)
    {
        f[xx]=yy;
    }
}

int main()
{
    re int n,m,a,b,c,cnt=0;
    re int guaguagua=0;

    n=read();m=read();//n是点数，m为边数 
    
    for(register int i=1;i<n+1;++i)
    {
        f[i]=i;//初始化
    }
    
    for(register int i=0;i<m;++i)
    {
        a=read();b=read();c=read();
        wzr[++guaguagua].u=a;
        wzr[guaguagua].v=b;
        wzr[guaguagua].w=c;/*
        wzr[++guaguagua].u=b;//存反向的边； 
        wzr[guaguagua].v=a;
        wzr[guaguagua].w=c;*/
    }
    
    sort(wzr+1,wzr+/*2**/m+1);

    for(register int i=1;i</*2**/m+1;++i)
    {
        int uu=xuanxue(wzr[i].u);
        int vv=xuanxue(wzr[i].v);
        
        if(uu!=vv)//连接两点 
        {
            f[uu]=vv;
            addedge(wzr[i].u,wzr[i].v,wzr[i].w);
            addedge(wzr[i].v,wzr[i].u,wzr[i].w);//存图
            ++cnt;
            if(cnt==n-1) break;//一渣渣优化
        }
    }

    for(register int i=1;i<n+1;++i) 
    {
        if(!book[i]) 
        {
            lcac(i,0);
        }
    }

    re int q;
    q=read();
    
    for(register int i=0;i<q;++i)
    {
        a=read();b=read();
        re int c=LCA(a,b);

        printf("%d\n",c);
    }
    
    return 0;

}