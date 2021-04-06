#include <bits/stdc++.h>
using namespace std;\

const int MOD = 1000000007;
const int N = 1048576;

#define MaXN 1000000
#define MaXPOWN 1048576		// 2^(ceil(log_2(MaXN)))
#define MaXLEV 21			// ceil(log_2(MaXN)) + 1
int table[MaXLEV][MaXPOWN];
int maxlev, size;

int n , P , q;
int ar[N];
int b[N];

long long func(long long x, long long y = 1)
{
    return x * y % P;
}
void build(int a[],int level=0,int l=0, int r=size)
{
    int m = (l+r)/2;

    table[level][m] = func(a[m]);
    for(int i=m-1;i>=l;i--)
        table[level][i] = func(table[level][i+1] , a[i]);

    if(m+1 < r) {
        table[level][m+1] = func(a[m+1]);
        for(int i=m+2;i<r;i++)
            table[level][i] = func(table[level][i-1] , a[i]);
    }
    if(l + 1 != r){		// r - l > 1
        build(a, level+1, l, m);
        build(a, level+1, m, r);
    }
}
int query(int a[], int x, int y)
{
  if(x == y)
    return a[x]%P;
  int k2 = __builtin_clz(x^y) ^ 31;
  int lev = maxlev - 1 - k2;
  int ans = table[lev][x];
  if(y & ((1<<k2) - 1))	// y % (1<<k2)
    ans = func(ans , table[lev][y]);
  return ans;
}

void tc(int test_case)
{

    scanf("%d%d%d", &n, &P, &q);
    for(int i=0; i<n; i++){
        scanf("%d", &ar[i]);
    }
    int t = (q/64) + 2;
    for(int i=0; i<t; i++){
        scanf("%d", &b[i]);
    }

    /// initialization
    size = n;       // n is the size of the original array
    maxlev = __builtin_clz(n) ^ 31;		// floor(log_2(n))
    if( (1<<maxlev) != n)
        size = 1<<++maxlev;

    build(ar);      // arr is the original array to build on

    int x = 0;
    int l , r;
    for(int i=0; i<q; i++){
        if(i % 64 == 0){
            l = (b[i/64] + x) % n;
            r = (b[i/64+1] + x) % n;
        }
        else{
            l = (l + x) % n;
            r = (r + x) % n;
        }
        if (l > r) swap(l, r);
        x = query(ar , l , r);
        x = (x + 1) % P;
    }
    printf("%d\n", x);

    return;
}

int main() {

    int t;
    scanf("%d",&t);
	for(int i=1 ; i<=t ;i++){
        tc(i);
	}
    return 0;
}
