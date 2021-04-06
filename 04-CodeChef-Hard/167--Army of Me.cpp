#include <bits/stdc++.h>
using namespace std;

const int mxN=5e5, mxSTS=6e7;
int n, q, p[mxN], root[mxN+1], last, sts=1;
stack<int> stmax, stmin;

struct node {
	//children
	int lc, rc;
	//values for b and ans
	//maxb2 stores max(-l) over all b[l] that are minimum
	int minb1, maxb2, maxans;
	//lazy tags
	int lzaddb, lzmaxans;
} st[mxSTS];

void newver(int &i) {
	st[sts]=st[i];
	i=sts++;
}

void app(int i, int addb, int maxans) {
	st[i].minb1+=addb;
	st[i].maxans=max(maxans+st[i].maxb2, st[i].maxans);
	st[i].lzaddb+=addb;
	st[i].lzmaxans=max(maxans, st[i].lzmaxans);
}

void psh(int i) {
	newver(st[i].lc);
	app(st[i].lc, st[i].lzaddb, st[st[i].lc].minb1+st[i].lzaddb<=st[i].minb1?st[i].lzmaxans:0);
	newver(st[i].rc);
	app(st[i].rc, st[i].lzaddb, st[st[i].rc].minb1+st[i].lzaddb<=st[i].minb1?st[i].lzmaxans:0);
	st[i].lzaddb=st[i].lzmaxans=0;
}

void cmb(int i) {
	int j=st[st[i].lc].minb1<=st[st[i].rc].minb1?st[i].lc:st[i].rc;
	st[i].minb1=st[j].minb1;
	st[i].maxb2=st[j].maxb2;
	st[i].maxans=max(st[st[i].lc].maxans, st[st[i].rc].maxans);
}

void bld(int &i, int l2=0, int r2=n-1) {
	newver(i);
	if(l2==r2) {
		st[i].minb1=l2;
		st[i].maxb2=-l2;
		return;
	}
	int m2=(l2+r2)/2;
	bld(st[i].lc, l2, m2);
	bld(st[i].rc, m2+1, r2);
	cmb(i);
}

void upd(int i, int l1, int r1, int v, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, v, 0);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd(st[i].lc, l1, r1, v, l2, m2);
	if(m2<r1)
		upd(st[i].rc, l1, r1, v, m2+1, r2); 
	cmb(i);
}

int qry(int i, int l1, int r1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1)
		return st[i].maxans;
	int m2=(l2+r2)/2;
	psh(i);
	return max(l1<=m2?qry(st[i].lc, l1, r1, l2, m2):0, m2<r1?qry(st[i].rc, l1, r1, m2+1, r2):0);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	//input
	cin >> n >> q;
	for(int i=0; i<n; ++i)
		cin >> p[i];

	//construct segtree for all r
	//initialize b[i]=i
	bld(root[0]);
	for(int r=0; r<n; ++r) {
		//step 0. copy the data from the previous iteration
		root[r+1]=root[r];
		newver(root[r+1]);
		
		//step 1. update b
		//update the max part
		while(stmax.size()&&p[stmax.top()]<p[r]) {
			int updr=stmax.top(), updv=p[r]-p[stmax.top()];
			stmax.pop();
			int updl=stmax.size()?stmax.top()+1:0;
			upd(root[r+1], updl, updr, updv);
		}
		stmax.push(r);
		//update the min part
		while(stmin.size()&&p[stmin.top()]>p[r]) {
			int updr=stmin.top(), updv=-(p[r]-p[stmin.top()]);
			stmin.pop();
			int updl=stmin.size()?stmin.top()+1:0;
			upd(root[r+1], updl, updr, updv);
		}
		stmin.push(r);

		//step 2. max ans with r+1-l for b[l]=r
		app(root[r+1], 0, r+1);
	}
	
	//answer queries
	for(int l, r; q--; ) {
		cin >> l >> r;
		l=(l+last-1)%n;
		r=(r+last-1)%n;
		if(l>r)
			swap(l, r);
		//query for max ans[l..r] from iteration r
		cout << (last=qry(root[r+1], l, n)) << "\n";
	}
}