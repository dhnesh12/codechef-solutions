/*
    Time complexity: O(N)
    Space complexity: O(N)
    Where N is the size of input string
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;

char checkmate(string &s)
{
    string ans = "AB";
    int n = s.length();
    vector<int> c(2);
    vector<char> dir(n, '#');
    int cur = 0;

    for (int i = 0; i < n; i++)
    {
        if (s[i] != '.')
        {
            dir[i] = (cur == 0 ? 'R' : 'L');
            cur ^= 1;
        }
    }

    int pre = -1, ok = 0, grundy = 0;

    for (int i = 0; i < n; i++)
    {
        if (s[i] != '.')
        {
            if (pre == -1)
            {
                pre = i;
                continue;
            }

            if (dir[i] == 'L' && dir[pre] == 'R')
            {
                int dots = i - pre - 1;
                if (s[i] == s[pre])
                {
                    c[s[i] - 'A'] += dots;
                }
                else
                {
                    if (dots > 0)
                        ok = 1;
                    grundy ^= dots;
                }
            }

            pre = i;
        }
    }

    if (dir[pre] == 'R')
    {
        c[s[pre] - 'A'] += (n - pre - 1);
    }

    if (c[0] == c[1])
    {
        return ans[grundy == 0];
    }
    else
    {
        return ans[c[0] < c[1]];
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--){
        string s;
        cin>>s;
        cout << checkmate(s) << endl;
    }

    return 0;
}
