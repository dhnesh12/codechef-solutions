#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;
 
typedef pair <int, int> ii;
 
const int MaxN = 415;
const int Maxn = 205;
const int Maxm = 1000000;
 
int t;
int B, G, L;
int N;
vector <int> bneigh[Maxn], gneigh[Maxn];
int R[MaxN][MaxN];
bool fromb[Maxn][Maxn], fromg[Maxn][Maxn];
vector <int> neigh[MaxN];
int flow[MaxN], par[MaxN];
int seq[Maxm], slen;
int res[Maxn];
 
void addEdge(int a, int b, int cap)
{
	R[a][b] = cap; R[b][a] = 0;
	neigh[a].push_back(b);
	neigh[b].push_back(a);
}
 
void Clear(int a, int b)
{
	R[a][b] = R[b][a] = 0;
}
 
void Reverse(int a, int b)
{
	swap(R[a][b], R[b][a]);
}
 
int getFlow()
{
	for (int i = 0; i < slen; i++)
		flow[seq[i]] = 0;
	slen = 0;
	flow[0] = Maxn;
	priority_queue <ii> Q; Q.push(ii(flow[0], 0));
	while (!Q.empty()) {
		int f = Q.top().first, v = Q.top().second; Q.pop();
		if (f != flow[v]) continue;
		if (v == N - 1) break;
		for (int i = 0; i < neigh[v].size(); i++) {
			int u = neigh[v][i];
			if (min(f, R[v][u]) > flow[u]) {
				flow[u] = min(f, R[v][u]); par[u] = v;
				Q.push(ii(flow[u], u));
				seq[slen++] = u;
			}
		}
	}
	int v = N - 1;
	int res = flow[v];
	if (!res) return 0;
	while (v) {
		int u = par[v];
		R[u][v] -= res; R[v][u] += res;
		v = u;
	}
	return res;
}
 
int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &B, &G, &L);
		N = 2 + B + G;
		vector <ii> bseq, gseq;
		for (int i = 1; i <= B; i++) {
			int S, T, cnt; scanf("%d %d %d", &S, &T, &cnt);
			bneigh[i].resize(cnt);
			for (int j = 0; j < cnt; j++) {
				scanf("%d", &bneigh[i][j]);
				bneigh[i][j]++;
			}
			bseq.push_back(ii(S, i)); bseq.push_back(ii(T, -i));
		}
		sort(bseq.begin(), bseq.end());
		for (int i = 1; i <= G; i++) {
			int S, T, cnt; scanf("%d %d %d", &S, &T, &cnt);
			gneigh[i].resize(cnt);
			for (int j = 0; j < cnt; j++) {
				scanf("%d", &gneigh[i][j]); 
				gneigh[i][j]++;
			}
			gseq.push_back(ii(S, i)); gseq.push_back(ii(T, -i));
		}
		sort(gseq.begin(), gseq.end());
		for (int i = 0; i <= min(B, G); i++)
			res[i] = 0;
		for (int i = 0; i < N; i++) {
			neigh[i].clear();
			for (int j = 0; j < N; j++)
				R[i][j] = 0;
		}
		int lst = 0, was = 0;
		int i = 0, j = 0;
		while (i < bseq.size() || j < gseq.size()) {
			if (i < bseq.size() && (j >= gseq.size() || bseq[i].first <= gseq[j].first)) {
				res[was] += bseq[i].first - lst; lst = bseq[i].first;
				int ind = bseq[i].second;
				if (ind > 0) {
					addEdge(0, ind, 1);
					for (int l = 0; l < bneigh[ind].size(); l++) {
						int g = bneigh[ind][l];
						fromb[ind][g] = true;
						if (fromg[g][ind]) addEdge(ind, B + g, 1);
					}
				} else {
					ind = -ind;
					if (R[ind][0] > 0) was -= R[ind][0];
					Clear(0, ind);
					for (int l = 0; l < bneigh[ind].size(); l++) {
						int g = bneigh[ind][l];
						if (R[B + g][ind] > 0) { Clear(ind, B + g); Reverse(B + g, N - 1); }
						fromb[ind][g] = false;
					}
				}
				i++;
			} else {
				res[was] += gseq[j].first - lst; lst = gseq[j].first;
				int ind = gseq[j].second;
				if (ind > 0) {
					addEdge(B + ind, N - 1, 1);
					for (int l = 0; l < gneigh[ind].size(); l++) {
						int b = gneigh[ind][l];
						fromg[ind][b] = true;
						if (fromb[b][ind]) addEdge(b, B + ind, 1);
					}
				} else {
					ind = -ind;
					if (R[N - 1][B + ind] > 0) was -= R[N - 1][B + ind];
					Clear(B + ind, N - 1);
					for (int l = 0; l < gneigh[ind].size(); l++) {
						int b = gneigh[ind][l];
						if (R[B + ind][b] > 0) { Clear(b, B + ind); Reverse(0, b); }
						fromg[ind][b] = false;
					}
				}
				j++;
			}
			int f;
			while ((f = getFlow()) != 0)
				was += f;
		}
		res[was] += L - lst;
		for (int i = 0; i <= min(B, G); i++)
			printf("%d%c", res[i], i + 1 <= min(B, G)? ' ': '\n');
	}
	return 0;
} 