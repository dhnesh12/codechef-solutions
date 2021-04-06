#include<bits/stdc++.h>
using namespace std;
#define pi pair<int,int>
#define f first
#define s second
const int maxn=1e6+100;
int a[maxn];
vector<pair<int,pi>> ins;
bool f=0;
int check(int l,int r,int d)
{
    if(l==r)
    return 1;
    int lmn=(1<<30),lmx=-1,rmn=(1<<30),rmx=-1;
    int mxv=r-l+1;
    for(int it1=l,it2=r,cnt=0;cnt<(r-l+2)/2 and !f and it1<r and it2>l;it1++,it2--)
    {
        lmn=min(lmn,a[it1]-d);
        lmx=max(lmx,a[it1]-d);
        rmn=min(rmn,a[it2]-d);
        rmx=max(rmx,a[it2]-d);
        if(lmn==1 and lmx-lmn==it1-l)
        ins.push_back({1,{check(l,it1,d),check(it1+1,r,d+it1-l+1)}});
        else if(rmn==1 and rmx-rmn==r-it2)
        ins.push_back({2,{check(l,it2-1,d+r-it2+1),check(it2,r,d)}});
        else if(lmx==mxv and lmx-lmn==it1-l)
        ins.push_back({2,{check(l,it1,d+r-it1),check(it1+1,r,d)}});
        else if(rmx==mxv and rmx-rmn==r-it2)
        ins.push_back({1,{check(l,it2-1,d),check(it2,r,d+it2-l)}});
        else
        continue;
        return 1+ins.size();
    }
    f=1;
    return 0;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        cin>>a[i];
        ins.clear();
        f=0;
        check(1,n,0);
        if(f)
        cout<<"NO\n";
        else
        {
            cout<<"YES\n";
            cout<<ins.size()<<'\n';
            for(auto& xx:ins)
            cout<<xx.s.f<<' '<<xx.s.s<<' '<<xx.f<<'\n';
        }
    }
    return 0;
}
