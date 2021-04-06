#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
bool p[1000005];
void sieve()
{
    for(int i=0;i<1000005;i++)
	p[i]=true;
	for(int i=2;i*i<1000005;i++)
	{
		if(p[i])
		{
			for(int j=i*i;j<1000005;j+=i)
			p[j]=false;
		}
	}

}

int main(){

    int t;
    cin>>t;
    sieve();
    while(t--){
        ll n,k;
        cin>>n>>k;
        ll ans=1;
        for(ll i=2;i<=n;i++){
            if(p[i]==false || k%i==0 )
            continue;
              ll m=n;
            while(m>=i){
                for( ll j=0;j<m/i;j++){
                    ans=ans*i%mod;
                }
                m/=i;
            }
        }
        cout<<ans<<endl;;
    }
}
