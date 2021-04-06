#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<map>
#include<stack>
#include<queue>
#include<ctime>
#include<vector>
#include<set>
#include<cstdlib>
#include<utility>
using namespace std;
int a[200000+5],last,ans=0;
struct Tree{int l,r,sum1,sum2,max_v,id;}t[2000000+5];
int query1(int pos,int maxv)
{
    if (t[pos].l==t[pos].r)
    {
        if (t[pos].max_v>maxv)
            return 1;
        return 0;
    }
    if (t[pos*2].max_v>maxv)
        return t[pos].sum1-t[pos*2].sum1+query1(pos*2,maxv);
    else
        return query1(pos*2+1,maxv);
}
int query2(int pos,int maxv)
{
    if (t[pos].l==t[pos].r)
    {
        if (t[pos].max_v>maxv)
            return 1;
        return 0;
    }
    if (t[pos*2+1].max_v>maxv)
        return t[pos].sum2-t[pos*2+1].sum2+query2(pos*2+1,maxv);
    else
        return query2(pos*2,maxv);
}
void updata(int pos)
{
    if (t[pos*2].max_v>t[pos*2+1].max_v)
        t[pos].id=t[pos*2].id;
    else
        t[pos].id=t[pos*2+1].id;
    t[pos].max_v=max(t[pos*2].max_v,t[pos*2+1].max_v);
    t[pos].sum1=t[pos*2].sum1+query1(pos*2+1,t[pos*2].max_v);
    t[pos].sum2=t[pos*2+1].sum2+query2(pos*2,t[pos*2+1].max_v);
}
void Build(int Left,int Right,int pos)
{
    t[pos].l=Left;t[pos].r=Right;
    if (Left==Right)
    {
        t[pos].max_v=0;
        t[pos].sum1=t[pos].sum2=1;
        t[pos].id=Left;
        return;
    }
    int mid=(Left+Right)/2;
    Build(Left,mid,pos*2);
    Build(mid+1,Right,pos*2+1);
    updata(pos);
}
void modify(int id,int pos,int s)
{
    if (id==t[pos].l&&id==t[pos].r)
    {
        t[pos].max_v=s;
        a[id]=s;
        return;
    }
    int mid=(t[pos].l+t[pos].r)/2;
    if (id<=mid)
        modify(id,pos*2,s);
    else
        modify(id,pos*2+1,s);
    updata(pos);
}
void get_ans(int Left,int Right,int pos,int inv)
{
    if (Left<=t[pos].l&&Right>=t[pos].r)
    {
        if (inv==0)
            ans+=query1(pos,last);
        else
            ans+=query2(pos,last);
        last=max(last,t[pos].max_v);
        return;
    }
    int mid=(t[pos].l+t[pos].r)/2;
    if (inv==0)
    {
        if (mid>=Left)
            get_ans(Left,Right,pos*2,inv);
        if (mid<Right)
            get_ans(Left,Right,pos*2+1,inv);
    }
    else
    {
        if (mid<Right)
            get_ans(Left,Right,pos*2+1,inv);
        if (mid>=Left)
            get_ans(Left,Right,pos*2,inv);
    }
}
int get_min(int Left,int Right,int pos)
{
    if (Left<=t[pos].l&&Right>=t[pos].r)
        return t[pos].id;
    int mid=(t[pos].l+t[pos].r)/2,id1=0,id2=0;
    if (mid>=Left)
        id1=get_min(Left,Right,pos*2);
    if (mid<Right)
        id2=get_min(Left,Right,pos*2+1);
    if (a[id1]<a[id2])
        return id2;
    return id1;
}
int opt[200000+5],x[200000+5],y[200000+5];
map<int,int>mop;
int p[200000+5],top;
int main()
{
    int n=0,m,i,j;
    scanf("%d",&m);
    for (i=1;i<=m;i++)
    {
        scanf("%d",&opt[i]);
        if (opt[i]==1)
            scanf("%d",&x[i]);
        else
            scanf("%d%d",&x[i],&y[i]);
    }
    for (i=1;i<=m;i++)
        if (opt[i]==0)
            p[++top]=x[i];
    sort(p+1,p+top+1);
    mop[p[1]]=++n;
    for (i=2;i<=top;i++)
        mop[p[i]]=++n;
    for (i=1;i<=m;i++)
    {
        if (opt[i]==2)
            y[i]=mop[y[i]];
        x[i]=mop[x[i]];
    }
  //  printf("\n\n\n");
   // for (i=1;i<=m;i++)
 //       printf("%d %d %d\n",opt[i],x[i],y[i]);
    Build(1,n,1);
    for (i=1;i<=m;i++)
    {
        if (opt[i]==0)
            modify(x[i],1,y[i]);
        else if (opt[i]==1)
            modify(x[i],1,0);
        else
        {
            int l=x[i],r=y[i],sum=0;
            if (l>r)
                swap(l,r);
            int lca=get_min(l,r,1);
      //      printf("%d %d %d\n",l,r,lca);
            ans=1;
            last=a[l];
            if (l!=1) get_ans(1,l-1,1,1);
            last=a[l];
            if (l!=n) get_ans(l+1,n,1,0);
            sum+=ans;
            ans=1;
            last=a[r];
            if (r!=1) get_ans(1,r-1,1,1);
            last=a[r];
            if (r!=n) get_ans(r+1,n,1,0);
            sum+=ans;
            ans=1;
            last=a[lca];
            if (lca!=1) get_ans(1,lca-1,1,1);
            last=a[lca];
            if (lca!=n) get_ans(lca+1,n,1,0);
            sum-=2*ans;
            printf("%d\n",sum);
        }
    }
}
