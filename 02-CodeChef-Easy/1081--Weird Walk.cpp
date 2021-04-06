#include <bits/stdc++.h>
#define fo(i, n) for (int i = 0; i < n; i++)
#define pb(num) push_back(num)
#define ppb pop_back()
using namespace std;
typedef vector<int> vi;
#define it vector<int>::iterator itr
#define pi(arr)                                            \
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) \
    cout << arr[i] << ' '
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<ii> vii;
typedef vector<char> vc;
typedef unsigned long long ull;
typedef set<string, int> ssi;
typedef set<int> si;
typedef set<string> ss;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    int t;
    cin >> t;
    fo(i, t)
    {
        ll n;
        cin >> n;
        ll arr1[n + 1];
        ll arr2[n + 1];
        fo(i, n)
        {
            cin >> arr1[i];
        }
        fo(i, n)
        {
            cin >> arr2[i];
        }
        
        ll x1 = 0;
        ll x2 = 0;
        ll res = 0;
        fo(i, n)
        {
            if (x1 == x2 && arr1[i] == arr2[i])
            {
                res = res + arr1[i];
                
            }
                x1 += arr1[i];
                x2 += arr2[i];
        }
        cout << res << endl;
    }

    return 0;
}