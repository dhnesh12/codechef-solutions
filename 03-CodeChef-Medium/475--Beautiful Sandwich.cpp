#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
const int N = 2e5 + 5, LOG = 18;
ll f[LOG][1<<LOG];
char s[N];
int pre[LOG], cnt[LOG][N];
int main()
{
	int n, k; scanf("%d%d", &n, &k);
	scanf("%s", s+1);
	for(int i=1; i<=n; i++)
	{
		for(int j=0; j<k; j++) cnt[j][i] = cnt[j][i-1];
		cnt[s[i]-'a'][i]++;
	}
	for(int i=1; i<=n; i++)
	{
		int c = s[i] - 'a';
		pre[c] = i;
		vector<pair<int, int>> alpha(k+1);
		for(int j=0; j<k; j++) alpha.emplace_back(pre[j], j);
		alpha.emplace_back(0, 0);
		sort(begin(alpha), end(alpha)); reverse(begin(alpha), end(alpha));
		int S = (1<<k) - 1;
		f[c][S]++;
		for(int j=0; j<k; j++)
		{
			if(!alpha[j].first) break;
			if(j) S ^= (1<<alpha[j].second);
			f[c][S] += 2*(cnt[c][alpha[j].first-1] - cnt[c][alpha[j+1].first]);
		} 
	}
	for(int c=0; c<k; c++)
		for(int i=0; i<k; i++)
			for(int j=1; j<(1<<k); j++)
				if(!((j>>i)&1)) f[c][j] += f[c][j|(1<<i)];
	int q; scanf("%d", &q);
	while(q--)
	{
		static char t[20];
		scanf("%s", t);
		int len = strlen(t), S = (1<<k) - 1;
		for(int i=0; i<len; i++) S ^= (1<<(t[i]-'a'));
		ll ans = 0;
		for(int i=0; i<k; i++) if((S>>i)&1) ans += f[i][S];
		printf("%lld\n", ans);
	}
	return 0;
}