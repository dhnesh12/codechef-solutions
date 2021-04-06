#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define sd(val) scanf("%d", &val)
#define ss(val) scanf("%s", &val)
#define sl(val) scanf("%lld", &val)
#define debug(val) printf("check%d\n", val)
#define PB push_back
#define MP make_pair
#define FF first
#define SS second
#define ll long long
#define ld double
#define MOD 1000000007

#define all(x) x.begin(), x.end()    // Forward traversal
#define rall(x) x.rbegin(), x.rend() // Reverse traversal
#define tr(c, i) for (__typeof__((c)).begin() i = (c).begin(); i != (c).end(); i++)
#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())
#define sz(a) int((a).size())

#define clr(val) memset(val, 0, sizeof(val))
#define what_is(x) cerr << #x << " is " << x << endl;
#define print_array(a, n)             \
    cerr << "Array '" << #a << "': "; \
    for (int i = 0; i < n; i++)       \
        cerr << a[i] << " ";          \
    cerr << endl;

#define IOTXT                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#define FIO                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<ll> vll;
typedef vector<vll> vvll;

int main()
{

    FIO;

    int t;
    cin >> t;

    while (t--)
    {
        ll n, x;
        cin >> n >> x;

        ll a[n];
        vector<vector<int>> column_bit_loc(31);
        vector<int> ptr(31, 0);

        for (ll i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        for (ll i = 0; i < n; i++)
        {
            ll temp = a[i], j = 0;

            while (temp > 0)
            {
                int pos = (int)log2(temp);

                column_bit_loc[31 - pos - 1].push_back(i);
                temp ^= 1 << pos;
            }
        }

        for (ll i = 0; i < n - 1; i++)
        {
            for (ll j = 0; j < 31; j++)
            {
                if (x == 0)
                {
                    j = 1000;
                    i = 1000;
                    break;
                }

                if (a[i] == 0)
                {
                    break;
                }

                if ((1 << (31 - j - 1)) & a[i])
                {

                    a[i] ^= 1 << (31 - j - 1);
                    ptr[j] += 1;

                    if (column_bit_loc[j].size() - ptr[j] >= 1)
                    {
                        ll k = column_bit_loc[j][ptr[j]];

                        a[k] ^= 1 << (31 - j - 1);
                        ptr[j] += 1;
                    }
                    else
                    {
                        ll k = n - 1;

                        a[k] ^= 1 << (31 - j - 1);
                        column_bit_loc[j].push_back(k);
                        ptr[j] += 1;
                    }

                    x--;
                }
            }
        }

        // what_is(x);

        if (n == 2 && x % 2 == 1)
        {
            a[n - 1] ^= 1;
            a[n - 2] ^= 1;
        }

        for (ll i = 0; i < n; i++)
        {
            cout << a[i] << " ";
        }
    }

    return 0;
}