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
typedef struct Vector{
	ll x,y;
	Vector () {}
	Vector (ll x,ll y): x(x), y(y) {}
}Vector;
ll operator % (Vector &a,Vector &b)
{
	return a.x*b.y-a.y*b.x;
}
ll operator * (Vector &a,Vector &b)
{
	return a.x*b.x+a.y*b.y;
}
Vector u(0,1);
bool A(Vector a)
{
	return (u%a>0||(u%a==0&&u*a>=0));
}
ll sqr(Vector x)
{
	return x.x*x.x+x.y+x.y;
}
ll operator < (Vector &a,Vector &b)
{
	if(A(a)==A(b)&&a%b==0)
	{
		return sqr(a)<sqr(b);
	}
	return (A(a)==A(b)&&a%b>=0)||(A(a)&&!A(b));
}
bool comp(Vector &a,Vector &b)
{
	return a<b;
}
vector <Vector> vr;
Vector tr[6055];  
map <pii,ll> mr;  	
ll t,n;
int main()
{
	// freopen("input.txt","r",stdin);
	vr.resize(2005);	
	vector <Vector> qr;
			
	scanf("%lld",&n);
	rep(i,0,n)
	{
		ll x,y;
		scanf("%lld %lld",&x,&y);
		vr[i]=Vector(x,y);
	}
	ll ans=0;
	rep(i,0,n)
	{
		ll q=0;

		rep(j,0,n)
		{		
			if(i!=j)
			{
				tr[q++]=Vector(vr[j].x-vr[i].x,vr[j].y-vr[i].y);
			}
		}

		sort(tr,tr+n-1,comp);
		rep(j,0,n-1)
			tr[n-1+j]=tr[2*n-2+j]=tr[j];

		ll l=2*n-3,r=n-1;

		for(int j=2*n-3;j>=n-1;j--)
		{
			l=min(l,(ll)j-1);	
			while(((tr[j]%tr[l])<0||(tr[j]%tr[l]==0&&comp(tr[l],tr[j])))&&(tr[j]*tr[l])>0&&abs(l-j)!=n)
			{
				l--;
			}
			ans+=n+l;
		}
		for(int j=n-1;j<2*n-2;j++)
		{
			r=max(r,(ll)j+1);
			// r=j+1;
			while(((tr[j]%tr[r])>0||(tr[j]%tr[r]==0&&comp(tr[j],tr[r])))&&(tr[j]*tr[r])>0)
			{
				r++;
			}
			ans+=-r;
		}
	}
	printf("%lld\n",((n*(n-1)*(n-2))/6-ans/2));
}