#include<bits/stdc++.h>
using namespace std;
#define lli long long int
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define ff first
#define asc(a) ((int)a)
#define ss second
#define mp(a,b) make_pair(a,b)
#define pii pair<int,int>
#define pll pair<lli,lli>
#define pii3 pair< int,pair<int,int> >
#define pll3 pair< lli,pair<lli,lli> >
#define pb(a) push_back(a)
#define en "\n"
const lli MOD=1e9+7;

int main(){
	lli n,m;
	double p,a,b,c;
	int t;
	cin>>t;
	while(t--){
		cin>>n>>m>>p;
		p=p/100;
		vector<pair<int,double> >v;
		for(int i=0,x;i<m;i++){
			cin>>x;
			v.push_back({x-1,1});
		}
		sort(v.begin(),v.end());
		while(n>1){
			vector<pair<int,double> >y;
			for(int i=0;i<v.size();i++){
				if( (v[i].ff&1) ==0 && i!=v.size()-1 && v[i].ff+1==v[i+1].ff){
					y.push_back({v[i].ff/2, v[i].ss*v[i+1].ss + (v[i].ss+v[i+1].ss-2*v[i].ss*v[i+1].ss)*p });
					i++;
				}
				else{
					y.push_back({v[i].ff/2,v[i].ss*p});
				}
			}
			v=y;
			n=n/2;
		}
		cout<<setprecision(9)<<v[0].ss*100<<endl;
	}
	return 0;
}