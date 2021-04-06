#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define ll long long
#define pb push_back
#define mp make_pair

using namespace std;

int n, m, q;
vector<int> parent;
vector<pair<int, int>> edges;
vector<pair<bool, pair<int, ll>>> queries;
vector<bool> edgelink (500001, 1);
vector<ll> ans;
vector<ll> population;
vector<ll> regpopulation;
ll maxans {0};
int maxreg;

int find_parent(int a)
{
	if(parent[a] == a)
		return a;

	return parent[a] = find_parent(parent[a]);
}

void union_nodes(int a, int b)
{
	int prta {find_parent(a)};
	int prtb {find_parent(b)};

	if(prta == prtb)
		return;

	if(regpopulation[prta] > regpopulation[prtb])
	{
		parent[prtb] = prta;
		regpopulation[prta] += regpopulation[prtb];
		if(regpopulation[prta] > maxans)
		{
			maxans = regpopulation[prta];
			maxreg = prta;
		}
	}
	else
	{
		parent[prta] = prtb;
		regpopulation[prtb] += regpopulation[prta];
		if(regpopulation[prtb] > maxans)
		{
			maxans = regpopulation[prtb];
			maxreg = prtb;
		}
	}
}

void solve()
{
	for (int i = 1; i <= n; ++i)
	{
		if(population[i] > maxans)
		{
			maxans = population[i];
			maxreg = i;
		}
	}

	for (int i = 1; i <= m; ++i)
	{
		if(edgelink[i])
			union_nodes(edges[i].first, edges[i].second);
	}
	ans.pb(maxans);

	for (int i = q-1; i > 0; --i)
	{
		auto k {queries[i]};
		int ind {k.second.first};
		if(k.first)
		{
			ll oldp {population[ind]}, newp {k.second.second};
			population[ind] = newp;
			int prt {find_parent(ind)};
			regpopulation[prt] += (newp - oldp);
			if(prt == maxreg)
				maxans = regpopulation[prt];
			else if(regpopulation[prt] > maxans)
			{
				maxans = regpopulation[prt];
				maxreg = prt;
			}
		}
		else
		{
			union_nodes(edges[ind].first, edges[ind].second);
		}

		ans.pb(maxans);
	}
}

int main()
{
	fastio
	char c;
	int x, y, k, a;
	cin >> n >> m >> q;

	parent = vector<int> (n+1);
	population = vector<ll> (n+1);
	regpopulation = vector<ll> (n+1);

	for (int i = 1; i <= n; ++i)
	{
		cin >> population[i];
		parent[i] = i;
		regpopulation[i] = population[i];
	}

	edges.pb({0, 0});
	for (int i = 1; i <= m; ++i)
	{
		cin >> x >> y;
		edges.pb(mp(x, y));
	}

	for (int i = 0; i < q; ++i)
	{
		cin >> c;
		if(c == 'D')
		{
			cin >> k;
			edgelink[k] = 0;
			queries.pb({0, mp(k, 0)});
		}
		else
		{
			cin >> a >> x;
			queries.pb({1, mp(a, population[a])});
			regpopulation[a] = population[a] = x;
		}
	}

	solve();

	for (int i = q-1; i >= 0; --i)
	{
		cout << ans[i] << "\n";
	}
	return 0;
}