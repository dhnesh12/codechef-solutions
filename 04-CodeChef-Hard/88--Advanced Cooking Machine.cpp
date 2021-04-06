#include<bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int inf=0x3f3f3f3f;
const LL Linf=1ll<<61;
const int mod=1e9+7;

inline void add(int&x,int y)
{
	x+=y;
	if(x>=mod)x-=mod;
}
#define array abracadabra
struct array
{
	int va[100111],vb[100111],sq;
	LL n;
	void init(LL N)
	{
		n=N;
		sq=(int)sqrt(n+0.5);
		for(int i=0;i<=sq;i++)va[i]=vb[i]=0;
	}
	int&operator [](LL x)
	{
		if(x<=sq)return va[x];
		else
		{
			assert(n/(n/x)==x);
			return vb[n/x];
		}
	}
};
const int maxv=10000111;
int pr[maxv],phi_pre[maxv],s_pre[maxv];

const int inv2=(mod+1)/2;
const int inv6=(mod+1)/6;

namespace sieve
{
	array s,phi;
	LL n;
	void calc(LL N)
	{
		n=N;
		s.init(n);phi.init(n);
		vector<LL> vs;
		for(LL i=1;i<=n;i=n/(n/i)+1)
		{
			LL v=n/i;vs.pb(v);
			if(v<maxv)
			{
				s[v]=s_pre[v];
				phi[v]=phi_pre[v];
			}
		}
		reverse(vs.begin(),vs.end());
		for(auto v:vs)if(v>=maxv)
		{
			int cur;
			
			cur=(LL)v%mod*((v+1)%mod)%mod*inv2%mod;
			for(LL i=2,j;i<=v;i=j+1)
			{
				j=v/(v/i);
				add(cur,mod-(j-i+1)%mod*phi[v/i]%mod);
			}
			phi[v]=cur;
			
			cur=1;
			for(LL i=2,j;i<=v;i=j+1)
			{
				j=v/(v/i);
				add(cur,mod-(LL)(phi[j]-phi[i-1]+mod)*s[v/i]%mod);
			}
			s[v]=cur;
		}
	}
};

char s[1000111];

LL n;int m;
bool check_s()
{
	int k1=0,k2=0;
	for(int i=1;i<=m;i++)
	{
		if(s[i]=='L'||s[i]=='R')
		{
			k1^=1;
			if((s[i]=='R')^k1)return false;
			s[i]='R';
		}
		else
		{
			k2^=1;
			if((s[i]=='T')^k2)return false;
			s[i]='T';
		}
	}
	return true;
}

int comp_frac(int a,int b,int c,int d)
{
	LL kk=(LL)a*d-(LL)b*c;
	return (kk<0?-1:(kk>0?1:0));
}

int cnt[1000111],sum[1000111];

int query_cnt(LL x,int k1,int k2)
{
	LL t=(x/k2)%mod;
	int rem=x%k2;
	return (t*cnt[k2]%mod+cnt[rem]+t*(t+mod-1)%mod*inv2%mod*k1%mod*k2%mod+t*k1%mod*rem%mod)%mod;
}
int query_sum(LL x,int k1,int k2)
{
	LL t=(x/k2)%mod,sum2=t*(t+mod-1)%mod*inv2%mod,sum3=t*(t+mod-1)%mod*(t+t+mod-1)%mod*inv6%mod;
	int rem=x%k2;
	int ret=(t*sum[k2]%mod+sum2*cnt[k2]%mod*(k1+k2)%mod+sum[rem]+t*cnt[rem]%mod*(k1+k2)%mod)%mod;
	ret=(ret+sum2*inv2%mod*k1%mod*k2%mod*(k2+2)%mod+sum3*inv2%mod*k1%mod*k2%mod*(k1+k2+k2)%mod)%mod;
	ret=(ret+(t*k1%mod*rem%mod*inv2%mod)*((t*k1+rem+2+t*2*k2)%mod)%mod)%mod;
	return ret;
}

