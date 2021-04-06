#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
struct node
{
	node *l, *r;
	node *p;
	int prior;
	ll sum;
	ll mod;
	int alive, curAlive;
	ll val;
	int size;
	node()
	{
		l = NULL;
		r = NULL;
		p = NULL;
		prior = rand();
		sum = 0;
		mod = 0;
		alive = 0;
		curAlive = 0;
		val = 0;
		size = 1;
	}
};
int getSize(node *v)
{
	if (v == NULL) return 0;
	return v->size;
}
ll getSum(node *v)
{
	if (v == NULL) return 0;
	return v->sum + v->mod * v->alive;
}
int getAlive(node *v)
{
	if (v == NULL) return 0;
	return v->alive;
}
void update(node *v)
{
	v->size = 1 + getSize(v->l) + getSize(v->r);
	v->sum = v->val + getSum(v->l) + getSum(v->r);
	v->alive = v->curAlive + getAlive(v->l) + getAlive(v->r);
	if (v->r != NULL) v->r->p = v;
	if (v->l != NULL) v->l->p = v;
}
void push(node *v)
{
	if (v == NULL) return;
	if (v->curAlive == 1)
	{
		v->val += v->mod;
	}
	if (v->l != NULL) v->l->mod += v->mod;
	if (v->r != NULL) v->r->mod += v->mod;
	v->mod = 0;
}
pair<node*, node*> split(node *v, int x)
{
	if (v == NULL) return make_pair(v, v);
	push(v);
	int myId = getSize(v->l) + 1;
	if (x >= myId)
	{
		pair<node*, node*> tmp = split(v->r, x - myId);
		v->r = tmp.first;
		update(v);
		v->p = NULL;
		return make_pair(v, tmp.second);
	}
	else
	{
		pair<node*, node*> tmp = split(v->l, x);
		v->l = tmp.second;
		update(v);
		v->p = NULL;
		return make_pair(tmp.first, v);
	}
}
node *merge(node *l, node *r)
{
	if (l == NULL) return r;
	if (r == NULL) return l;
	if (l->prior < r->prior)
	{
		push(l);
	//	push(r);
		l->r = merge(l->r, r);
		update(l);
		return l;
	}
	else
	{
//		push(l);
		push(r);
		r->l = merge(l, r->l);
		update(r);
		return r;
	}
}
int getId(node *v)
{
	int res = getSize(v->l) + 1;
	while (v->p != NULL)
	{
		node *vv = v->p;
		if (vv->r == v)
		{
			res += getSize(vv->l) + 1;
		}
		v = vv;
	}
	return res;
}
const int MAXN = 100 * 1000 + 7;
vector<int> g[MAXN];
vector<int> euler;
void dfs(int v, int p = -1)
{
	euler.push_back(v);
	bool leaf = true;
	for (int i = 0; i < (int)g[v].size(); i++)
	{
		int to = g[v][i];
		if (to != p)
		{
			dfs(to, v);
			euler.push_back(v);
			leaf = false;
		}
	}
	if (leaf)
	{
		euler.push_back(v);
	}
}
int a[MAXN];
node *leftv[MAXN], *rightv[MAXN];
int lp[MAXN], rp[MAXN];
pair<int, int> getSubtree(int v)
{
//	return make_pair(lp[v], rp[v]);
	int l = getId(leftv[v]), r = getId(rightv[v]);
	return make_pair(l, r);
}
int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, -1);
	node *v = NULL;
	for (int i = 0; i < (int)euler.size(); i++)
	{
		node *cur = new node();
	//	cerr << euler[i] << " ";
		if (leftv[euler[i]] == NULL)
		{
			lp[euler[i]] = i + 1;
			cur->sum = a[euler[i]];
			cur->val = cur->sum;
			cur->curAlive = 1;
			cur->alive = 1;
			leftv[euler[i]] = cur;
		}
		v = merge(v, cur);
		rp[euler[i]] = i + 1;
		rightv[euler[i]] = cur;
	}
//	cerr << endl;
	for (int i = 1; i <= q; i++)
	{
		int type;
		scanf("%d", &type);
		if (type == 1)
		{
			int u;
			scanf("%d", &u);
			pair<int, int> seg = getSubtree(u);
		//	cerr << seg.first << " " << seg.second << endl;
			pair<node*, node*> go1 = split(v, seg.second);
	//		cerr << getSum(go1.first) << endl;
			pair<node*, node*> go2 = split(go1.first, seg.first - 1);
	//		cerr << "ALIVE: " << go2.second->alive << endl;
 
			printf("%lld\n", getSum(go2.second));
			v = merge(merge(go2.first, go2.second), go1.second);
		}
		else if (type == 2)
		{
			int u, x;
			scanf("%d %d", &u, &x);
			pair<int, int> seg = getSubtree(u);
	//		cerr << seg.first << " " << seg.second << endl;
			pair<node*, node*> go1 = split(v, seg.second);
			pair<node*, node*> go2 = split(go1.first, seg.first - 1);
	//		cerr << "ALIVE: " << go2.second->alive << endl;
			go2.second->mod += x;
	//		cerr << getSum(go2.second) << endl;
			v = merge(merge(go2.first, go2.second), go1.second);
	//		cerr << getSum(v) << endl;
		}
		else
		{
			int a, b;
			scanf("%d %d", &a, &b);
			pair<int, int> sega = getSubtree(a);
			pair<int, int> segb = getSubtree(b);
			if (segb.first <= sega.second) swap(sega, segb);
			if (segb.first >= sega.first && segb.first <= sega.second)
			{
				printf("-1\n");
				continue;
			}
			if (sega.first >= segb.first && sega.first <= segb.second)
			{
				printf("-1\n");
				continue;
			}
			pair<node*, node*> after2 = split(v, segb.second);
			pair<node*, node*> sec = split(after2.first, segb.first - 1);
			pair<node*, node*> after1 = split(sec.first, sega.second);
			pair<node*, node*> fir = split(after1.first, sega.first - 1);
			v = merge(fir.first, merge(sec.second, merge(after1.second, merge(fir.second, after2.second))));
		}
	}
}
