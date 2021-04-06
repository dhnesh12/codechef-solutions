#include<bits/stdc++.h>
#define ll long long int
using namespace std;
vector<ll> pwds;
void findpwd()
{
    ll base=3141;
    double pw=(double)5/3;
    ll limit=powl(base,pw);
    ll blimit=powl(base,5);
    ll tmp=blimit;
    //cout<<blimit;
    for(ll i=2;i<=limit;i++)
    {
        ll rgh=sqrtl(i);
        if(rgh*rgh==i) continue;
        tmp=blimit;
        rgh=i*i*i;
        tmp/=(i*i*i);
        while(tmp>0)
        {
            pwds.push_back(rgh);
            tmp/=(i*i);
            if(tmp>0) rgh*=(i*i);
        }
    }
    sort(pwds.begin(),pwds.end());
    pwds.erase(unique(pwds.begin(),pwds.end()),pwds.end());
}
ll chkpopwd(ll x)
{
    if(x<4) return 0;
    ll ans1=sqrtl(x);
    ll ans2=lower_bound(pwds.begin(),pwds.end(),x)-pwds.begin();
    if(ans1*ans1==x) return ans1+ans2-1;
    if(pwds[ans2]==x) return ans1+ans2;
    return 0;
}
ll chknpopwd(ll x)
{
    if(x==0) return 2;
    ll ans1=0,ans2=0;
    ans2=lower_bound(pwds.begin(),pwds.end(),x)-pwds.begin();
    if(x>3) ans1=sqrtl(x)-1;
    ll key=x-ans1-ans2+1;
//    cout<<key<<endl;
//    cout<<(key&(-key))<<endl;
    if((key&(-key))==key) return log2l(key);
    ll l=powl(2LL,(ll)log2l(key));
    ll r=l*2LL;
    l++; r--;
    ll ans=(ll)log2l(key)+1;
    while(l<=r)
    {
        ans++;
        ll mid=(l+r)>>1;
        if(mid==key) break;
        if(key<mid) r=mid-1;
        else l=mid+1;
    }
    return ans;
}
int main()
{
    findpwd();
//    for(int i=0;i<15;i++) cout<<pwds[i]<<" ";
    int n=0; cin>>n;
    while(n--)
    {
        ll x; cin>>x;
        ll ans=chkpopwd(x);
        if(ans==0) ans=chknpopwd(x);
        cout<<ans<<" ";
    }
    cout<<endl;
    return 0;
}
