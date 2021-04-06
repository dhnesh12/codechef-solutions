#include "bits/stdc++.h"
using namespace std;
struct SegTree {
	vector<int> rt, left, right, cnt;
	int sz;
	int build(int lo, int hi) {
		int no = sz++;
		cnt[no] = 0;
		if(lo != hi) {
			int mid = (lo + hi) >> 1;
			left[no] = build(lo, mid);
			right[no] = build(mid + 1, hi);
		}
		return no;
	}
	int upd(int k, int lo, int hi, int R) {
		int no = sz++;
		if(lo == hi) cnt[no] = 1 + cnt[R];
		else {
			int mid = (lo + hi) >> 1;
			if(k <= mid) {
				left[no] = upd(k, lo, mid, left[R]);
				right[no] = right[R];
			} else {
				left[no] = left[R];
				right[no] = upd(k, mid + 1, hi, right[R]);
			}
			cnt[no] = cnt[R] + 1;
		}
		return no;
	}
	int query(int l, int r, int lo, int hi, int L, int R) {
		if(l > r) return 0;
		else if(r - l == hi - lo) return cnt[R] - cnt[L];
		int mid = (lo + hi) >> 1;
		return query(l, min(r, mid), lo, mid, left[L], left[R]) + 
		query(max(mid + 1, l), r, mid + 1, hi, right[L], right[R]);
	}
	SegTree(vector<int>& a) {
		sz = 0;
		rt.resize(1 + a.size());
		int h = 33 - __builtin_clz(a.size());
		left.resize((1 << h) + h * a.size());
		right.resize(left.size());
		cnt.resize(left.size());
		rt[0] = build(0, int(a.size()) - 1);
		for(int i = 1; i <= int(a.size()); ++i) rt[i] = upd(a[i - 1], 0, int(a.size()) - 1, rt[i - 1]);
	}
	int query(int l, int r, int k) {
		return query(k, int(rt.size()) - 2, 0, int(rt.size()) - 2, rt[l], rt[r + 1]);
	}
};
long long solve(vector<int>& a) {
	int n = a.size();
	vector<int> l(n);
	stack<pair<int, int>> st;
	for(int i = n - 1; i >= 0; --i) {
		while(!st.empty() && st.top().first >= a[i]) st.pop();
		l[i] = st.empty() ? n - 1 : st.top().second - 1;
		st.push({a[i], i});
	}
	while(!st.empty()) st.pop();
	long long cnt = 0;
	SegTree seg(l);
	for(int i = 0; i < n; ++i) {
		int g;
		while(!st.empty() && st.top().first <= a[i]) st.pop();
		g = st.empty() ? 0 : st.top().second + 1;
		st.push({a[i], i});
		cnt += seg.query(g, i, i);
	}
	return cnt;
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		vector<int> a(n);
		for(int& x : a) cin >> x;
		long long cnt = solve(a);
		int x = -1, y = 0;
		for(int z : a) {
			if(x != z) {
				cnt -= y * (y - 1LL) / 2 + y;
				x = z;
				y = 1;
			} else ++y;
		}
		cnt -= y * (y - 1LL) / 2 + y;
		reverse(a.begin(), a.end());
		cnt += solve(a);
		cout << cnt << '\n';
	}
	return 0;
}