#pragma GCC optimize("01")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
ll n,k,m;
 
 
ll power(ll a,ll b)
{
    ll res=1;
    while(b>0)
    {
        if(b%2){res=(res*a)%mod;}
        b>>=1;
        a=(a*a)%mod;
    }
    return res;
}
 
 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin>>m>>n>>k;
    
    if(m==1)
    {
        ll total=1,add,powk=1;
        for(int i=2;i<=n;i++){
           total=(total*k)%mod;
           add=(k-1)*powk;
           add%=mod;
           powk=(powk*k)%mod;
           total=(total+add)%mod;
        }
        
        total=(total*k)%mod;
        ll den=power(k,m*n);
        den=power(den,mod-2);
        cout<<(total*den)%mod;
    }
    else
    {
        if(k==1){
            cout<<1<<'\n';
        }
        else{
            ll powk=1,mul=(k*k)%mod;
            ll diff=2,same=1,total,differ=(mul-k+mod)%mod;
            ll diffCnt=mul,sameCnt=(k-1)*(k-1);
            sameCnt%=mod;
            diffCnt=(diffCnt+sameCnt-1+mod)%mod;
            
            total=(differ*diff)%mod;
            total+=(same*k)%mod;
            total%=mod;
            
            for(int i=2;i<=n;i++){
                diff=total;
                diff+=(diffCnt*powk)%mod;
                diff%=mod;
                
                same=total;
                same+=(sameCnt*powk)%mod;
                same%=mod;
                
                powk=(powk*mul)%mod;
                total=(differ*diff)%mod;
                total+=(same*k)%mod;
                total%=mod;
            }
            
            ll den=power(k,m*n);
            den=power(den,mod-2);
            cout<<(total*den)%mod;
            
        }
    }
    
	return 0;
}