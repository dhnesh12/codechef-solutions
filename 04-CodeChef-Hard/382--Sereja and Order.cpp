#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
#define pi pair<int,int>
#define rep(i,n) for(int i=1;i<=n;i++)
const int mod=1e9+7,nax=2e5+100;
struct node{
    int a,b,id,ta,tb;
}e[nax];
bool cmp(const node& aa,const node& bb){
    return aa.b<bb.b;
}
int n,total,sum,ans;
pi res[nax];
void solve()
{
    sum=ans=total=0;
    cin>>n;
    rep(i,n){
        cin>>e[i].a>>e[i].b;
        sum+=e[i].a;
        ans+=e[i].b;
        e[i].id=i;
    }
    int tt=max(ans,sum);
    int ok=0;
    rep(i,n)
    ok=max(ok,e[i].a+e[i].b);
    cout<<(total=max(ok,tt))<<'\n';
    if(ok>=tt){
        int x=0;
        rep(i,n)
        if(e[i].a+e[i].b==ok)
        x=i;
        res[x].f=0;
        int cur=e[x].a;
        rep(i,n)
        if(i!=x){
            res[i].f=cur;
            cur+=e[i].a;
        }
        cur=0;
        rep(i,n)
        if(i!=x){
            res[i].s=cur;
            cur+=e[i].b;
        }
        res[x].s=e[x].a;
        rep(i,n)
        cout<<res[i].f<<' '<<res[i].s<<'\n';
        return;
    }
    int f=0;
    if(sum<ans){
        swap(sum,ans);
        rep(i,n)
        swap(e[i].a,e[i].b);
        f=1;
    }
    sort(e+1,e+n+1,cmp);
    int ptr=0,x=0,y=0;
    while(ptr<=n and max(x+e[ptr].a,y)+e[ptr].b<=sum){
        x+=e[ptr].a;
        y=max(x,y)+e[ptr].b;
        ptr++;
    }
    y=sum;
    for(int i=ptr-1;i;i--){
        y-=e[i].b;
        e[i].tb=y;
    }
    y=0;
    for(int i=ptr;i<=n;i++){
        e[i].tb=y;
        y+=e[i].b;
    }
    x=0;
    rep(i,n){
        e[i].ta=x;
        x+=e[i].a;
    }
    if(f){
        rep(i,n)
        {
            swap(e[i].ta,e[i].tb);
            swap(e[i].a,e[i].b);
        }
    }
    rep(i,n){
        res[e[i].id]=make_pair(e[i].ta,e[i].tb);
    }
    rep(i,n){
        cout<<res[i].f<<' '<<res[i].s<<'\n';
    }
}
int32_t main()
{
    int t=1;
    cin>>t;
    while(t--)
    solve();
    return 0;
}