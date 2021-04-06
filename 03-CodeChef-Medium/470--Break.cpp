#include<bits/stdc++.h>
using namespace std;

namespace
{
    vector<int> roww[3];      
    unordered_set<int> uns1;

    bool solve1(const int n)
    {
        uns1.clear();
        uns1.insert(roww[0][0]);

        for (auto i = 0; i < n; ++i)
        {
            const auto ins = uns1.insert(roww[0][i]);
            if (ins.second || roww[0][i] >= roww[1][i])
                return false;

            uns1.insert(roww[1][i]);
        }

        return true;
    }

    bool is_feasible(const vector<int>& a, const vector<int>& b)
    {
        auto &ab = roww[2];
        ab.resize(a.size() + b.size());
        merge(a.begin(), a.end(), b.begin(), b.end(), ab.begin());

        for (auto i = 0u; i < a.size(); ++i)
            if (ab[i] == ab[i + a.size()])
                return false;

        return true;
    }

    bool solve(const int n, const int s)
    {
        // 444 123
        // 234 111
        if (roww[0][0] == roww[0][n - 1] && roww[0][0] >= roww[1][n - 1] ||
            roww[1][0] == roww[1][n - 1] && roww[0][0] >= roww[1][n - 1])
            return false;// 1st step

        if (solve1(n))
            return true;
        if (s != 2)
            return false;

        if (n == 2)
            return roww[0][0] < roww[1][1] && roww[1][0] < roww[0][1];

        const auto r = is_feasible(roww[0], roww[1]);
        return r;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, s;
    cin >> t >> s;
    while (t--)
    {
        int n;
        cin >> n;

        for (auto j = 0; j < 2; ++j)
        {
            auto &a = roww[j];
            a.resize(n);
            for (auto i = 0; i < n; ++i) cin >> a[i];

            sort(a.begin(), a.end());
        }

        const auto sol = solve(n, s);
        cout << (sol ? "YES\n" : "NO\n");
    }

    return 0;
}