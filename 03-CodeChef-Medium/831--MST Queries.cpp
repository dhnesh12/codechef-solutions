#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e3 + 20, N2 = 2e5 + 20;
vector<pair<pair<int, int>, ll>> edg, edg2;
vector<int> vt;
bool darim[N2], zero[N2];
int par[N], sz[N];
int n, m, q;

bool compa(int i, int j) {return (zero[i] ? 0ll : edg[i].second) < (zero[j] ? 0ll : edg[j].second);}

int get_par(int u)
{
	if (par[u] == u) return u;
	return par[u] = get_par(par[u]);
}

void mer(int u, int v)
{
	u = get_par(u); v = get_par(v);
	if (u == v) return;
	if (sz[v] > sz[u]) swap(u, v);
	sz[u] += sz[v];
	par[v] = u;
	return;
}

inline ll kruskal(bool ff = false)
{
	sort(vt.begin(), vt.end(), compa);
	for (int i = 0; i < n; i++)
	{
		par[i] = i;
		sz[i] = 1;
	}
	ll ans = 0;
	for (int e : vt)
	{
		int u = edg[e].first.first, v = edg[e].first.second;
		if (get_par(u) != get_par(v))
		{
			ans += (zero[e] ? 0ll : edg[e].second);
			if (ff) darim[e] = true;
		}
		mer(u, v);
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m >> q;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		ll w;
		cin >> u >> v >> w;
		u--; v--;
		if (u > v) swap(u, v);
		edg.push_back({{u, v}, w});
		edg2.push_back({{u, v}, i});
	}
	sort(edg2.begin(), edg2.end());
	for (int i = 0; i < m; i++) vt.push_back(i);
	sort(vt.begin(), vt.end(), compa);
	kruskal(true);
	vt.clear();
	for (int i = 0; i < m; i++) if (darim[i]) vt.push_back(i);
	sort(vt.begin(), vt.end(), compa);
	while (q--)
	{
		int w;
		cin >> w;
		if (w == 1)
		{
			int u, v;
			cin >> u >> v;
			u--; v--;
			if (u > v) swap(u, v);
			int indx = edg2[lower_bound(edg2.begin(), edg2.end(), make_pair(make_pair(u, v), 0ll)) - edg2.begin()].second;
			if (!zero[indx] && !darim[indx])
			{
				vt.push_back(indx);
				int ind = (int)vt.size() - 1;
				while (ind > 0)
				{
					swap(vt[ind], vt[ind - 1]);
					ind--;
				}
			}
			zero[indx] = true;
			continue;
		}
		if (w == 2)
		{
			int u, v;
			cin >> u >> v;
			u--; v--;
			if (u > v) swap(u, v);
			int indx = edg2[lower_bound(edg2.begin(), edg2.end(), make_pair(make_pair(u, v), 0ll)) - edg2.begin()].second;
			if (zero[indx] && !darim[indx]) vt.erase(find(vt.begin(), vt.end(), indx));
			zero[indx] = false;
			continue;
		}
		cout << kruskal() << '\n';
	}
	return 0;
}

