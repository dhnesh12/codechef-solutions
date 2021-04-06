/**
 ____ ____ ____ ____ ____
||a |||t |||o |||d |||o ||
||__|||__|||__|||__|||__||
|/__\|/__\|/__\|/__\|/__\|

**/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N_MAX = 100002;
const int M_MAX = 100002;
const int K_MAX = 200002;
const int NM_MAX = 200002;

const int MOD = 1e9+7;

int pwr (int a, int b)
{
    if(b == 0)
        return 1;
    if(b & 1)
        return 1LL * a * pwr(a, (b ^ 1)) % MOD;
    int aux = pwr(a, (b >> 1));
    return 1LL * aux * aux % MOD;
}

int n, d;

int a[N_MAX];

int m;

int upos[M_MAX], uval[M_MAX];

map <int, int> mp;

int k;
int val[K_MAX];
int occ[K_MAX];

map <int, int> pos;

int fact[NM_MAX];
int ifact[NM_MAX];

int inv[NM_MAX];

int x[K_MAX];

int answer = 1;

void updateInsert (int p)
{
    occ[p]++;
    answer = 1LL * answer * (x[p] + occ[p]) % MOD;
    for(int i = p + 1; i <= k && val[p] + d > val[i]; i++)
    {
        x[i]++;
        if(occ[i] != 0)
        {
            answer = 1LL * answer * inv[x[i]] % MOD;
            answer = 1LL * answer * (x[i] + occ[i]) % MOD;
        }
    }
}

void updateErase (int p)
{
    answer = 1LL * answer * inv[x[p] + occ[p]] % MOD;
    occ[p]--;
    for(int i = p + 1; i <= k && val[p] + d > val[i]; i++)
    {
        if(occ[i] != 0)
        {
            answer = 1LL * answer * inv[x[i] + occ[i]] % MOD;
            answer = 1LL * answer * x[i] % MOD;
        }
        x[i]--;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> d;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> m;
    for(int i = 1; i <= m; i++)
        cin >> upos[i] >> uval[i];
    for(int i = 1; i <= n; i++)
        mp[a[i]]++;
    for(int i = 1; i <= m; i++)
        mp[uval[i]];
    for(map <int, int> :: iterator it = mp.begin(); it != mp.end(); it++)
    {
        k++;
        val[k] = it->first;
        occ[k] = it->second;
        pos[it->first] = k;
    }
    fact[0] = ifact[0] = 1;
    for(int i = 1; i <= n + m; i++)
    {
        inv[i] = pwr(i, MOD - 2);
        fact[i] = 1LL * fact[i - 1] * i % MOD;
        ifact[i] = pwr(fact[i], MOD - 2);
    }
    for(int i = 1; i <= k; i++)
    {
        for(int j = i - 1; j >= 1 && val[j] + d > val[i]; j--)
            x[i] += occ[j];
        if(occ[i] != 0)
            answer = 1LL * answer * fact[x[i] + occ[i]] % MOD * ifact[x[i]] % MOD;
    }
    for(int i = 1; i <= m; i++)
    {
        int p1 = pos[a[upos[i]]];
        int p2 = pos[uval[i]];
        updateInsert(p2);
        updateErase(p1);
        a[upos[i]] = uval[i];
        cout << answer << "\n";
    }
    return 0;
}
