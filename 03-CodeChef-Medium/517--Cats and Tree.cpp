#include<bits/stdc++.h>
using namespace std;

#define testcases int t; cin>>t; while(t--)
#define int long long
const int MOD =  1e9 + 7;
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl "\n"

const int N = 3e5 + 10;
vector<int> tree[N];
int up[N][25];
int depth[N];
int present[N];

int root;

void binary_lifting(int src, int par, int lvl)
{
    up[src][0] = par;
    depth[src] = lvl;

    for (int i = 1; i <= 22; i++)
    {
        int p = up[src][i - 1];
        if (p != -1)
        {
            up[src][i] = up[p][i - 1];
        }
        else break;
    }

    for (auto child : tree[src])
    {
        if (child == par) continue;

        binary_lifting(child, src, lvl + 1);
    }
}

int jumpTo(int x)
{
    for (int i = 22; i >= 0; i--)
    {
        int p = up[x][i];
        if (p == -1 || present[p])
        {

        }
        else {
            x = up[x][i];
        }
    }

    return x;

}

int32_t main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    FASTIO;

    memset(up, -1, sizeof up);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;

        if (x == 0)
        {
            root = i;
        }
        else {
            tree[x].push_back(i);
            tree[i].push_back(x);
        }
    }

    binary_lifting(root, -1, 0);


    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;

        if (present[x])
        {
            cout << 0 << endl;
        }
        else {

            if (present[x])
            {
                cout << 0 << endl;
                continue;
            }

            int node = jumpTo(x);
            // cout << node << endl;
            cout << depth[x] - depth[node] + 1 << endl;
            present[node] = 1;

        }

    }

}