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
#define  piii pair<pair<ll,ll>,ll>
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
#define MAXN 200005
ll t,n,q,a,b,ans[MAXN];
typedef struct NODE{
	ll min_,max_;
}NODE;
typedef struct UPDA{
	ll fix,var;
}UPDA;
NODE operator + (NODE a,NODE b)
{
	NODE c;
	c.max_=max(a.max_,b.max_);
	c.min_=min(a.min_,b.min_);
	return c;
}
NODE tr[4*MAXN+555];
UPDA up[4*MAXN+555];
pii pr[MAXN];
piii qr[MAXN];
void upd(ll,ll,ll,ll,ll,ll,ll);
ll query(ll,ll,ll,ll);
int main()
{
	// freopen("input.txt","r",stdin);
	// freopen("output1.txt","w",stdout);	
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld %lld %lld %lld",&n,&q,&a,&b);
		ll x,y;
		rep(i,1,n+1)
		{
			scanf("%lld %lld",&pr[i].fi,&pr[i].se);
		}	
		rep(i,0,q)
		{
			scanf("%lld %lld",&qr[i].fi.fi,&qr[i].fi.se);
			qr[i].se=i;
		}
		sort(qr,qr+q);
		memset(tr,0,sizeof(tr));
		memset(up,0,sizeof(up));
		ll ptr=0;
		rep(i,1,n+1)
		{
			ll tot=query(0,1,200000,pr[i].fi)+query(0,1,200000,pr[i].se);
			upd(0,1,200000,pr[i].fi+1,pr[i].se-1,a,b+tot);
			// if(i<5)
				// cout<<"A "<<pr[i].fi+1<<" "<<pr[i].se-1<<" "<<a<<" "<<b+tot<<" "<<q<<" "<<qr[ptr].fi.fi<<"\n";
			while(ptr<q&&qr[ptr].fi.fi==i)
			{
				// cout<<"HERE\n\n\n";
				// process

				ans[qr[ptr].se]=query(0,1,200000,qr[ptr].fi.se);
				// if(i<5)
				// cout<<qr[ptr].se<<" "<<ans[qr[ptr].se]<<"   "<<qr[ptr].fi.se<<"BB\n";
				// cout<<qr[ptr].se<<" "<<ans[qr[ptr].se]<<"PP\n";
				ptr++;
			}		
		}
		rep(i,0,q)
		printf("%lld\n",ans[i]);
	}
}
void upd(ll idx,ll l,ll r,ll low,ll high,ll var,ll fix)
{
	// cout<<idx<<" "<<l<<" "<<r<<" "<<var<<" "<<fix<<"\n";
	// lazy prop 
	if(1)
	{
		if(up[idx].fix)
		{
			tr[idx].min_=tr[idx].max_=up[idx].fix;
		}
		if(up[idx].var)
		{
			tr[idx].min_+=up[idx].var;
			tr[idx].max_+=up[idx].var;
		}
		if(l!=r)
		{
			if(up[idx].fix)
			{
				up[2*idx+1].fix=up[2*idx+2].fix=up[idx].fix;
				up[2*idx+1].var=up[2*idx+2].var=0;
			}
			if(up[idx].var)
			{
				up[2*idx+1].var+=up[idx].var;
				up[2*idx+2].var+=up[idx].var;
			}
		}
		up[idx].var=0;
		up[idx].fix=0;
	}

	if(high<l||low>r)
		return;
	if(low<=l&&r<=high)
	{
		bool ok=0;
		if(tr[idx].max_+var<=fix)
		{
			ok=1;
			// updates --> increase everything by a
			tr[idx].min_+=var;
			tr[idx].max_+=var;
			if(l!=r)
			{
				up[2*idx+1].var+=var;
				up[2*idx+2].var+=var;
			}
		}
		else if(tr[idx].min_+var>=fix)
		{
			ok=1;
			// updatees --> set evrything to b
			tr[idx].min_=tr[idx].max_=fix;
			if(l!=r)
			{
				up[2*idx+1].var=up[2*idx+2].var=0;
				up[2*idx+1].fix=up[2*idx+2].fix=fix;
			}
		}
		if(ok)
		{
			// cout<<l<<" "<<r<<" "<<tr[idx].min_<<" "<<tr[idx].max_<<"QQQQQ\n";
			return;
		}	
	}
	ll mid=(l+r)/2;
	upd(2*idx+1,l,mid,low,high,var,fix);
	upd(2*idx+2,mid+1,r,low,high,var,fix);
	tr[idx]=tr[2*idx+1]+tr[2*idx+2];
}
ll query(ll idx,ll l,ll r,ll pos)
{
	// lazy prop
	if(1)
	{
		// cout<<idx<<" "<<l<<" "<<r<<" "<<pos<<" "<<up[idx].fix<<" "<<up[idx].var<<"\n";
		if(up[idx].fix)
		{
			tr[idx].min_=tr[idx].max_=up[idx].fix;
		}
		if(up[idx].var)
		{
			tr[idx].min_+=up[idx].var;
			tr[idx].max_+=up[idx].var;
		}
		if(l!=r)
		{
			if(up[idx].fix)
			{
				up[2*idx+1].fix=up[2*idx+2].fix=up[idx].fix;
				up[2*idx+1].var=up[2*idx+2].var=0;
			}
			if(up[idx].var)
			{
				up[2*idx+1].var+=up[idx].var;
				up[2*idx+2].var+=up[idx].var;
			}
		}
		up[idx].var=0;
		up[idx].fix=0;
	}	
	// cout<<l<<" "<<r<<" "<<tr[idx].min_<<" "<<tr[idx].max_<<"\n";
	if(pos<l||pos>r)
		return 0;
	if(l==r)
		return tr[idx].max_;
	ll mid=(l+r)/2;
	return query(2*idx+1,l,mid,pos)+query(2*idx+2,mid+1,r,pos);
}