int calc(LL n,int k1,int k2)// k = k1/k2
{
	if(k1==0)return 0;
	for(int i=1;i<=k2;i++)
	{
		int j=(LL)i*k1/k2;
		cnt[i]=cnt[i-1]+j;if(cnt[i]>=mod)cnt[i]-=mod;
		sum[i]=(sum[i-1]+(LL)i*j+(LL)j*(j+1)/2)%mod;
	}
	
	int ret=(LL)(mod-2)*query_cnt(n,k1,k2)%mod;
	int coef=n%mod*((n+1)%mod)%mod*(mod-1)%mod;
	for(LL i=1,j;i<=n;i=j+1)
	{
		j=n/(n/i);
		int cur=query_sum(n/i,k1,k2),cur2=(sieve::s[j]-sieve::s[i-1]+mod)%mod;
		ret=(ret+(LL)cur*cur2)%mod;
	}
	
	/*for(int i=1;i<=n;i++)
	{
		int j=(LL)i*k1/k2;
		s=(LL)i*j+(LL)j*(j+1)/2;
//		ret=(ret+(mod-j)*2%mod)%mod;
		int nxt=query_sum(i,k1,k2);
		//cur=nxt;
		h[i]=s%mod;
		//ret=(ret+(LL)h[i]*sieve::s[n/i])%mod;
	}*/
	return ret;
}

void solve()
{
	scanf("%lld%d%s",&n,&m,s+1);
	if(!check_s())
	{
		puts("0");
		return;
	}
	if(s[1]=='T')
	{
		for(int i=1;i<=m;i++)
		{
			if(s[i]=='T')s[i]='R';
			else s[i]='T';
		}
	}
	
	// C > R * la/lb
	// C < R * ra/rb
	int la=0,lb=1,ra=1,rb=1;
	int cr=1,ct=0;
	for(int i=2;i<=m;i++)
	{
		if(s[i]=='R')
		{
			cr++;
			// (ct+1) * C < cr * R
			if(comp_frac(ra,rb,ct+1,cr)==1)
			{
				ra=ct+1;
				rb=cr;
			}
		}
		else
		{
			ct++;
			if(comp_frac(la,lb,ct,cr+1)==-1)
			{
				la=ct;
				lb=cr+1;
			}
		}
//		printf("cr= %d ct= %d\n",cr,ct);
//		printf("i= %d c= %c la= %d lb= %d ra= %d rb= %d\n",i,s[i],la,lb,ra,rb);
	}
	
	if((LL)ra*lb<=(LL)la*rb)
	{
		puts("0");
		return;
	}
	sieve::calc(n);
	int ans=(calc(n,ra,rb)-calc(n,la,lb)+mod)%mod;
	
	int g=__gcd(ra,rb);
	ans=(ans+mod-(n/(rb/g)%mod)*(ra+rb)/g%mod)%mod;
	ans=(ans+2*(n/(rb/g))%mod)%mod;
	
	/*int ans=0;
	for(int r=1;r<=n;r++)for(int c=1;c<r;c++)
	{
		if(c*lb>r*la&&c*rb<r*ra)
		{
			ans+=(r+c)/g[r][c]-2;
		}
	}*/
	printf("%d\n",ans);
}
int main()
{
	phi_pre[1]=s_pre[1]=1;
	for(int i=2;i<maxv;i++)
	{
		if(!pr[i])
		{
			pr[i]=i;
			if((LL)i*i<maxv)
			{
				for(int j=i*i;j<maxv;j+=i)
					if(!pr[j])pr[j]=i;
			}
		}
		if(pr[i]!=pr[i/pr[i]])
		{
			phi_pre[i]=phi_pre[i/pr[i]]*(pr[i]-1);
			s_pre[i]=(LL)s_pre[i/pr[i]]*(mod+1-pr[i])%mod;
		}
		else
		{
			phi_pre[i]=phi_pre[i/pr[i]]*pr[i];
			s_pre[i]=s_pre[i/pr[i]];
		}
	}
	for(int i=1;i<maxv;i++)
	{
		add(phi_pre[i],phi_pre[i-1]);
		add(s_pre[i],s_pre[i-1]);
	}
	int tc;
	scanf("%d",&tc);
	while(tc--)solve();
	return 0;
}
