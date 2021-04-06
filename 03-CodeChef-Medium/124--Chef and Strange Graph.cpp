#include <bits/stdc++.h>
using namespace std;
 
const int Maxn = 10005;
 
int t;
int n, m;
bool con[Maxn][Maxn];
vector <int> neigh[Maxn];
int A[Maxn], B[Maxn];
int K;
set <int> S[Maxn];
bool forb[Maxn][Maxn];
int mya[Maxn], myb[Maxn];
bool tk[Maxn];
int tmp[Maxn], tlen;
vector <int> C;
 
void createNew()
{
	K++; S[K].clear();
}
 
void Connect(int e, int v1, int v2)
{
	S[v1].insert(e);
	S[v2].insert(e);
	mya[e] = min(v1, v2); 
	myb[e] = max(v1, v2);
	forb[mya[e]][myb[e]] = true;
	tk[e] = true;
}
 
void findClique()
{
	for (int i = 1; i <= m; i++) {
		int a = 0, b = 0;
		tlen = 0;
		while (a < neigh[A[i]].size() && b < neigh[B[i]].size())
			if (neigh[A[i]][a] < neigh[B[i]][b]) a++;
			else if (neigh[B[i]][b] < neigh[A[i]][a]) b++;
			else { tmp[tlen++] = neigh[A[i]][a]; a++; b++; }
		for (int j = 0; j < tlen; j++)
			for (int l = j + 1; l < tlen; l++)
				if (con[tmp[j]][tmp[l]]) {
					C.clear();
					C.push_back(A[i]);
					C.push_back(B[i]);
					C.push_back(tmp[j]);
					C.push_back(tmp[l]);
					createNew();
					for (int z = 0; z < C.size(); z++) {
						createNew();
						Connect(C[z], 1, K);
					}
					return;
				}
	}
	assert(false);
}
 
bool Check(int v, int e)
{
	int pnt = 0;
	for (set <int>::iterator it = S[v].begin(); it != S[v].end(); it++) {
		while (pnt < neigh[e].size() && neigh[e][pnt] < *it) pnt++;
		if (pnt >= neigh[e].size() || neigh[e][pnt] != *it) return false;
		pnt++;
	}
	return true;
}

void Fill(int e)
{
	if (tk[e]) return;
	vector <int> tmp;
	for (int i = 0; i < neigh[e].size(); i++) {
		int e2 = neigh[e][i];
		if (tk[e2]) {
			tmp.push_back(mya[e2]);
			tmp.push_back(myb[e2]);
		}
	}
	sort(tmp.begin(), tmp.end()); tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
	vector <int> wr;
	for (int i = 0; i < tmp.size() && wr.size() < 2; i++)
		if (wr.size() == 0 || !forb[wr[0]][tmp[i]])
			if (Check(tmp[i], e)) wr.push_back(tmp[i]);
	if (wr.size() == 2) Connect(e, wr[0], wr[1]);
	else {
		createNew(); Connect(e, wr[0], K);
	}
	for (int i = 0; i < neigh[e].size(); i++)
		Fill(neigh[e][i]);
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			tk[i] = false;
			neigh[i].clear();
			for (int j = 1; j <= n; j++)
				con[i][j] = false;
		}
		for (int i = 1; i <= m; i++) {
			int a, b; scanf("%d %d", &a, &b);
			con[a][b] = con[b][a] = true;
			neigh[a].push_back(b);
			neigh[b].push_back(a);
			A[i] = a; B[i] = b;
		}
		for (int i = 1; i <= K; i++)
			for (int j = 1; j <= K; j++)
				forb[i][j] = false;
		K = 0;
		for (int i = 1; i <= n; i++)
			sort(neigh[i].begin(), neigh[i].end());
		findClique();
		for (int i = 0; i < C.size(); i++)
			for (int j = 0; j < neigh[C[i]].size(); j++)
				Fill(neigh[C[i]][j]);
		printf("%d\n", K);
		for (int i = 1; i <= n; i++) {
			printf("%d %d\n", mya[i], myb[i]);
			assert(mya[i] > 0 && myb[i] > 0);
		}
	}
	return 0;
} 