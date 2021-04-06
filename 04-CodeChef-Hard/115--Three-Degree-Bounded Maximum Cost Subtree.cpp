//pb_ds 20160711
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <cmath>
#include <iostream>
#include <queue>
using namespace std;
#define RG register
//#define IL inline
#define IL __inline__ __attribute__((always_inline))
#define For(i, a, b) for(RG int i = a, ___u = b; i <= ___u; ++i)
#define Dor(i, a, b) for(RG int i = b, ___d = a; i >= ___d; --i)
#define Rep(i, a, b) for(RG int i = a, ___u = b; i != ___u; ++i)
#define dmin(a, b) ((a) < (b) ? (a) : (b))
#define dmax(a, b) ((a) > (b) ? (a) : (b))
#define cmin(a, b) ((a) > (b) ? (a) = (b) : 1)
#define cmax(a, b) ((a) < (b) ? (a) = (b) : 1)
#define ddel(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))
#define dabs(i) ((i) > 0 ? (i) : -(i))
typedef long long ll;
typedef unsigned uint;

#include <vector>
#include <string>

namespace pb_ds
{   
	namespace io
	{
		const int MaxBuff = 1 << 15;
		const int Output = 1 << 23;
		char B[MaxBuff], *S = B, *T = B;
		//#define getc() getchar()
		#define getc() ((S == T) && (T = (S = B) + fread(B, 1, MaxBuff, stdin), S == T) ? 0 : *S++)
		char Out[Output], *iter = Out;
	}
	template<class Type> IL Type read()
	{
		using namespace io;
		RG char ch; RG Type ans = 0; RG bool neg = 0;
		while(ch = getc(), (ch < '0' || ch > '9') && ch != '-')     ;
		ch == '-' ? neg = 1 : ans = ch - '0';
		while(ch = getc(), '0' <= ch && ch <= '9') ans = ans * 10 + ch - '0';
		return neg ? -ans : ans;
	}
	IL int gets(RG char *s)
	{
		using namespace io;
		RG char *t = s, ch;
		while(ch = getc(), ch == ' ' || ch == '\n' || ch == '\r') ;	*s++ = ch;
		while(ch = getc(), ch != ' ' && ch != '\n' && ch != '\r')	*s++ = ch;
		*s = 0; return s - t;
	}
	template<class Type> IL void Print(RG Type x, RG char ch = '\n')
	{
		using namespace io;
		if(!x) *iter++ = '0';
		else
		{
			if(x < 0) *iter++ = '-', x = -x;
			static int s[100]; RG int t = 0;
			while(x) s[++t] = x % 10, x /= 10;
			while(t) *iter++ = '0' + s[t--];
		}
		*iter++ = ch;
	}

	const int MaxN = 200;
	const int MaxM = 1000;
	template<class T> IL void reinit(RG T& t) {t.~T(); new (&t) T;}
	struct Pointer{int to; Pointer *next;};
	Pointer mem[MaxM], *tot, *fir[MaxN];
	bool h[MaxN][MaxN];
	int l[MaxN][MaxN];
	int dfn[MaxN], low[MaxN], bel[MaxN], timer, Blo;
	int stack[MaxN], top;
	IL void link(RG int a, RG int b, RG int v)
	{
		h[a][b] = h[b][a] = 1;
		l[a][b] = l[b][a] = v;
		*++tot = (Pointer) {b, fir[a]}, fir[a] = tot;
		*++tot = (Pointer) {a, fir[b]}, fir[b] = tot;
	}
	struct S
	{
		int v; uint c;
		IL void Cmax(RG const S& s, RG int d = 0)
		{
			if(v > s.v + d) return;
			if(v == s.v + d) c += s.c;
			else v = s.v + d, c = s.c;
		}
		IL S operator + (RG const S& s) const
		{
			return (S) {v + s.v, c * s.c};
		}
		IL void operator += (RG const S& s)
		{
			v += s.v, c *= s.c;
		}
	} null = (S) {(int) -1e9, 0u}, ans;
	
	#define Fetch(s, i) (((s) >> ((i) << 1)) & 3)
	#define Bit(i) (1 << ((i) << 1))
	
