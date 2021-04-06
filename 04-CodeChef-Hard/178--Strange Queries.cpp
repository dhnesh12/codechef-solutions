#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=400000*60,inf=1e18;
struct node
{
    int l,r,mn,mx;
    int lson,rson,cnt,dp[2][2];
    void refresh()
    {
        for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
        dp[i][j]=0;
    }
}t[maxn];
int timer;
int newNode(int l,int r)
{
    int v=++timer;
    t[v].l=l;
    t[v].r=r;
    t[v].lson=t[v].rson=t[v].cnt=0;
    return v;
}
void add(int v,int x,int d)
{
    t[v].cnt+=d;
    if(t[v].l==t[v].r)
    {
        t[v].mn=t[v].mx=x;
        t[v].dp[0][0]=t[v].dp[1][1]=-inf;
        t[v].dp[0][1]=t[v].dp[1][0]=0;
    }
    else
    {
        int c=(t[v].l+t[v].r)>>1;
        if(x<=c)
        {
            if(t[v].lson==0)
            t[v].lson=newNode(t[v].l,c);
            add(t[v].lson,x,d);
        }
        else
        {
            if(t[v].rson==0)
            t[v].rson=newNode(c+1,t[v].r);
            add(t[v].rson,x,d);
        }
        int last=-1,lson=t[v].lson,rson=t[v].rson;
        if(t[lson].cnt==0)
        last=rson;
        if(t[rson].cnt==0)
        last=lson;
        if(last!=-1)
        {
            t[v].mn=t[last].mn;
            t[v].mx=t[last].mx;
            memcpy(t[v].dp,t[last].dp,sizeof(t[v].dp));
        }
        else
        {
            t[v].mn=t[lson].mn;
            t[v].mx=t[rson].mx;
            for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
            {
                t[v].dp[i][j]=-inf;
                for(int p=0;p<2;p++)
                for(int q=0;q<2;q++)
                t[v].dp[i][j]=max(t[v].dp[i][j],t[lson].dp[i][p]+t[rson].dp[q][j]+p*q*(t[rson].mn-t[lson].mx));
            }
        }
    }
}
signed main()
{
    int tt;
    cin>>tt;
    while(tt--)
    {
        timer=0;
        int n,q;
        cin>>n>>q;
        for(int i=1;i<=(n<<2);i++)
        {
            t[i].l=t[i].r=t[i].mn=t[i].mx=t[i].cnt=0;
            t[i].refresh();
        }
        //node root;
        newNode(0,inf);
        while(n--)
        {
            int x;
            cin>>x;
            add(1,x,1);
        }
        while(q--)
        {
            int type,x;
            cin>>type>>x;
            add(1,x,3-2*type);
            int res=t[1].mx-t[1].mn-max(t[1].dp[1][1],0LL);
            cout<<res<<'\n';
        }
    }
    return 0;
}
