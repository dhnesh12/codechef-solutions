#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i,a,b) for(ll i=a,ggdem=b;i<ggdem;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;

const int MAXN=1000006;
ll n,k,kk,m,x;
const ll MOD=1000000007;
ll c[MAXN];

ll fpow(ll b, ll e){
	ll res=1;
	while(e){
		if(e&1)res=res*b%MOD;
		b=b*b%MOD; e>>=1;
	}
	return res;
}

bool isprime[MAXN];
vector<ll> prime;
ll SPF[MAXN];
void sieve(int n){
    isprime[0] = isprime[1] = false;
    fore(i,2,n+1){
        if(isprime[i]) prime.push_back(i), SPF[i] = i;
        for(int j=0; j<SZ(prime)&&i*prime[j]<=n&&prime[j]<=SPF[i]; j++){
            isprime[i*prime[j]] = false;
            SPF[i*prime[j]] = prime[j];
        }
    }
}

ll ex[MAXN],em[MAXN],exm[MAXN],emc[MAXN],exmc[MAXN];

ll gm[MAXN];

void addi(ll &x, ll y){
	x+=y;
	if(x>=MOD)x-=MOD;
}

void subi(ll &x, ll y){
	x-=y;
	if(x<0)x+=MOD;
}

bool visp[MAXN];
ll p[MAXN];
ll szp=0;
ll sump[MAXN][2];

ll elev(ll b){
	if(b){
		return fpow(b,kk);
	}else{
		if(k==1){
			return 1;
		}else{
			return 0;
		}	
	}
}

ll getgm(ll x){
	szp=0;
	for(int i=x;i<=1000000;i+=x){
		ll sp=SPF[i];
		visp[sp]=true;
		addi(sump[sp][0],emc[i]);
		addi(sump[sp][1],exmc[i]);
	}
	fore(i,1,1000000/x+1){
		if(visp[i]&&(sump[i][0]||sump[i][1])){
			p[szp]=i; szp++;
		}
		visp[i]=false;
	}
	if(1000000/x<SPF[x]){
		if(visp[SPF[x]]&&(sump[SPF[x]][0]||sump[SPF[x]][1])){
			p[szp]=SPF[x]; szp++;
		}
		visp[SPF[x]]=false;
	}
	ll res=0;
	ll s[2]={0,0};
	for(int i=szp-1;i>=0;i--){
		addi(s[0],sump[p[i]][0]);
		sump[p[i]][0]=0;
		addi(s[1],sump[p[i]][1]);
		sump[p[i]][1]=0;
		ll nt=elev(s[0])*s[1]%MOD;
		if(i)nt=nt*(p[i]-p[i-1])%MOD;
		else nt=nt*(p[i])%MOD;
		addi(res,nt);
	}
	return res;
}

short mu[MAXN] = {0,1};
void mobius(){
	fore(i,1,MAXN)if(mu[i])for(int j=i+i;j<MAXN;j+=i)mu[j]-=mu[i];
}

ll g(ll x){
	ll res=0;
	for(int i=x,j=1;i<=1000000;i+=x,j++){
		if(mu[j]==1)addi(res,gm[i]);
		else if(mu[j]==-1)subi(res,gm[i]);
	}
	return res;
}

int main(){FIN;
	cin>>n>>k>>m>>x;
	kk=(k+MOD-2)%(MOD-1);
	m=m%(MOD-1);
	x=x%(MOD-1);
	mset(isprime,true);
	sieve(MAXN-1);
	fore(i,0,n){
		ll lle; cin>>lle;
		c[lle]++;
	}
	fore(i,1,MAXN){
		if(isprime[i]||i==1){
			ex[i]=fpow(i,x);
			em[i]=fpow(i,m);
		}else{
			ex[i]=ex[SPF[i]]*ex[i/SPF[i]]%MOD;
			em[i]=em[SPF[i]]*em[i/SPF[i]]%MOD;
		}
		exm[i]=ex[i]*em[i]%MOD;
		emc[i]=em[i]*c[i]%MOD;
		exmc[i]=exm[i]*c[i]%MOD;
	}
	mobius();
	fore(i,1,1000001){
		gm[i]=getgm(i);
	}
	ll res=0;
	fore(i,1,1000001){
		res=(res+g(i)*i)%MOD;
	}
	res=res*(k%MOD)%MOD;
	cout<<res<<"\n";
	return 0;
}