	struct Block
	{
		static const int MaxB = 20;
		int pts[MaxB], n;
		bool H[MaxB][MaxB];
		int L[MaxB][MaxB];
		S *f, ret[4];
		bool *v;
		IL void init() 
		{
///*lgg*/printf("new block\n");
			n = 0;
		}
		IL void add(RG int p) 
		{
			pts[n++] = p;
///*lgg*/printf("pts p = %d\n", p);		
		}
		void work();
		
		vector<int> state[4];
		IL string format(RG int set)
		{
			RG string ret; Rep(i, 0, n) ret.push_back('0' + Fetch(set, i));
			return ret;
		}
		#define Format(set) format(set).c_str()
		const S& dp(RG int set, RG int E)
		{
			if(v[set]) return f[set]; v[set] = 1;
			RG S& s = f[set]; s = null;
			
			RG int p = 0;
			while(p != n && Fetch(set, p) != 1) ++p;
			if(p == n) return s = null;
			set -= Bit(p);
			if(!--E)
			{
				RG int q = 0;
				while(q != n && Fetch(set, q) != 1) ++q;
				if(q == n || !H[p][q]) return s = null;
				else s = (S) {L[p][q], 1u};
			}
			else
			{
				for(RG int i = 0; i != n; ++i)
					if(Fetch(set, i) > 1 && H[p][i])
						s.Cmax(dp(set - Bit(i), E), L[p][i]);
			}
///*lgg*/set+=Bit(p);if(s.c)printf("dp set = %s E = %d s = (%d, %u)\n", Format(set), E+1, f[set].v, f[set].c);	
			return s;
		}
		void dfs(RG int i, RG int set, RG int sum)
		{
			if(!i--) 
			{
				if(!set) return; if(sum & 1) return;
				if(dp(set, sum >> 1).c) 
///*lgg*/printf("new state set = %s E = %d f = (%d, %u)\n", Format(set), sum / 2, f[set].v, f[set].c),
					state[set & 3].push_back(set);
				return;
			}
			For(d, 0, 3) dfs(i, set << 2 | d, sum + d);
		}
	} blo[MaxN];
	
	IL vector<Block*> to_blocks(RG int p, RG int B = MaxN)
	{
		RG vector<Block*> ret;
///*lgg*/printf("to_blocks p = %d B = %d\n", p, B);
		for(RG Pointer *k = fir[p]; k; k = k->next)
			if(bel[k->to] < B) ret.push_back(blo + bel[k->to]);
		sort(ret.begin(), ret.end());
		ret.erase(unique(ret.begin(), ret.end()), ret.end());
		return ret;
	}
	
