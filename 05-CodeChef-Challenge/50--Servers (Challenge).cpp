
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef float ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
 
#define X first
#define Y second
 
#define read(x) \
{ \
	char c = getchar(); \
	for (; !isdigit(c); c = getchar()); \
	x = c-'0'; \
	for (c = getchar(); isdigit(c); c = getchar()) \
		x = x*10+c-'0'; \
}
 
const int MAXN = 500010;
const ld INF = 1e9;
 
ll timestamp;
 
int n;
pii id[MAXN];
struct point
{
	int x, y, z;
}p[MAXN];
 
struct node
{
	node *Lc, *Rc, *pre;
	int Lx, Rx, Ly, Ry, Lz, Rz;
	point *p;
	int tot, cur;
}tree[MAXN];
 
node *root;
int r[MAXN];
 
bool cmpx(const int &i, const int &j)
{
	return p[i].x < p[j].x;
}
 
bool cmpy(const int &i, const int &j)
{
	return p[i].y < p[j].y;
}
 
bool cmpz(const int &i, const int &j)
{
	return p[i].z < p[j].z;
}
 
node *build(int L, int R)
{
	if (L > R) return 0;
	int m = (L+R)/2;
	ld sx, sy, sz, tx, ty, tz;
	sx = sy = sz = tx = ty = tz = 0;
	for (int i = L; i <= R; ++ i)
	{
		sx += p[r[i]].x;
		tx += (ld)p[r[i]].x*p[r[i]].x;
		sy += p[r[i]].y;
		ty += (ld)p[r[i]].y*p[r[i]].y;
		sz += p[r[i]].z;
		tz += (ld)p[r[i]].z*p[r[i]].z;
	}
	int len = R-L+1;
	sx /= len, tx /= len, sy /= len, ty /= len, sz /= len, tz /= len;
	tx -= sx*sx;
	ty -= sy*sy;
	tz -= sz*sz;
	int kd = (tz >= tx && tz >= ty) ? 2 : (tx >= ty && tx >= tz) ? 0 : 1;
	nth_element(r+L, r+m, r+R+1, kd == 0 ? cmpx : kd == 1 ? cmpy : cmpz);
	
	node *it = tree+r[m];
	it->p = p+r[m];
	it->Lx = it->Rx = it->p->x;
	it->Ly = it->Ry = it->p->y;
	it->Lz = it->Rz = it->p->z;
	it->tot = it->cur = 1;
	it->Lc = build(L, m-1);
	it->Rc = build(m+1, R);
	if (it->Lc)
	{
		it->Lc->pre = it;
		it->tot += it->Lc->tot;
		it->Lx = min(it->Lx, it->Lc->Lx);
		it->Rx = max(it->Rx, it->Lc->Rx);
		it->Ly = min(it->Ly, it->Lc->Ly);
		it->Ry = max(it->Ry, it->Lc->Ry);
		it->Lz = min(it->Lz, it->Lc->Lz);
		it->Rz = max(it->Rz, it->Lc->Rz);
	}
	if (it->Rc)
	{
		it->Rc->pre = it;
		it->tot += it->Rc->tot;
		it->Lx = min(it->Lx, it->Rc->Lx);
		it->Rx = max(it->Rx, it->Rc->Rx);
		it->Ly = min(it->Ly, it->Rc->Ly);
		it->Ry = max(it->Ry, it->Rc->Ry);
		it->Lz = min(it->Lz, it->Rc->Lz);
		it->Rz = max(it->Rz, it->Rc->Rz);
	}
	return it;
}
 
void update(node *it, int delta)
{
	for (it->cur += delta; it; it = it->pre)
		it->tot += delta;
}
 
point q;
ld best;
int ans;
int cnt;
 
ld getdis(node *it)
{
	ld d;
	if (it->Lx <= q.x && q.x <= it->Rx)
	{
		if (it->Ly <= q.y && q.y <= it->Ry)
			d = 0;
		else
			d = min(abs(q.y-it->Ly), abs(q.y-it->Ry));
	}
	else
	{
		if (it->Ly <= q.y && q.y <= it->Ry)
			d = min(abs(q.x-it->Lx), abs(q.x-it->Rx));
		else
		{
			int dx = min(abs(q.x-it->Lx), abs(q.x-it->Rx));
			int dy = min(abs(q.y-it->Ly), abs(q.y-it->Ry));
			d = sqrtf((ld)dx*dx+(ld)dy*dy);
		}
	}
	return d+it->Lz;
}
 
void search(node *it)
{
	if (!it) return;
	if (!it->tot) return;
	if (it->cur)
	{
		ld cur = sqrtf((ld)(q.x-it->p->x)*(q.x-it->p->x)+(ld)(q.y-it->p->y)*(q.y-it->p->y))+it->p->z;
		if (cur < best)
		{
			best = cur;
			ans = it-tree;
		}
	}
	cnt ++;
	if (best < INF && cnt > 2000) return;
	ld Ld = INF, Rd = INF;
	if (it->Lc) Ld = getdis(it->Lc);
	if (it->Rc) Rd = getdis(it->Rc);
	if (Ld < Rd)
	{
		if (Ld < best) search(it->Lc);
		if (Rd < best) search(it->Rc);
	}
	else
	{
		if (Rd < best) search(it->Rc);
		if (Ld < best) search(it->Lc);
	}
}
 
vector<int> e[MAXN];
 
int main()
{
	
	timestamp = clock();
	
	int n, q;
	read(n);
	read(q);
	for (int i = 1; i <= n; ++ i)
	{
		int x, y, k;
		read(x);
		read(y);
		read(k);
		for (int j = 1; j <= k; ++ j)
		{
			int w;
			read(w);
			id[++ ::n] = pii(i, j);
			p[::n] = point{x, y, w};
		}
	}
	
	n = ::n;
	for (int i = 1; i <= n; ++ i)
		r[i] = i;
	root = build(1, n);
	
	puts("?");
	fflush(stdout);
	
	for (int k = 1; k <= q; ++ k)
	{
		for (auto svr : e[k])
			update(tree+svr, 1);
		read(::q.x);
		read(::q.y);
		best = INF;
		cnt = 0;
		search(root);
		//++ ans;
		printf("! %d %d\n", id[ans].X, id[ans].Y);
		if (k == q)
		{
			puts("end");
			fflush(stdout);
			break;
		}
		puts("?");
		fflush(stdout);
		
		update(tree+ans, -1);
		if (k+p[ans].z <= q)
			e[k+p[ans].z].push_back(ans);
	}
	
	return 0;
}
 