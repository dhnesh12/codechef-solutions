#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long ll;

struct pkt
{
    ll x, y;
};

struct przedzial
{
    pkt p, k;
};

const przedzial INF = {{1000000001, 1000000001}, {1000000001, 1000000001}};

ll maxi(ll a, ll b)
{
    if (a > b) return a;
    else return b;
}

ll mini(ll a, ll b)
{
    if (a < b) return a;
    else return b;
}

bool porownanie1(przedzial a, przedzial b)
{
    if (a.p.x < b.p.x) return true;
    else
    {
        if (a.p.x == b.p.x)
        {
            if (a.p.y < b.p.y) return true;
            else return false;
        }
        else return false;
    }
}

bool porownanie2(przedzial a, przedzial b)
{
    if (a.p.y < b.p.y) return true;
    else
    {
        if (a.p.y == b.p.y)
        {
            if (a.p.x < b.p.x) return true;
            else return false;
        }
        else return false;
    }
}

przedzial Przeciecie(przedzial a, przedzial b)
{
    if (a.p.y == a.k.y && a.p.x > a.k.x) swap(a.p.x, a.k.x);
    if (a.p.x == a.k.x && a.p.y > a.k.y) swap(a.p.y, a.k.y);
    if (b.p.y == b.k.y && b.p.x > b.k.x) swap(b.p.x, b.k.x);
    if (b.p.x == b.k.x && b.p.y > b.k.y) swap(b.p.y, b.k.y);
    if (a.p.y == a.k.y && b.p.x == b.k.x && b.p.x >= a.p.x && b.p.x <= a.k.x && b.p.y <= a.p.y && b.k.y >= a.p.y) return {{b.p.x, a.p.y}, {b.p.x, a.p.y}};
    if (a.p.x == a.k.x && b.p.y == b.k.y && b.p.y >= a.p.y && b.p.y <= a.k.y && a.p.x >= b.p.x && a.p.x <= b.k.x) return {{a.p.x, b.p.y}, {a.p.x, b.p.y}};
    if (a.p.y == a.k.y && b.p.y == b.k.y && a.p.y == b.p.y)
    {
        ll t1 = maxi(a.p.x, b.p.x), t2 = mini(a.k.x, b.k.x);
        if (t1 <= t2) return {{t1, a.p.y}, {t2, a.p.y}};
    }
    if (a.p.x == a.k.x && b.p.x == b.k.x && a.p.x == b.p.x)
    {
        ll t1 = maxi(a.p.y, b.p.y), t2 = mini(a.k.y, b.k.y);
        if (t1 <= t2) return {{a.p.x, t1}, {a.p.x, t2}};
    }
    return INF;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<przedzial> L(n);
    for (int i = 0; i < n; ++i)
    {
        char kier;
        ll d;
        scanf(" %c %lld", &kier, &d);
        if (kier == 'U')
        {
            if (i == 0) L[i] = {{0, 0}, {0, d}};
            else L[i] = {{L[i - 1].k.x, L[i - 1].k.y + 1}, {L[i - 1].k.x, L[i - 1].k.y + d}};
        }
        else if (kier == 'D')
        {
            if (i == 0) L[i] = {{0, 0}, {0, -d}};
            else L[i] = {{L[i - 1].k.x, L[i - 1].k.y - 1}, {L[i - 1].k.x, L[i - 1].k.y - d}};
        }
        else if (kier == 'L')
        {
            if (i == 0) L[i] = {{0, 0}, {-d, 0}};
            else L[i] = {{L[i - 1].k.x - 1, L[i - 1].k.y}, {L[i - 1].k.x - d, L[i - 1].k.y}};
        }
        else if (kier == 'R')
        {
            if (i == 0) L[i] = {{0, 0}, {d, 0}};
            else L[i] = {{L[i - 1].k.x + 1, L[i - 1].k.y}, {L[i - 1].k.x + d, L[i - 1].k.y}};
        }
        vector<przedzial> P;
        for (int j = 0; j < i; ++j)
        {
            przedzial t = Przeciecie(L[i], L[j]);
            if (t.p.x != 1000000001)
            {
                if (t.p.x == t.k.x)
                {
                    if (t.p.y > t.k.y) swap(t.p.y, t.k.y);
                }
                else
                {
                    if (t.p.x > t.k.x) swap(t.p.x, t.k.x);
                }
                P.push_back(t);
            }
        }
        ll wyn = d;
        if (P.size() == 0)
        {
            printf("%lld\n", d);
            continue;
        }
        ll p, k;
        if (kier == 'L' || kier == 'R')
        {
            sort(P.begin(), P.end(), porownanie1);
            for (int j = 0; j < P.size(); ++j)
            {
                p = P[j].p.x, k = P[j].k.x;
                while (j < P.size() && P[j].p.x <= k)
                {
                    k = maxi(k, P[j].k.x);
                    ++j;
                }
                --j;
                wyn -= (k - p + 1);
            }
        }
        else
        {
            sort(P.begin(), P.end(), porownanie2);
            for (int j = 0; j < P.size(); ++j)
            {
                p = P[j].p.y, k = P[j].k.y;
                while (j < P.size() && P[j].p.y <= k)
                {
                    k = maxi(k, P[j].k.y);
                    ++j;
                }
                --j;
                wyn -= (k - p + 1);
            }
        }
        printf("%lld\n", wyn);
    }
    return 0;
}
