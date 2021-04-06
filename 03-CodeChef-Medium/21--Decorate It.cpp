#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN=3e5;
int n, q, k, p[mxN], d[mxN];
ll ans[mxN];
ar<int, 3> ev[3*mxN];
vector<int> xs;
set<ar<int, 2>> s[mxN];

struct ft {
	ll a[mxN+1];
	void upd(int i, int x) {
		for(++i; i<=q; i+=i&-i)
			a[i]+=x;
	}
	ll qry(int i) {
		ll r=0;
		for(; i; i-=i&-i)
			r+=a[i];
		return r;
	}
} f1, f2;

void us2(int l, int r, int x1, int x2) {
	int p1=lower_bound(xs.begin(), xs.end(), l)-xs.begin(), p2=upper_bound(xs.begin(), xs.end(), r)-xs.begin()-1;
	if(p1>p2)
		return;
	f1.upd(p1, x1);
	f1.upd(p2+1, -x1);
	f2.upd(p1, x2);
	f2.upd(p2+1, -x2);
}

void us(int l, int r, int s) {
	//cout << l << " " << r << " " << s << endl;
	int m=(ll)((ll)l+r)/2;
	us2(l, m, s, -l*s);
	us2(m+1, r, -s, r*s);
}

ll qry(int l1) {
	int p=lower_bound(xs.begin(), xs.end(), l1)-xs.begin();
	ll r1=f1.qry(p+1), r2=f2.qry(p+1);
	return r1*l1+r2;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q >> k;
	for(int i=0; i<n; ++i) {
		cin >> p[i] >> d[i] >> ev[2*i][0] >> ev[2*i+1][0];
		--d[i];
		ev[2*i+1][1]=-1;
		ev[2*i][2]=i;
		ev[2*i+1][2]=i;
		++ev[2*i+1][0];
	}
	for(int i=0; i<q; ++i) {
		cin >> ev[2*n+i][1] >> ev[2*n+i][0];
		xs.push_back(ev[2*n+i][1]);
		ev[2*n+i][2]=i;
	}
	sort(xs.begin(), xs.end());
	//for(int i=0; i<q; ++i) {
		//ev[2*n+i][1]=lower_bound(xs.begin(), xs.end(), ev[2*n+i][1])-xs.begin();
	//}
	int m=2*n+q;
	sort(ev, ev+m);
	for(int i=0; i<k; ++i) {
		s[i].insert({(int)-1e9, -1});
		s[i].insert({(int)2e9, 1});
		us(-1e9, 2e9, 1);
	}
	for(int i=0, na=0; i<m; ++i) {
		if(ev[i][1]>0) {
			//query
			//cout << "qry " << ev[i][2] << endl;
			if(na<k) {
				ans[ev[i][2]]=-1;
			} else {
				ans[ev[i][2]]=qry(ev[i][1]);
			}
		} else if(!ev[i][1]) {
			//add
			int j=ev[i][2];
			//cout << "add " << j << endl;
			if(s[d[j]].size()<3)
				++na;
			auto it1=s[d[j]].lower_bound({p[j]}), it2=it1--;
			us((*it1)[0], (*it2)[0], -1);
			us((*it1)[0], p[j], 1);
			us(p[j], (*it2)[0], 1);
			s[d[j]].insert({p[j], j});
		} else {
			//rem
			int j=ev[i][2];
			s[d[j]].erase({p[j], j});
			if(s[d[j]].size()<3)
				--na;
			//cout << "rem " << j << endl;
			auto it1=s[d[j]].lower_bound({p[j]}), it2=it1--;
			us((*it1)[0], (*it2)[0], 1);
			us((*it1)[0], p[j], -1);
			us(p[j], (*it2)[0], -1);
		}
	}
	for(int i=0; i<q; ++i)
		cout << ans[i] << "\n";
}