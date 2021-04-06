#include <bits/stdc++.h>
using namespace std;

template<typename T>
void out(T x) { cout << x << endl; exit(0); }
#define watch(x) cout << (#x) << " is " << (x) << endl





using ll = long long;


const int maxn = 1e6 + 5;



int n;
int A[maxn], G[maxn];

void solve() {
    cin>>n;
    for (int i=0; i<n; i++) {
	cin>>A[i];
    }
    for (int i=0; i<n+1; i++) {
	cin>>G[i];
    }
    {
	// G[i] terms occur i times
	ll sum = 0;
	for (int i=0; i<=n; i++) {
	    sum += 1ll*i*G[i];
	}
	if (sum != n) {
	    cout<<"impossible\n";
	    return;
	}
    }
    {
	// there are sum(G[i]) terms
	ll sum = 0;
	for (int i=0; i<=n; i++) {
	    sum += G[i];
	}
	if (sum != n) {
	    cout<<"impossible\n";
	    return;
	}
    }



    multiset<int> ms;
    for (int i=0; i<=n; i++) {
	for (int j=0; j<G[i]; j++) {
	    ms.insert(i);
	}
    }

    vector<int> w;
    vector<int> f(n, 0);
    for (int i=0; i<n; i++) {
	if (~A[i]) {
	    f[A[i]]++;
	} else {
	    w.push_back(i);
	}
    }

    for (int x=n-1; x>=0; x--) {
	int have = f[x];
	auto iter = ms.lower_bound(have);
	if (iter == ms.end()) {
	    cout<<"impossible\n";
	    return;
	}
	int take = *iter - have;
	ms.erase(iter);
	for (int i=0; i<take; i++) {
	    if (w.empty()) {
		cout<<"impossible\n";
		return;
	    }
	    int idx = w.back();
	    A[idx] = x;
	    w.pop_back();
	}
    }

    for (int i=0; i<n; i++) {
	cout<<A[i]<<" ";
    }
    cout<<"\n";
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);  cout.tie(0);

    int t;
    cin>>t;
    while (t--) {
	solve();
    }
    
    
    return 0;
}
