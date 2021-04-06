/*
not my solution.
code reference:https://www.codechef.com/viewsolution/8788799(waterfalls)
learn about 
1. treaps
   -https://tanujkhattar.wordpress.com/2016/01/10/treaps-one-tree-to-rule-em-all-part-1/
   -https://tanujkhattar.wordpress.com/2016/01/10/treaps-one-tree-to-rule-em-all-part-2/
   -https://jeffe.cs.illinois.edu/teaching/algorithms/notes/03-treaps.pdf
   -https://faculty.washington.edu/aragon/pubs/rst96.pdf(original research paper)
   -https://dl.acm.org/doi/pdf/10.1145/2676723.2677251(the best paper which gives intuition as to why treaps height is log(n) with high probability)
   incase you want a mathematical proof u have to learn about chernoff bounds
   -http://math.mit.edu/~goemans/18310S15/chernoff-notes.pdf
   -https://people.eecs.berkeley.edu/~jfc/cs174/lecs/lec10/lec10.pdf
try to gain nice intuition
2.DSU on trees
   -https://codeforces.com/blog/entry/44351
*/      
#include<bits/stdc++.h>
#define int long long
#define N 100005
#define mod 1000000007
using namespace std;
int n,a[N],sum[N],ans[N];
vector<int>g[N];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int add(int x,int y)
{
    x=(x+y);
    if(x<0)
    x+=mod;
    if(x>=mod)
    x-=mod;
    return x;
}
int mul(int x,int y)
{
    return (1LL*x*y)%mod;
}
int inv(int x)
{
    x=(x%mod);
    int y=(mod-2);
    int res=1LL;
    while(y)
    {
        if(y&1)
        res=mul(res,x);
        x=mul(x,x);
        y=y/2;
    }
    return res;
}
// treap statisfying the max property
struct node
{
    int val,id,pr,sts,sz,lazy;
    /* val denotes the number of ways in which u can decompose the tree with value of 
       path equal to id
       sts denotes the sum of all the ways in which u can decompose the tree with value 
       of paths between s[0] to s[1]
     */  
    int s[2];//to store the range of values under this treap
    node* c[2];//left and right child
    node(int i,int v=0)
    {
        val=sts=v;
        id=s[0]=s[1]=i;
        c[0]=c[1]=0;
        pr=rng();
        lazy=-1;
        sz=1;
    }
};
node* head[N];
void give(node* x,int val)
{
    if(!x)
    return;
    if(x->lazy==-1)
    x->lazy=val;
    else
    x->lazy=mul(x->lazy,val);
}
void push(node* x)
{
    if(!x)
    return;
    if(x->lazy!=-1)
    {
        x->val=mul(x->val,x->lazy);
        x->sts=mul(x->sts,x->lazy);
        if(x->c[0])
        give(x->c[0],x->lazy);
        if(x->c[1])
        give(x->c[1],x->lazy);
        x->lazy=-1;
    }
}
void calc(node* t)
{
    if(!t)
    return;
    push(t->c[0]);
    push(t->c[1]);
    t->sts=t->val;
    t->sz=1;
    t->s[0]=t->s[1]=t->id;
    if(t->c[0])
    {
        t->sts=add(t->sts,t->c[0]->sts);
        t->sz=add(t->sz,t->c[0]->sz);
        t->s[0]=t->c[0]->s[0];
    } 
    if(t->c[1])
    {
        t->sts=add(t->sts,t->c[1]->sts);
        t->sz=add(t->sz,t->c[1]->sz);
        t->s[1]=t->c[1]->s[1];
    }
}
void modify(node* t,int k,int val)
{
    push(t);
    if(t->id==k)
    t->val=add(t->val,val);
    else if(t->id<k)
    modify(t->c[1],k,val);
    else
    modify(t->c[0],k,val);
    calc(t);
}
void split(node* t,int k,node*& l,node*& r)
{
    push(t);
    if(!t)
    {
        l=r=0;
    }
    else if(t->id<=k)
    {
        l=t;
        split(t->c[1],k,t->c[1],r);
    }
    else
    {
        r=t;
        split(t->c[0],k,l,t->c[0]);
    }
    calc(t);
}
void insert(node*& t,node* x)
{
    push(t);
    if(!t)
    t=x;
    else if(x->pr > t->pr)
    {
        split(t,x->id,x->c[0],x->c[1]);
        t=x;
    }
    else
    {
        if(x->id<t->id)
        insert(t->c[0],x);
        else
        insert(t->c[1],x);
    }
    calc(t);
}
void add(node*& t,int k,int val)
{
    if(abs(k)>1e9)
    return;
    node *f=t;
    while(true)
    {
        if(!f || f->id==k)break;
        else if(f->id<k)
        f=f->c[1];
        else
        f=f->c[0];
    }
    if(f)
    modify(t,k,val);
    else
    insert(t,new node(k,val));
}
void make(node*& t)
{
    insert(t,new node(-1.1e9));
    insert(t,new node(1.1e9));
}
int query(node* t,int v)
{
    if(!t)
    return 0;
    push(t);
    if(t->s[1]<v)
    return 0;
    if(t->s[0]>=v)
    return t->sts;
    int res=add(query(t->c[0],v),query(t->c[1],v));
    if(t->id>=v)
    res=add(res,t->val);
    return res;
}
void setup(int x,int p)
{
    if(p)
    g[x].erase(find(g[x].begin(),g[x].end(),p));
    sum[x]=a[x];
    sum[x] += sum[p];
    for(auto i:g[x])
    setup(i,x);
}
int dfsadd(node* x,node* y,int v)
{
    if(!x)
    return 0;
    push(x);
    int res=mul(x->val,query(y,2*sum[v]-a[v]-x->id));
    res=add(res,dfsadd(x->c[0],y,v));
    res=add(res,dfsadd(x->c[1],y,v));
    return res;
}
void dfsmerge(node* x,node*& y)
{
    if(!x)
    return;
    push(x);
    add(y,x->id,x->val);
    dfsmerge(x->c[0],y);
    dfsmerge(x->c[1],y);
}
void dfs(int x)
{
    for(auto i:g[x])
    dfs(i);
    int prod=1LL;
    vector<int>zeros;
    for(auto i:g[x])
    {
        if(ans[i])
        prod=mul(prod,ans[i]);
        else
        zeros.push_back(i);
    }
    if(!g[x].size())
    {
        make(head[x]);
        add(head[x],sum[x],1);
        if(a[x]>=0)
        ans[x]=1;
        return;
    }
    if(zeros.size()>2)
    {
        ans[x]=0;
        make(head[x]);
    }
    else if(zeros.size()==2)
    {
        if(head[zeros[1]]->sz>head[zeros[0]]->sz)
        ans[x]=add(ans[x],mul(prod,dfsadd(head[zeros[0]],head[zeros[1]],x)));
        else
        ans[x]=add(ans[x],mul(prod,dfsadd(head[zeros[1]],head[zeros[0]],x)));
        make(head[x]);
    }
    else if(zeros.size()==1)
    {
        ans[x]=add(ans[x],mul(prod,query(head[zeros[0]],sum[x]-a[x])));
        if(g[x].size()==1)
        {
            head[x]=head[g[x][0]];
            return;
        }
        for(int i=0;i<g[x].size();i++)
        if(g[x][i]==zeros[0])
        swap(g[x][i],g[x][0]);
        for(int i=1;i<g[x].size();i++)
        give(head[g[x][i]],inv(ans[g[x][i]]));
        head[x]=head[g[x][1]];
        for(int i=2;i<g[x].size();i++)
        {
            if(head[x]->sz<head[g[x][i]]->sz)
            swap(*head[x],*head[g[x][i]]);
            dfsmerge(head[g[x][i]],head[x]);
        }    
        give(head[x],prod);
        if(head[x]->sz>head[g[x][0]]->sz)
        ans[x]=add(ans[x],dfsadd(head[g[x][0]],head[x],x));
        else
        ans[x]=add(ans[x],dfsadd(head[x],head[g[x][0]],x));
        head[x]=head[g[x][0]];
        give(head[x],prod);
    }
    else if(zeros.size()==0)
    {
        if(a[x]>=0)
        ans[x]=prod;
        for(int i=0;i<g[x].size();i++)
        {
            give(head[g[x][i]],inv(ans[g[x][i]]));
            ans[x]=add(ans[x],mul(prod,query(head[g[x][i]],sum[x]-a[x])));
        }
        head[x]=head[g[x][0]];
        for(int i=1;i<g[x].size();i++)
        {
            if(head[x]->sz<head[g[x][i]]->sz)
            ans[x]=add(ans[x],mul(prod,dfsadd(head[x],head[g[x][i]],x)));
            else
            ans[x]=add(ans[x],mul(prod,dfsadd(head[g[x][i]],head[x],x)));
            if(head[x]->sz<head[g[x][i]]->sz)
            swap(*head[x],*head[g[x][i]]);
            dfsmerge(head[g[x][i]],head[x]);
        }
        add(head[x],sum[x],1);
        give(head[x],prod);
    }
}
void reset()
{
    for(int i=0;i<=n;i++)
    {
        sum[i]=0;
        a[i]=0;
        g[i].clear();
        ans[i]=0;
        head[i]=0;
    }
}
signed main()
{
    //ios_base::sync_with_stdio(false);
    //cin.tie(0);
    //cout.tie(0);
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int t;
    //cin>>t;
    scanf("%lld",&t);
    while(t--)
    {
        //cin>>n;
        scanf("%lld",&n);
        reset();
        for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
        for(int i=1;i<n;i++)
        {
            int x,y;
            //cin>>x>>y;
            scanf("%lld%lld",&x,&y);
            g[x].push_back(y);
            g[y].push_back(x);
        }
        setup(1,0);
        dfs(1);
        //for(int i=1;i<=n;i++)
        //cout<<ans[i]<<"  ";
        //cout<<"\n";
        printf("%lld\n",ans[1]);
    }
    return 0;
}