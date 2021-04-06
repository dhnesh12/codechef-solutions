#include<bits/stdc++.h>
// #define int long long
#define endl "\n"
using namespace std;

const int max_n = 2e5+10;
const int max_x = 5e3+10;
const int Mod = 998244353;

signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;cin>>T;
	while(T--){
		int n,m;cin>>n>>m;
		int a[n];
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		vector<pair<int,int> > b;
		b.resize(m);
		for(int i=0;i<m;i++){
			cin>>b[i].first>>b[i].second;
		}
		sort(b.begin(),b.end());

		set< pair<int,int> , greater<pair<int,int> > > rights;
		bool assigned[m];
		memset(assigned,0,sizeof(assigned));
		int t=0;

		for(int i=0;i<m;i++){
			while(t<n && a[t]==0) t++;

			if(t<b[i].first){
				a[t]--;
				rights.insert({b[i].second,i});
				assigned[i]=1;
			}else{
				if(rights.size()>0 && (*rights.begin()).first>=b[i].second){
					pair<int,int> c = *rights.begin();
					rights.erase(c);
					assigned[c.second]=0;
					assigned[i]=1;
					rights.insert({b[i].second,i});
				}else{

				}
			}
		}

		vector<int> R;
		int ans=0;
		for(int i=0;i<m;i++){
			if(!assigned[i]){
				R.push_back(b[i].second);
			}else ans++;
		}
		sort(R.begin(),R.end());

		reverse(a,a+n);
		t=0;
		for(int i:R){
			while(t<n && a[t]==0) t++;
			if(t<i){
				ans++;
				a[t]--;
			}
		}

		cout<<ans<<endl;


	}


}