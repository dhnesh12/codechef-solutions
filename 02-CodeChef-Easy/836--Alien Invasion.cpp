#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define f first
#define s second
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vector<int>>
#define vii vector<pair<int, int>>
#define vvb vector<vector<bool>>
#define piii pair<int, pair<int, int>>
#define vvpii vector<vector<pair<int, int>>>
#define inf 987654321
#define pb push_back
#define p push
#define ll long long
#define ull unsigned long long
#define g get
#define dbl double

int N, D, T;
int space[100005];

bool ok (long double r)
{
    long double t = -1;
    for (int i = 0; i < N; i++)
    {
        //cout << t << " " << space[i] + D << endl;
        if (t > space[i] + D)
            return false;
        t = max(t, (long double)space[i]) + r;
    }
    return true;
}

int main() {
    cin >> T;
    while (T--)
    {
        scanf("%d%d", &N, &D);
        for (int i = 0; i < N; i++)
            scanf("%d", &space[i]);
        sort(space, space + N);
        long double loc = 0, am = 1e9;
        for (int i = 0; i < 55; i++)
        {
            while (loc + am > 0 && ok(loc + am))
                loc += am;
            //printf("%Lf\n", am);
            am /= 2;
        }
        printf("%Lf\n", loc);
    }
}