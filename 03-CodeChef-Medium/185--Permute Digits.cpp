#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int Maxn = 10;
const int Maxm = 1400;

int T;
int X;
int cnt1[Maxn], cnt2[Maxn];
int pw1[Maxn], pw2[Maxn];
int has1[Maxm], has2[Maxm];
vector <int> my1[Maxm], my2[Maxm];
bool inmy1[Maxm][Maxn], inmy2[Maxm][Maxn];
ll dp[Maxm][Maxm][2];
void Record(const string &S, int cnt[], int pw[], int has[], vector <int> my[], bool inmy[][Maxn])
{
	fill(cnt, cnt + Maxn, 0);
	for (int i = 0; i < S.length(); i++)
		cnt[S[i] - '0']++;
	pw[0] = 1;
	for (int i = 1; i < X; i++)
		pw[i] = pw[i - 1] * (cnt[i - 1] + 1);
	for (int i = 0; i < Maxm; i++) {
		has[i] = 0; my[i].clear();
		for (int j = 0; j < X; j++) {
			int dig = i / pw[j] % (cnt[j] + 1);
			has[i] += dig;
			if (dig < cnt[j]) my[i].push_back(j);
			inmy[i][j] = dig < cnt[j];
		}
	}
}
int main()
{
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &X);
		string A, B, C; cin >> A >> B >> C;
		while (C.length() < A.length() || C.length() < B.length())
			C = "0" + C;
		Record(A, cnt1, pw1, has1, my1, inmy1);
		Record(B, cnt2, pw2, has2, my2, inmy2);
		fill((ll*)dp, (ll*)dp + Maxm * Maxm * 2, 0); dp[0][0][0] = 1;
		ll res = 0;
		for (int i = 0; i < Maxm; i++)
			for (int j = 0; j < Maxm; j++)
				for (int l = 0; l < 2; l++) if (dp[i][j][l]) {
					int cur = max(has1[i], has2[j]);
					int ind = int(C.length()) - 1 - cur;
					if (cur >= A.length() && cur >= B.length()) {
						if (cur + 1 == C.length() && C[0] - '0' == l || cur == C.length() && l == 0) 
							res += dp[i][j][l];
					} else if (cur >= A.length()) {
						int nd = (X + int(C[ind] - '0') - l) % X;
						if (inmy2[j][nd]) dp[i][j + pw2[nd]][(nd + l) / X] += dp[i][j][l];
					} else if (cur >= B.length()) {
						int nd = (X + int(C[ind] - '0') - l) % X;
						if (inmy1[i][nd]) dp[i + pw1[nd]][j][(nd + l) / X] += dp[i][j][l];
					} else for (int z = 0; z < my1[i].size(); z++) {
						int dig = my1[i][z];
						int nd = (X + int(C[ind] - '0') - dig - l) % X;
						if (inmy2[j][nd]) dp[i + pw1[dig]][j + pw2[nd]][(dig + nd + l) / X] += dp[i][j][l];
					}
				}
		cout << res << endl;
	}
	return 0;
}