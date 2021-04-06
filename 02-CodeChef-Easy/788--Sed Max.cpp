/**
 * Author : RDP
 * There are no two words in the English language more harmful than "good job".
 * 1729 ;)
**/
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void debug_out() { cerr << '\n'; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T)
{
    cerr << " " << to_string(H);
    debug_out(T...);
}

#define endl '\n'
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#define FAST_IO              \
    ios::sync_with_stdio(0); \
    std::cin.tie(0);         \
    std::cout.tie(0);
#define all(x) (x).begin(), (x).end()
#define PI 3.1415926535897932384626433832795
const ll MOD = 1000000007;

void test_case()
{
    int n;
    cin >> n;
    vector<ll> a(n);
    set<ll> se;
    vector<ll> stack;
    for (auto &x : a)
        cin >> x;

    for (ll x : a)
    {
        while (!stack.empty() && stack.back() <= x)
        {
            se.insert(abs(x - stack.back()));
            stack.pop_back();
        }
        stack.push_back(x);
    }
    stack.clear();
    reverse(all(a));
    for (ll x : a)
    {
        while (!stack.empty() && stack.back() <= x)
        {
            se.insert(abs(x - stack.back()));
            stack.pop_back();
        }
        stack.push_back(x);
    }
    cout << se.size() << endl;
    return;
}
int main()
{
    FAST_IO
    int t = 1;
    cin >> t;
    while (t--)
        test_case();
    return 0;
}
