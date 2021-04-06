#include <bits/stdc++.h>
#include <iostream>
#define mod 1000000007
#define ll long long
#define vi vector<int>
#define vii vector<vector<int>>
#define fo(i,n) for(int i=0;i<n;i++)
#define pb(x) push_back(x)
#define ci(x) cin>>x
#define ci2(x,y) cin>>x>>y
#define ci3(x,y,z) cin>>x>>y>>z
#define co(x) cout<<x<<endl
#define co2(x,y) cout<<x<<' '<<y<<endl
#define co3(x,y,z) cout<<x<<' '<<y<<' '<<z<<endl

using namespace std;



void test(){
    int n, x;
    cin>>n>>x;
    vector<pair<int, int>> intervals(n);
    fo(i, n){
        int s, e;
        ci2(s, e);
        intervals[i] = {s, e};
    }
    if(x == 1){
        cout<<n<<endl;
        return;
    }
    sort(intervals.begin(), intervals.end());
    int ans = 0;
    multiset<int> last;
    for(int i = 0; i < n; i++){
        if(last.size() == 0)
            last.insert(intervals[i].second);
        else{
            int cur_start = intervals[i].first;
            multiset<int> copyset;
            for(auto num : last){
                if(num >= cur_start)
                    copyset.insert(num);
            }
            last = copyset;
            last.insert(intervals[i].second);
            if(last.size() == x){
                ans++;
                auto it = last.end();
                it--;
                last.erase(it);
            }
        }
    }
    cout<<ans<<endl;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin>>t;
    while(t--){
	    test();
    }
}

