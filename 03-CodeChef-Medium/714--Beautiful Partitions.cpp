// Author: HarshKumar
#include <bits/stdc++.h>
using namespace std;
#define ll int64_t
const ll N = 1e6 + 6, M = 1e9 + 7;
vector<ll> LIS(const vector<ll> &elements)
{
    // declare the set with a custom comparison function
    // that compares values instead of indices
    auto compare = [&](ll x, ll y) { return elements[x] < elements[y]; };
    set<ll, decltype(compare)> S(compare);

    // process the elements; for each length
    // maintain the index of the best end so far
    vector<ll> previous(elements.size(), -1);
    for (ll i = 0; i < elements.size(); ++i)
    {
        auto it = S.insert(i).first;
        if (it != S.begin())
            previous[i] = *prev(it);
        if (*it == i && next(it) != S.end())
            S.erase(next(it));
    }

    // reconstruct the indices that form
    // one possible optimal answer
    vector<ll> answer;
    answer.push_back(*S.rbegin());
    while (previous[answer.back()] != -1)
        answer.push_back(previous[answer.back()]);
    reverse(answer.begin(), answer.end());
    return answer;
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);
    ll T;
    cin >> T;
    while (T--)
    {
        ll n, k;
        cin >> n >> k;
        vector<ll> a(n + 1);
        for (ll i = 1; i <= n; i++)
            cin >> a[i], a[i] += a[i - 1];
        for (ll i = 1; i < n; i++)
            if (a[i] < 0)
                a[i] = 0;
            else if (a[i] > a[n])
                a[i] = a[n];
        if (a[n] < k)
        {
            cout << "NO\n";
            continue;
        }
        auto lis = LIS(a);
        lis[0] = 0;
        if (lis.size() > k)
        {
            cout << "YES\n";
            for (ll i = 1; i < k; i++)
                cout << lis[i] - lis[i - 1] << ' ';
            cout << n - lis[k - 1] << '\n';
        }
        else
            cout << "NO\n";
    }
}