#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T> using oset=tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Event{
	int x, type, y;
	bool operator<(const Event &o) {
		return make_pair(x, type)<make_pair(o.x, o.type);
	}
};

void solve(){
	int n;
	cin>>n;
	vector<int> xl(n+1), xr(n+1);
	for(int i=0;i<n;i++){
		cin>>xl[i]>>xr[i];
	}
	map<int, int> mpl, mpr;
	for(int i=0;i<n;i++){
		if(mpl.find(xl[i])==mpl.end())
			mpl[xl[i]]=xr[i];
		else
			mpl[xl[i]]=max(xr[i], mpl[xl[i]]);
		if(mpr.find(xr[i])==mpr.end())
			mpr[xr[i]]=xl[i];
		else
			mpr[xr[i]]=min(xl[i], mpr[xr[i]]);
	}
	vector<Event> arr;
	for(auto a : mpr){
		arr.push_back({a.second, 1, a.first});
		arr.push_back({a.first, 2, a.first});
	}
	for(auto a : mpl) {
		arr.push_back({a.first, 3, a.second});
	}
	sort(arr.begin(), arr.end());
	long long ans=0;
	oset<int> os;
	for(Event e : arr){
		if(e.type==1){
			os.insert(e.y);
		}
		else if(e.type==2){
			os.erase(e.y);
		}
		else{
			ans+=os.order_of_key(e.y+1);
		}
	}
	cout<<ans+1<<endl;
}

signed main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}


