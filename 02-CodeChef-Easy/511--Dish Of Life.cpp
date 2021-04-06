#include "bits/stdc++.h"
#define endl       '\n'
#define pb         push_back
#define mod        1000000007
#define int        long long int
#define hii        cout<<"yes\n";
#define all(x)     x.begin(),x.end()
#define deb(x)     cout<<#x<<" : "<<x<<"\n";
#define FASTIO     ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

using namespace std;
using namespace chrono;

void solve() {
    int n,k;
    cin >> n >> k;
 
    set<int> arr_ingredients;
    set<int> record_mountains_required;
    bool flag = false;
    bool flag_1 = false;
    for(int i = 0; i < n; ++i){
        int pi;
        cin >> pi;
        if(pi == k && n > 1){
            flag = true;
        }
        else if(pi == k && n == 1){
            flag_1 = true;
        }

        for(int j = 0; j < pi; ++j){
            int a;  cin >> a;
            if(!arr_ingredients.count(a)){
                arr_ingredients.insert(a);
                record_mountains_required.insert(i);
            }
        }
    }

    if(flag){
        cout<<"some"<<endl;
        return;
    }
    else if(flag_1){
        cout<<"all"<<endl;
        return;
    }

    if(arr_ingredients.size() == k){
        if(record_mountains_required.size() == n)
            cout<<"all"<<endl;
        else
            cout<<"some"<<endl;
    }
    else
        cout<<"sad"<<endl;
    arr_ingredients.clear();
    record_mountains_required.clear();
}


int32_t main() {
	FASTIO;
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
    freopen("Error.txt", "w", stderr);
#endif 
    auto start1 = high_resolution_clock::now();
	int t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
	auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
#ifndef ONLINE_JUDGE
    cerr << "Time: " << duration.count() / 1000 << endl;
#endif
	return 0;
}