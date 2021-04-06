//Pritish Wadhwa
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define MOD 1000000000
#define mp make_pair
#define pub push_back
#define endl "\n"
#define setbits __builtin_popcount
#define int long long
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef tree<pair<ll, int>, null_type, less<pair<ll, int>>, rb_tree_tag, tree_order_statistics_node_update> PBDS;

void offline()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

int32_t main()
{
    fastio();
    offline();
    int t;
    cin >> t;
    for (int tc = 0; tc < t; tc++)
    {
        int n, m;
        cin >> n >> m;
        if (min(n, m) == 1 && max(n, m) <= 2)
        {
            cout << 1 << endl;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    cout << 1 << " ";
                }
                cout << endl;
            }
            continue;
        }
        if (min(n, m) == 1 && max(n, m) >= 3)
        {
            cout << 2 << endl;
            vector<int> id{1, 2};
            int itr = 0;
            int c = 0;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (c == 2)
                    {
                        c = 0;
                        itr = (itr + 1) % 2;
                    }
                    cout << id[itr] << " ";
                    c++;
                }
                cout << endl;
            }

            continue;
        }
        if (min(n, m) == 2 && max(n, m) == 2)
        {
            cout << 2 << endl;
            for (int i = 0; i < n; i++)
            {
                cout << i + 1 << " " << i + 1;
                cout << endl;
            }
            continue;
        }
        if (min(n, m) == 2)
        {
            cout << 3 << endl;
            vector<int> id{1, 2, 3};
            if (n == 2)
            {
                for (int i = 0; i < n; i++)
                {
                    int itr = 0;
                    for (int j = 0; j < m; j++)
                    {
                        cout << id[itr] << " ";
                        itr = (itr + 1) % 3;
                    }
                    cout << endl;
                }
            }
            else
            {
                int itr = 0;
                for (int j = 0; j < n; j++)
                {
                    cout << id[itr] << " " << id[itr] << endl;
                    itr = (itr + 1) % 3;
                }
            }
        }
        else
        {
            cout << 4 << endl;
            vector<int> id{1, 2, 3, 4, 3, 4, 1, 2};
            int c = 0;
            vector<int> off{0, 4};
            int offitr = 0;
            for (int i = 0; i < n; i++)
            {
                int itr = 0;
                if (c == 2)
                {
                    c = 0;
                    offitr = (offitr + 1) % 2;
                }
                for (int j = 0; j < m; j++)
                {
                    cout << id[off[offitr] + itr] << " ";
                    itr = (itr + 1) % 4;
                }
                c++;
                cout << endl;
            }
        }
    }
    return 0;
}