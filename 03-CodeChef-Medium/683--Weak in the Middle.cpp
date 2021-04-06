#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 100005
#define inf 0x3f3f3f3f
#define INF 2147483647
int a[maxn], sta[maxn];
int ans[maxn], p, m[maxn];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--){
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        for (int i = 0; i < n; ++i){
            while (p > 1 && a[sta[p]] < a[sta[p - 1]] && a[sta[p]] < a[i]){
            	ans[sta[p]] = std::max(m[sta[p]], m[sta[p - 1]]) + 1;
                m[sta[p - 1]] = ans[sta[p]];
                --p;
            }
            sta[++p] = i;
        }
        for (int i = 0; i < n; ++i) printf(i == n - 1 ? "%d\n" : "%d ", ans[i]);
        memset(ans, 0, sizeof(ans));
        memset(m, 0, sizeof(m));
        p = 0;
    }
    return 0;
}