#include <bits/stdc++.h>
using namespace std;

#define FAST ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define int long long
#define F first
#define S second
#define pb push_back
#define sz(x) (int)x.size()
#define len(x) (int)x.length()
#define pii pair<int,int>
#define ppi pair<pii,int>
#define vi vector<int>
#define mp make_pair
#define minheap priority_queue<int,vector<int>,greater<int>>

int32_t main(){
FAST
    int t,n;
    cin>>t;
    while(t--) {
        cin >> n;
        int x = 0,y = 0,moves = 0;
        while(x < n) {
            int p = sqrt(y)+1;
            x = p;
            y += p*p;
            moves++;
            //cout << x << ' '<< y << '\n';
        }
        if(x > n) moves--;
        cout << moves << '\n';
    }
}