	void Block::work()
	{
		/*if(f) delete[] f;*/ f = new S[1 << (n << 1)];
		/*if(v) delete[] v;*/ v = new bool[1 << (n << 1)];
		memset(v, 0, 1 << (n << 1));
		Rep(i, 0, n) Rep(j, 0, n)
			H[i][j] = h[pts[i]][pts[j]],
			L[i][j] = l[pts[i]][pts[j]];
		For(i, 0, 3) reinit(state[i]);
		dfs(n, 0, 0);
		
		RG S F[n][4], g[4];
		RG vector<Block*> pto[MaxB];
		For(i, 0, 3) ret[i] = null;
		
		Rep(i, 1, n) 
		{
			pto[i] = to_blocks(pts[i], this - blo);
			Rep(j, 0, pto[i].size())
			{
///*lgg*/printf("edge blo[%d]->pts[%d] -> blo[%d]\n", this-blo,i,pto[i][j]-blo);
				pto[i][j]->work();
			}
		}
		
///*lgg*/printf("===== blo[%d] single point ======\n", this - blo);
		Rep(i, 0, n) // 散点枚举。散点在父连通块中统计答案，因此 0 不算在 ans 里面。
		{
///*lgg*/printf("pts[%d] = %d\n", i, pts[i]);
			RG S *f = F[i];
			f[0] = (S) {0, 1u};
			For(s, 1, 3) f[s] = null;
			Rep(j, 0, pto[i].size())
			{
				memcpy(g, f, sizeof g);
				for(RG int w = 1; w <= 3; ++w)
					for(RG int s = w; s <= 3; ++s)
						f[s].Cmax(g[s - w] + pto[i][j]->ret[w]);
			}
///*lgg*/For(s, 0, 3) if(f[s].c) printf("f[%d] = (%d, %u)\n", s, f[s].v, f[s].c);
			For(s, 0, 3) 
				if(i) ans.Cmax(f[s]);
				else ret[s].Cmax(f[s]);
		}
///*lgg*/printf("===== blo[%d] states ======\n", this - blo);
		For(dt, 0, 3) Rep(i, 0, state[dt].size())
		{
			RG int set = state[dt][i]; 
			RG S sol = f[set], tmp;
///*lgg*/printf("[STATE] dt = %d set = %s f = (%d, %u)\n", dt, Format(set), sol.v, sol.c);
			for(RG int i = n; i--; ) 
				if(Fetch(set, i) && (i || !dt))
				{
					tmp = null;
					For(s, 0, 3 - Fetch(set, i)) tmp.Cmax(F[i][s]);
					sol += tmp;
				}
///*lgg*/if(dt) For(s, 0, 3 - dt) if(F[0][s].c) printf("f[%d] = (%d, %u)\n", dt+s, (F[0][s]+sol).v, (F[0][s]+sol).c); 
///*lgg*/if(!dt) printf("sol = (%d, %u)\n", sol.v, sol.c);
			if(dt) For(s, 0, 3 - dt) ret[dt + s].Cmax(F[0][s] + sol); // 更新 ret
			else ans.Cmax(sol); // 更新 ans
		}
///*lgg*/For(s,0,3) if(ret[s].c) printf("ret[%d] = (%d, %u)\n", s, ret[s].v, ret[s].c);
///*lgg*/getchar();
	}
	
	void dfs(RG int i)
	{
		dfn[i] = low[i] = ++timer;
		stack[++top] = i;
		for(RG Pointer *k = fir[i]; k; k = k->next)	
			if(!dfn[k->to])
			{
				dfs(k->to);
				if(low[k->to] == dfn[i])
				{
					blo[++Blo].init();
					blo[Blo].add(i);
					RG int tmp;
					do blo[Blo].add(tmp = stack[top--]), bel[tmp] = Blo;
					while(tmp != k->to);
				}
				else cmin(low[i], low[k->to]);
			}
			else cmin(low[i], dfn[k->to]);
	}
	
	IL void main()
	{
		RG int (*F)() = read<int>;
		For(__, 1, F())
		{
			RG int n = F(), m = F();
			tot = mem;
			memset(fir + 1, 0, n * sizeof fir[0]);
			For(i, 1, n) For(j, 1, n) h[i][j] = 0;
			for(RG int x, y; m--; )
				x = F(), y = F(), link(x, y, F());
			timer = Blo = 0;
			memset(dfn + 1, 0, n << 2);
			ans = (S) {0, 1};
			For(i, 1, n) if(!dfn[i]) 
			{
				dfs(i);
				bel[i] = ++Blo;
				
				RG S f[4], g[4];
				RG vector<Block*> _to = to_blocks(i);
				RG Block **to = _to.data();
				f[0] = (S) {0, 1u};
				For(s, 1, 3) f[s] = null;
				Rep(j, 0, _to.size()) // 根 i 所在的连通块，根为它们的割点，因此仅仅统计根的答案。
				{
					to[j]->work();
					memcpy(g, f, sizeof g);
					for(RG int w = 1; w <= 3; ++w)
						for(RG int s = w; s <= 3; ++s)
							f[s].Cmax(g[s - w] + to[j]->ret[w]);
				}
///*lgg*/printf("Outside\n"); For(s,0,3)if(f[s].c) printf("f[%d] = (%d, %u)\n", i, f[s].v, f[s].c); getchar();
				For(s, 0, 3) ans.Cmax(f[s]);
				printf("%d %u\n", ans.v, ans.c);
			}
		}
		
	}
}

int main()
{
	#define FILE "dev"
	//freopen(FILE ".in", "r", stdin), freopen(FILE ".out", "w", stdout);
	pb_ds::main();
	fclose(stdin), fclose(stdout);  
}
/*

*/