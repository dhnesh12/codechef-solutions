#include <bits/stdc++.h>
using namespace std;

template<typename T>
void out(T x) { cout << x << endl; exit(0); }
#define watch(x) cout << (#x) << " is " << (x) << endl








const int inf = 2e9;


bool check(int le, int mid, int ri) {
    bool ok = true;
    
    // xMxx
    ok &= (le+mid >= ri);

    // invalid xxMx
    ok &= (le+1 <= mid+ri);
    return ok;    
}


template<typename T> struct segtree {
    
    T merge(T x, T y) {
	return x+y;
    }
    int n;
    vector<T> t;
    void init(int n) {
	n += 10;
	this->n = n;
	t.assign(n*4, 0);
    }

    void upd(int v, int tl, int tr, int i, T dx) {
	if (tl == tr) {
	    t[v] = merge(t[v], dx);
	} else {
	    int tm = (tl+tr)/2;
	    if (i<=tm) {
		upd(2*v,tl,tm,i,dx);
	    } else {
		upd(2*v+1,tm+1,tr,i,dx);
	    }
	    t[v] = merge(t[2*v], t[2*v+1]);
	}
    }

    T qry(int v, int tl, int tr, int l, int r) {
	if (l>tr || r<tl) {
	    return 0;
	}
	if (l <= tl && tr <= r) {
	    return t[v];
	}
	int tm = (tl+tr)/2;
	return merge(qry(2*v,tl,tm,l,r), qry(2*v+1,tm+1,tr,l,r));
    }

    int med(int v, int tl, int tr, int le, int ri) {
	if (tl==tr) {
	    return tl;
	} else {
	    int tm = (tl+tr)/2;
	    bool goLeft = check(le, t[2*v], t[2*v+1]+ri);
	    bool goRight = check(le+t[2*v], t[2*v+1], ri);
	    assert(goLeft ^ goRight);

	    if (goLeft) {
		return med(2*v,tl,tm,le,t[2*v+1]+ri);
	    } else {
		return med(2*v+1,tm+1,tr,le+t[2*v],ri);
	    }
	}
    }
};


void solve() {
    int n,q;
    cin>>n>>q;
    vector<int> a(n+1);
    vector<int> ord = {0, inf};
    for (int i=1; i<=n; i++) {
	cin>>a[i];
	ord.push_back(a[i]);
    }
    
    vector<pair<int,int>> Q(q);
    for (int i=0; i<q; i++) {
	cin>>Q[i].first>>Q[i].second;
	ord.push_back(Q[i].second);
    }

    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());
    int N = ord.size();

    auto get = [&](int x) {
	return lower_bound(ord.begin(), ord.end(), x) - ord.begin();
    };

    segtree<int> tree;
    tree.init(N+10);


    for (int i=1; i<=n; i++) {
	tree.upd(1,1,N,get(a[i]),+1);
    }

    for (int i=0; i<q; i++) {
	int idx = Q[i].first;
	int val = Q[i].second;
	
	tree.upd(1,1,N,get(a[idx]),-1);
	a[idx] = val;
	tree.upd(1,1,N,get(a[idx]),+1);
	

	int med = tree.med(1,1,N,0,0);
	
	int fm = tree.qry(1,1,N,med,med);
	int fl = tree.qry(1,1,N,1,med-1);
	int fr = tree.qry(1,1,N,med+1,N);

	assert(check(fl,fm,fr));

	int res = fm;
	if (fl>=fr) {
	    res -= (fl-fr);
	}
	cout<<res<<"\n";
    }
    
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
