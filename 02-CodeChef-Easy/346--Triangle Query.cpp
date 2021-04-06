#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int maxN = 1e6 + 5;
template <typename T>
class fenwick {
private:
	vector <T> BIT;
	int size;
	
public:
	fenwick(int _n) : size(_n) {
		BIT.assign(size + 1, 0);
	}
	
	void reset() {
		BIT.assign(size + 1, 0);
	}

	void upd(int i, T v) {
		for(; i <= size; i += i&-i)
		BIT[i] += v;
	}
	
	T qry(int i) {
		T sum = 0;
		for(; i; i -= i&-i)
		sum += BIT[i];
		return sum;
	}
};

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	int t;
	cin >> t;
	while(t--)
	{
		int n, qq;
		cin >> n >> qq;
		vector <pair<int, int>> a(n), b(n);
		for(int i = 0; i < n; i++) {
			int x, y;
			cin >> x >> y;
			a[i] = make_pair(y - x, x), b[i] = make_pair(y + x, x);
		}
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		
		using tup = tuple <int, int, int>;

		vector <tup> q[2];
		for(int i = 0; i < qq; i++) {
			int l, r;
			cin >> l >> r;
			q[0].emplace_back(l, (l + r) / 2, i);
			q[1].emplace_back((l + r) / 2 + 1, r, i);
		}


		sort(q[0].begin(), q[0].end(), [] (tup &p1, tup &p2) {if(get<0>(p1) == get<0>(p2)) return get<2>(p1) < get<2>(p2); return get<0>(p1) > get<0>(p2);});
		sort(q[1].begin(), q[1].end(), [] (tup &p1, tup &p2) {if(get<1>(p1) == get<1>(p2)) return get<2>(p1) < get<2>(p2); return get<1>(p1) < get<1>(p2);});

		vector <int> ans(qq, 0);
		fenwick <int> ft(maxN);

		for(int i = 0, j = 0; i < qq; i++) {
			auto &[x, y, ind] = q[0][i];
			while(j < n && a[j].first <= -x) {
				ft.upd(a[j].second + 1, 1);
				++j;
			}
			ans[ind] += ft.qry(y + 1) - ft.qry(x);
		}
		
		ft.reset();
		for(int i = 0, j = 0; i < qq; i++) {
			auto &[x, y, ind] = q[1][i];
			while(j < n && b[j].first <= y) {
				ft.upd(b[j].second + 1, 1);
				++j;
			}
			ans[ind] += ft.qry(y + 1) - ft.qry(x);
		}

		for(int &x : ans)
		cout << x << ' ';
		cout << '\n';
	}
}
