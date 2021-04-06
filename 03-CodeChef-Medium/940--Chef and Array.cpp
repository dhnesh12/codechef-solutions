/*As you dislike it <3*/

#include <bits/stdc++.h>
#define    _fastIO       ios_base::sync_with_stdio(0);cin.tie(0);
#define    ll            long long int
#define    dbg           cout << "Freak" << endl
#define    mem(a,b)      memset((a),(b),sizeof(a))
#define    pb            push_back
#define    all(v)        v.begin(),v.end()
#define    rvs(a,n)      reverse(a, a + n)
#define    gcd(a,b)      __gcd(a,b)
#define    lcm(a,b)      (a * b) / gcd(a, b)
#define    PI            acos(-1)
#define    mx            100007
#define    PII           pair<ll, ll>
#define    gc            getchar()
#define    nl            '\n'
using namespace std;
const long long mod = 1e9+7;

int main()
{

    int n;
    scanf("%d", &n);
    int lg[n + 5];

    lg[1] = 0;
    for(int i = 2; i <= n; i++)lg[i] = lg[i / 2] + 1;

    int k = lg[n] + 1;

    int table[n + 5][k];

    for(int i = 0; i < n;i++){
        int a;
        scanf("%d", &a);
        table[i][0] = a;
    }

    for(int j = 1; j <= k; j++){
        for(int i = 0; i + (1 << j) <= n; i++){
            table[i][j] = max(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
    }

    int m, x, y;
    scanf("%d %d %d", &m, &x, &y);

    int sum = 0;

    while(m--){
        int l = min(x, y);
        int r = max(x, y);
        int j = lg[r - l + 1];
        int ans = max(table[l][j], table[r - (1 << j) + 1][j]);
        sum += ans;

        x = (x + 7) % (n - 1);
        y = (y + 11) % n;
    }

    printf("%d\n", sum);


    return 0;
}


