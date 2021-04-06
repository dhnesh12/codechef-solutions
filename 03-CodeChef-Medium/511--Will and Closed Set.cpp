#include<bits/stdc++.h>
using namespace std;

#define Death Komachi 
#define Uni All right
#define REP(i,a,b) for(int i=(a),i##_end_=(b);i<i##_end_;++i)
#define DREP(i,a,b) for(int i=(a),i##_end_=(b);i>i##_end_;--i)
#define LL long long
#define M 64
#define Mod 1000000007
#define MX 200004

int Gcd[M][M], C[M][M];
bool Mark[M];
int T, n, m, L, K, Ans;
int Q[29][MX], R[M];

void DFS(int x, int S){
	bool Flag = 1;
	int i = x - 1;
	if (S & (1 << i))
		REP(j, 2, x - 1) if (S & (1 << j))
			if (Gcd[i][j] < x && !(S & (1 << Gcd[i][j]))) {
				Flag = 0; break;
			}
	if (!Flag) return;
	Q[x][R[x]++] = S;
	if (x == 28) return;
	if (Mark[x]) DFS(x + 1, S | (1 << x));
	else {
		DFS(x + 1, S);
		DFS(x + 1, S | (1 << x));
	}
}

int main() {
	REP(i, 1, M) REP(j, 1, M) Gcd[i][j] = __gcd(i, j);
	REP(i, 0, M) REP(j, C[i][0] = C[i][i] = 1, i)
		C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod;
	
	Mark[11] = Mark[13] = Mark[17] = Mark[19] = Mark[23] = 1;
	DFS(1, 0);
	
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &n, &K, &L);
		
		int QS = 0, PS = 0; ++L;
		REP(i, 0, n) {
			int x;
			scanf("%d", &x);
			QS |= 1 << x;
		}
		PS = QS;
		REP(i, 11, L) PS |= Mark[i] << i;
		
		Ans = 0;
		int S, s, p;
		REP(i, 0, R[L]) {
			S = Q[L][i];
			if ((S & QS) != QS) continue;
			s = __builtin_popcount(S);
			p = __builtin_popcount(S^PS);
			if (p <= K)
				Ans = (Ans + C[s + K - p - 1][K - p]) % Mod;
		}
		printf("%d\n",Ans);
	}
	return 0;
}

