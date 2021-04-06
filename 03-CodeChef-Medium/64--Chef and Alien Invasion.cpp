/*
checker
*/

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long
#define pi pair<int,int> 
#define in(x) scanf("%lld",&x)
#define inl(x) scanf("%lld",&x)
#define cs(x) printf("Case %d:",x)
#define iout(x) printf("%d",x) 
#define lout(x) printf("%lld",x)
#define gap printf(" ")
#define nl printf("\n") 
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define debug(x) cout << #x << " " << x << endl;
const ll inf = LONG_MAX;
const ll mod = 1e9+7;

struct st
{
	ll x1,y1,x2,y2;
};

st g[1000][1000];
vector<st> v;
vector<ll> vx,vy,ans;
bool vis[1000][1000];
ll n,m,k,c,r;

ll dx[] = {1,0,0,-1};
ll dy[] = {0,1,-1,0};

bool check(ll r1,ll c1,ll r2,ll c2)
{
	st s1 = g[r1][c1],s2 =g[r2][c2];
	// cout << s1.x1 << " " << s1.y1 << " " << s1.x2 << " " << s1.y2 << endl;
	// cout << s2.x1 << " " << s2.y1 << " " << s2.x2 << " " << s2.y2 << endl;
	if(s1.x1==s2.x2)
	{
		ll x = s1.x1;
		ll y1 = s1.y1;
		ll y2 = s1.y2;
		for(ll i=0;i<k;i++)
		{
			if(v[i].x1==x || v[i].x2==x)
			{
				if(v[i].y1<=y1 && v[i].y2>=y2)
					return true;
			}
		
		}
		return false;
	}
	if(s1.x2==s2.x1)
	{
		ll x = s1.x2;
		ll y1 = s1.y1;
		ll y2 = s1.y2;
		for(ll i=0;i<k;i++)
		{
			if(v[i].x1==x || v[i].x2==x)
			{
				if(v[i].y1<=y1 && v[i].y2>=y2)
					return true;
			}
		
		}
		return false;
	}
	if(s1.y1==s2.y2)
	{
		ll y = s1.y1;
		ll x1 = s1.x1;
		ll x2 = s1.x2;
		for(ll i=0;i<k;i++)
		{
			if(v[i].y1==y || v[i].y2==y)
			{
				if(v[i].x1<=x1 && v[i].x2>=x2)
					return true;
			}
		}
		return false;
	}
	if(s1.y2==s2.y1)
	{
		ll y = s1.y2;
		ll x1 = s1.x1;
		ll x2 = s1.x2;
		for(ll i=0;i<k;i++)
		{
			if(v[i].y1==y || v[i].y2==y)
			{
				if(v[i].x1<=x1 && v[i].x2>=x2)
					return true;
			}
		}
		return false;
	}
}


ll dfs(ll x,ll y)
{
	vis[x][y] = true;
	st ss = g[x][y];
	ll ans = ((ss.x2-ss.x1)*(ss.y2-ss.y1))%mod;
	for(ll i=0;i<4;i++)
	{
		ll xx = x+dx[i];
		ll yy = y+dy[i];
		if(vis[xx][yy] || xx>=r || yy>=c || xx<0 || yy<0 || check(x,y,xx,yy))continue;
		ans += dfs(xx,yy),ans%=mod;
	}
	return ans;
}


ll bpow(ll a,ll b)
{
	if(b==0)return 1LL;
	ll base = (b&1) ? a : 1 ;
	ll ret = bpow(a,b/2);
	ret = (ret * ret) % mod;
	ret = (ret * base) % mod;
	return ret;
}

int main()
{
	ll t;
	in(t);
	while(t--)
	{
		v.clear();
		vx.clear();
		vy.clear();
		ans.clear();
		r = 0,c = 0;
		memset(vis,0,sizeof vis);
		in(n),in(m),in(k);

		v.push_back({0,0,n,m});
		vx.push_back(0);
		vx.push_back(n);
		vy.push_back(0);
		vy.push_back(m);

		for(ll i=0;i<k;i++)
		{
			ll x1,x2,y1,y2;
			in(x1),in(y1),in(x2),in(y2);
			v.push_back({x1,y1,x2,y2});
			vx.push_back(x1);
			vx.push_back(x2);
			vy.push_back(y1);
			vy.push_back(y2);
		}
		k++;
		sort(vx.begin(),vx.end());
		vx.erase(unique(vx.begin(),vx.end()),vx.end());
		sort(vy.begin(),vy.end());
		vy.erase(unique(vy.begin(),vy.end()),vy.end());

		r = vy.size()-1;
		c = vx.size()-1;

		for(ll i=0;i<vy.size()-1;i++)
		{
			ll y = vy[i];
			ll y_next = vy[i+1];
			for(ll j=0;j<vx.size()-1;j++)
			{
				ll x = vx[j];
				ll x_next = vx[j+1];
				g[i][j] = {x,y,x_next,y_next};
			}
		}

		for(ll i=0;i<r;i++)
		{
			for(ll j=0;j<c;j++)
			{
				// cout << g[i][j].x1 << " " << g[i][j].y1 << " " << g[i][j].x2 <<  " " << g[i][j].y2 << endl;
				if(!vis[i][j])
					ans.push_back(dfs(i,j));
			}
		}
		ll cc = (n*m)%mod;
		cc = bpow(cc,mod-2);
		
		ll anss = 0LL;

		for(ll i=0;i<ans.size();i++)
		{
			anss += (ans[i]*ans[i])%mod;
			anss%=mod;
		}
		anss = (anss*cc)%mod;

		lout(anss),nl;
	}
}