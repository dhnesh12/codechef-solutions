#include<bits/stdc++.h>
using namespace std;

const int N = 700;
const int MAXNODE = N*N + 5;
#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(E * sqrt(V))
 */
#define HK HopcroftKarp
namespace HopcroftKarp {
  const int maxv = MAXNODE + 5;
  const int maxe = MAXNODE * 5 + 5;
  int nx, ny, E, nmatches;
  int adj[maxe], nxt[maxe];
  int lst[maxv], ptr[maxv], lev[maxv], que[maxv], matx[maxv], maty[maxv];
  void init(int _nx, int _ny) {
      nx = _nx, ny = _ny;
      E = nmatches = 0, fill_n(lst, nx, -1);
      fill_n(matx, nx, -1), fill_n(maty, ny, -1);
  }
  void add(int x, int y) {
      adj[E] = y, nxt[E] = lst[x], lst[x] = E++;
  }
  int bfs() {
      int qh = 0, qe = 0;
      for (int x = 0; x < nx; x++) {
          if (~matx[x]) {
              lev[x] = 0;
          }
          else {
              lev[x] = 1;
              que[qe++] = x;
          }
      }
      int res = 0;
      while (qh < qe) {
          int x = que[qh++];
          for (int e = lst[x]; ~e; e = nxt[e]) {
              int y = adj[e];
              if (!~maty[y]) {
                  res = 1;
              }
              else if (!lev[maty[y]]) {
                  lev[maty[y]] = lev[x] + 1;
                  que[qe++] = maty[y];
              }
          }
      }
      return res;
  }
  int dfs(int x) {
      for (int& e = ptr[x]; ~e; e = nxt[e]) {
          int y = adj[e];
          if (!~maty[y] || (lev[maty[y]] == lev[x] + 1 && dfs(maty[y]))) {
              matx[x] = y;
              maty[y] = x;
              return 1;
          }
      }
      return 0;
  }
  int maxmat() {
      while (bfs()) {
          for (int x = 0; x < nx; x++) {
              ptr[x] = lst[x];
          }
          for (int x = 0; x < nx; x++) {
              if (!~matx[x]) {
                  nmatches += dfs(x);
              }
          }
      }
      return nmatches;
  }
}

int n,m;

//Graph g;

char li[N+5][N+5];
int p[4] = {1,1,-1,-1};
int q[4] = {-1,1,-1,1};

int hashPair(int x, int y){
	return x * m + y ;
}

set<int> oof;

int makeGraph(){
	HK::init(n*m,n*m);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
//			if((i+j)%4 != x) continue;
			if(li[i][j] != 'F') continue;
			if((i/2)%2 == 1) continue;
			for(int k=0;k<4;k++){
				int ni = i+2*p[k];
				int nj = j+2*q[k];
				int pi = i+p[k];
				int pj = j+q[k];
				if(ni < 0 || ni >= n || nj < 0 || nj >= m || li[pi][pj] == 'P' || li[ni][nj] != 'F') continue;
				HK::add(hashPair(i,j) , hashPair(ni,nj));
//				g.addEdge(hashPair(i,j),hashPair(ni,nj),1);
//				int awal = hashPair(i,j);
//				int akhir = hashPair(ni,nj);
//				if(oof.find(awal) == oof.end()){
//					g.addEdge(0,awal,1);
//					oof.insert(awal);
//				}
//				if(oof.find(akhir) == oof.end()){
//					g.addEdge(akhir,n*m+1,1);
//					oof.insert(akhir);
//				}
			}
		}
	}
	
//	for(int i=0;i<n;i++){
//		for(int j=0;j<m;j++){
//			if(li[i][j] != 'F') continue;
//			if((i/2)%2 == 0) g.addEdge(0,hashPair(i,j),1);
//			else g.addEdge(hashPair(i,j),n*m+1,1);
//		}
//	}
//	return g.dinic(0,n*m+1);
	return HK::maxmat();
}

int main(){
	while(scanf("%d%d",&n,&m) && (n+m) != 0){
		for(int i=0;i<n;i++){
			scanf("%s",li[i]);
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(li[i][j] != 'G') continue;
				for(int k=0;k<4;k++){
					int ni = i+2*p[k];
					int nj = j+2*q[k];
					int pi = i+p[k];
					int pj = j+q[k];
					if(ni < 0 || ni >= n || nj < 0 || nj >= m || li[pi][pj] == 'P' || li[ni][nj] != 'F') continue;
					li[ni][nj] = 'O';
				}
			}
		}
		
		int awal = 0;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(li[i][j] == 'F') awal++;
//				printf("%c",li[i][j]);
			}
//			printf("\n");
		}
		int ans = makeGraph();
//		for(int i=0;i<4;i++){
//				ans+=makeGraph(i);
//		}
//		printf(">> %d\n",ans);
		printf("%d\n",awal - ans);
	}
	return 0;
}
