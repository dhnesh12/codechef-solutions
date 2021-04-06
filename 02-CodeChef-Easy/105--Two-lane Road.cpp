#include <bits/stdc++.h>
using namespace std;

template<typename T>
void out(T x) { cout << x << endl; exit(0); }
#define watch(x) cout << (#x) << " is " << (x) << endl










const int inf = 2e9;



int solve() {

    int n,k,d;
    cin>>n>>k>>d;
    vector<int> X(n), L(n);
    vector<int> a = {0,k};
    for (int i=0; i<n; i++) {
	cin>>X[i];
    }
    for (int i=0; i<n; i++) {
	cin>>L[i];
	L[i]--;
    }
    int lastChange = -inf;
    int curLane = L[0]^1;
    
    for (int i=0; i<n; i++) {
	if (L[i]!=curLane) {
	    continue;
	}
	// switch
	int to = max(X[i-1]+1, lastChange+d);
	if (to >= X[i]) {
	    return X[i];
	}
	lastChange = to;
	curLane ^= 1;
    }

    return k;
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);  cout.tie(0);

    int t;
    cin>>t;
    while (t--) {
	cout<<solve()<<"\n";
    }
    
    return 0;
}
