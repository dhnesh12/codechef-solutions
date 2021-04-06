#include<iostream>
#include<cstring>
#include<memory>
#include<algorithm>
#include<cmath>
#include<map>
#include<queue>
using namespace std;
typedef long long ll;
typedef long double LDB;
const int N=300005;
ll n,m,k,a[N],b[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		int j=i;
		while(a[j]==1&&j<=n){
			j++;
		}
		b[i]=j;
		i=j;
	}
	for(int i=0;i<m;i++){
		scanf("%lld",&k);
		ll ans=0;
		ll t; 
		ll j=1;
		while(k!=1){
			if(a[j]==1){
				ans+=k*(b[j]-j);
				j=b[j];
				continue;
			}
			t=k/a[j];
			if(k%a[j]){
				t++;
			}
			k=t;
			j++;
			ans+=k;
		}
		ans+=n-j+1;
		printf("%lld\n",ans);
	}
}