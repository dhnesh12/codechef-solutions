#include<bits/stdc++.h>
#include<math.h>
#define rep(i,k,n) for(int i=k;i<n;i++)
#define ll long long
#define MOD 998244353ll
#define MOD2 1000000009ll
#define MOD3 1000000007ll
#define INF 1e16
#define MIN(a,b) (a>b?b:a)
using namespace std;
#define mp make_pair
#define pb push_back
#define  piii pair<ll,pair<ll,ll>>
#define pii pair<ll,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) \
    for ( \
        auto blockTime = make_pair(chrono::high_resolution_clock::now(), true); \
        blockTime.second; \
        debug("%s: %lld ms\n", d, chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - blockTime.first).count()), blockTime.second = false \
    )
#define MAXN 100005
ll t,n;
pii ar[MAXN],tr[4*MAXN+555];
void build(ll,ll,ll),upd(ll,ll,ll,ll);
pii query(ll,ll,ll,ll);
vector <ll> vr;
pii neg=mp(0,0);
bool comp(pii a,pii b)
{
	if(a.fi==b.fi)
	{
		return a.se>b.se;
	}
	return a.fi>b.fi;
}
int main()
{
	// freopen("input.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	scanf("%lld",&t);
	while(t--)
	{
		vr.clear();
		scanf("%lld",&n);
		rep(i,0,n)
		{
			scanf("%lld %lld",&ar[i].fi,&ar[i].se);
		}
		sort(ar,ar+n,comp);
		build(0,0,n-1);
		ll cur=0;
		while(1)
		{
			cur=0;
			pii p=query(0,0,n-1,0);
			// cout<<p.fi<<" "<<p.se<<"\n";
			ll prev_=0;
			if(p==neg)
				break;
			while(p!=neg&&p.fi>prev_)
			{
				// cout<<p.fi<<" "<<p.se<<" "<<prev_<<"\n";				
				cur++;
				upd(0,0,n-1,p.se);
				prev_=p.fi;
				// cout<<prev_<<" "<<p.fi<<"\n";
				p=query(0,0,n-1,p.fi);
				// cout<<p.fi<<" "<<p.se<<"\n";
			}
			// cout<<"FG";
			vr.pb(cur);
		}
		// ll tot=0;
		printf("%d\n",vr.size());
		rep(i,0,vr.size())
		{
			// tot+=vr[i];
			printf("%lld ",vr[i]);
		}
		// cout<<tot<<" ";
		printf("\n");
	}
}
void build(ll idx,ll l,ll r)
{
	if(l==r)
	{
		tr[idx]=mp(ar[l].se,l);
		return;
	}
	ll mid=(l+r)/2;
	build(2*idx+1,l,mid);
	build(2*idx+2,mid+1,r);
	tr[idx]=max(tr[2*idx+1],tr[2*idx+2]);
}
void upd(ll idx,ll l,ll r,ll pos)
{
	if(pos<l||pos>r)
		return;
	if(l==r)
	{
		tr[idx]=mp(0,0);
		return;
	}
	ll mid=(l+r)/2;
	upd(2*idx+1,l,mid,pos);
	upd(2*idx+2,mid+1,r,pos);
	tr[idx]=max(tr[2*idx+1],tr[2*idx+2]);
}
pii query(ll idx,ll l,ll r,ll val)
{
	if(tr[idx].fi<=val)
		return mp(0,0);
	// cout<<idx<<" "<<l<<" "<<r<<"\n";
	if(l==r)
	{
		return tr[idx];
	}
	ll mid=(l+r)/2;
	pii a=query(2*idx+1,l,mid,val);
	if(a==neg)
		return query(2*idx+2,mid+1,r,val);
	return a;
}