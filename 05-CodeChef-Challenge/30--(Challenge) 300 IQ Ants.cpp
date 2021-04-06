#include <bits/stdc++.h>
using namespace std;

const int N = 1025, M = N * N;
int p[N][N], S = 1;
vector<int> I[250000];
set<int> r[N], c[N];

int main(){
	for(int i = 0; i < 250000; i++)I[i].clear();
	for(int i = 0; i < N; i++)r[i].clear(), c[i].clear();
	int n, x, y, cnt = 0, minR = 0, minC = 0, maxR = N - 1, maxC = N - 1;
	scanf("%d", &n);
	for(int i = 0; i < N; i++)for(int j = 0; j < N; j++)p[i][j] = M;
	for(int i = 1; i <= n; i++){
		scanf("%d %d", &x, &y);
		p[x][y] = min(p[x][y], i);
	}
	n = 0;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++){
			if(p[i][j] < M){
				n++;
				c[i].insert(j);
				r[j].insert(i);
			}
		}
	while(c[minC].empty())minC++;
	while(c[maxC].empty())maxC--;
	while(r[minR].empty())minR++;
	while(r[maxR].empty())maxR--;
	while(n > 1){
		int m = 2;
		I[cnt].push_back(m);
		if(minC == maxC){
			auto itS = c[minC].begin(); x = *itS;
			auto itE = c[minC].rbegin(); y = *itE;
			I[cnt].push_back(p[minC][x]);
			I[cnt].push_back(p[minC][y]);
			c[minC].erase(x);
			r[x].erase(minC);
			if(p[minC][x + 1] < M){
				--n;
			}
			else{
				p[minC][x + 1] = p[minC][x];
				c[minC].insert(x + 1);
				r[x + 1].insert(minC);
			}
			p[minC][x] = M;
		}
		else if(minR == maxR){
			auto itS = r[minR].begin(); x = *itS;
			auto itE = r[minR].rbegin(); y = *itE;
			I[cnt].push_back(p[x][minR]);
			I[cnt].push_back(p[y][minR]);
			r[minR].erase(x);
			c[x].erase(minR);
			if(p[x + 1][minR] < M){
				--n;
			}
			else{
				p[x + 1][minR] = p[x][minR];
				r[minR].insert(x + 1);
				c[x + 1].insert(minR);
			}
			p[x][minR] = M;
		}
		else if(n == 2){
			auto itS = c[minC].begin();
			auto itE = c[maxC].begin();
			int j1 = *itS, j2 = *itE, di = maxC - minC, dj = (j1 < j2) ? j2 - j1 : j1 - j2, d = __gcd(di, dj);
			I[cnt].push_back(p[minC][j1]);
			I[cnt].push_back(p[maxC][j2]);
			c[minC].erase(j1);
			r[j1].erase(minC);
			if(d == 1){
				--n;
			}
			else{
				di /= d; dj /= d; di += minC;
				int jj = (j1 < j2) ? j1 + dj : j1 - dj;
				p[di][jj] = p[minC][j1];
				p[minC][j1] = M;
				c[di].insert(jj);
				r[jj].insert(di);
				while(c[minC].empty())minC++;
				while(c[maxC].empty())maxC--;
				while(r[minR].empty())minR++;
				while(r[maxR].empty())maxR--;
			}
		}
		else{
			//if(n > 100000)S = 2;
			//else S = 1;
			
			m = 1;
			auto itS = c[minC].begin();
			x = minC; y = *itS;
			int s = S, nx = x + 1, dd = M, f;
			I[cnt].push_back(p[x][y]);
			while(s){
				if(nx > maxC)break;
				f = 0;
				for(auto it = c[nx].begin(); it != c[nx].end(); it++){
					int dy = (*it) - y;
					if(dd <= dy)break;
					if(s <= dy && __gcd(nx - x, dy) == 1){
						c[x].erase(y);
						r[y].erase(x);
						p[x][y] = M;
						--n;
						dd = dy;
						y += dy;
						x = nx++;
						++m;
						I[cnt].push_back(p[x][y]);
						s--;
						f = 1;
						break;
					}
				}
				if(f == 0)nx++;
			}
			s = S, nx = x + 1, dd = M;
			while(s){
				if(nx > maxC)break;
				f = 0;
				for(auto it = c[nx].rbegin(); it != c[nx].rend(); it++){
					int dy = y - (*it);
					if(dd <= dy)break;
					if(s <= dy && __gcd(nx - x, dy) == 1){
						c[x].erase(y);
						r[y].erase(x);
						p[x][y] = M;
						--n;
						dd = dy;
						y -= dy;
						x = nx++;
						++m;
						I[cnt].push_back(p[x][y]);
						s--;
						f = 1;
						break;
					}
				}
				if(f == 0)nx++;
			}

			if(m == 1){
				m = 2;
				auto itE = c[maxC].begin();
				int j1 = *itS, j2 = *itE, di = maxC - minC, dj = (j1 < j2) ? j2 - j1 : j1 - j2, d = __gcd(di, dj);
				I[cnt].push_back(p[maxC][j2]);
				c[minC].erase(j1);
				r[j1].erase(minC);
				if(dj == 0){
					x = minC + 1; y = j1;
				}	
				else{
					di /= d;
					dj /= d;
					x = minC + di;
					y = (j1 < j2) ? j1 + dj : j1 - dj;
				}
				if(p[x][y] < M){
					--n;
				}
				else{
					p[x][y] = p[minC][j1];
					c[x].insert(y);
					r[y].insert(x);
				}
				p[minC][j1] = M;
			}

			while(c[minC].empty())minC++;
			while(c[maxC].empty())maxC--;
			while(r[minR].empty())minR++;
			while(r[maxR].empty())maxR--;
		}
		I[cnt++][0] = m;
	}
	printf("%d\n", cnt);
	for(int i = 0; i < cnt; i++){
		printf("%d", I[i][0]);
		for(int j = 1; j <= I[i][0]; j++)
			printf(" %d", I[i][j]);
		printf("\n");	
	}
	return 0;
}
