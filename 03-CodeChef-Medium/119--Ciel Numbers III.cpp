#include<iostream>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<string>
#include<sstream>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<vector>
#include<algorithm>
#pragma comment(linker, "/STACK:16777216")
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define LL long long
#define bit __builtin_popcountll
#define sqr(x) (x) * (x)
using namespace std;
typedef pair<int, int> pii;
const double eps = 1e-9, pi = acos(-1.0);
const int maxn = (int)1e5 + 10;
char s[maxn];
int cnt[10],id[] = {0,0,0,3,0,5,0,0,8,0};
int D(int d3, int d5, int d8, int L) {
	int a3, a5, a8, res = L, d0 = L - d3 - d5 - d8;
	if(d3 <= d5 + d0 && d5 + d0 <= d8) return d0;
	a3 = d3; a5 = (L - d3) / 2; a8 = (L - d3 + 1) / 2;
	if (a3 <= a5 && a5 <= a8) res = min(res,max(a3 - d3,0) + max(a5 - d5,0) + max(a8 - d8,0));
	a3 = (L - d8) / 2; a5 = (L - d8 + 1) / 2; a8 = d8;
	if (a3 <= a5 && a5 <= a8) res = min(res,max(a3 - d3,0) + max(a5 - d5,0) + max(a8 - d8,0));
	a3 = L / 3; a5 = (L + 1) / 3; a8 = (L + 2) / 3;
	res = min(res,max(a3 - d3,0) + max(a5 - d5,0) + max(a8 - d8,0));
	return res;
}
bool exist(int n3, int n5, int n8, int k, int L, int x) {
	return D(n3,n5,n8,L) - (L - k) <= x && x <= D(n3,n5,n8,L);
}
void solve() {
	int x;
	scanf("%d%s", &x, &s);
	int L = strlen(s);
	for(int i = 0; i < L; i++) s[i] -= '0';
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i < L; i++) cnt[id[s[i]]]++;
	if(exist(cnt[3], cnt[5], cnt[8], L, L, x)) {
		for(int i = 0; i < L; i++) s[i] += '0';
		printf("%s\n", s);
		return;
	}
	for(int i = L - 1; i >= 0; i--) {
		cnt[id[s[i]]]--;
		for(int j = s[i] - 1; j >= (i == 0 && L > 1 ? 1 : 0); j--) {
			cnt[id[j]]++;
			if(exist(cnt[3],cnt[5],cnt[8],i + 1,L,x)) {
				s[i] = j;
				for(int k = i + 1; k < L; k++) {
					for(int r = 9; r >= 0; r--) {
						cnt[id[r]]++;
						if(exist(cnt[3],cnt[5],cnt[8],k + 1,L,x)) {
							s[k] = r;
							break;
						}
						cnt[id[r]]--;
					}
				}
				for (int i = 0; i < L; i++) s[i] += '0';
				printf("%s\n",s);
				return;
			}
			cnt[id[j]]--;
		}
	}
	if(L == 1 || !exist(0, 0, 0, 0, L - 1, x)) {
		printf("-1\n");
		return;
	}
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i < L - 1; i++) {
		for(int j = 9; j >= 0; j--) {
			cnt[id[j]]++;
			if(exist(cnt[3], cnt[5], cnt[8], i + 1, L - 1, x)) {
				printf("%d", j);
				break;
			}
			cnt[id[j]]--;
		}
	}
	puts("");
}
int main()
{
	int T;
	scanf("%d", &T);	
	while(T--) solve();
	return 0;
}  