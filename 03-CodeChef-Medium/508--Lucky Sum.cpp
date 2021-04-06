#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T ;
int n;
string s[55];

bool is_valid(string &s)
{
    for(auto x:s)
        if(x>'7')
            return false;
    return true;
}
string build_string_from_msk(int exact, int wt, int len)
{
    string res;
    for(int i=0;i<len ; i++)
    {
        char added = '4';
        if(wt & (1<<i))
            added = '7';
        if(!(exact & (1<<i)))
            added--;
        res.push_back(added);
    }
    return res;
}
pair<int,int>build_msk_from_string(string &a)
{
    int exact = 0, wt = 0;
    for(int i=0;i<(int)a.size();i++)
    {
        if(a[i] >'4')
            wt|=(1<<i);
        if(a[i] == '4' || a[i]=='7')
            exact |= (1<<i);
    }
    return {exact, wt};
}
string add_strings(string &a, string &b)
{
    string res;
    int n = max(a.size(), b.size());
    for(int i=0;i<n;i++)
    {
        if((int)a.size() <= i)
            res.push_back(b[i]);
        else if((int)b.size() <= i)
            res.push_back(a[i]);
        else
            res.push_back(max(a[i],b[i]));
    }
    return res;
}

ll dp[(1<<9)+2][(1<<9)+2][55][10];
int calced[(1<<9)+2][(1<<9)+2][55][10];

ll calc(int exact, int wt, int pos, int len)
{
    if(pos == n)
    {
        return exact == ((1<<len)-1) && len;
    }
    ll &res = dp[exact][wt][pos][len];
    if(calced[exact][wt][pos][len] == T)
        return res;
    calced[exact][wt][pos][len] = T;
    res = calc(exact, wt, pos+1, len);

    string a = build_string_from_msk(exact,wt, len);
    string sum = add_strings(a, s[pos]);
    pair<int,int> msks = build_msk_from_string(sum);
    res += calc(msks.first, msks.second, pos+1, sum.size());
    return res;
}

char temp[15];
int main()
{
    int t;
    scanf("%d", &t);
    for(T = 1;T<=t;T++)
    {
        scanf("%d", &n);
        for(int i=0;i<n;i++)
        {
            scanf("%s",temp);
            string a = temp;
            if(!is_valid(a))
            {
                i--, n--;
                continue;
            }
            reverse(a.begin(), a.end());
            s[i] = a;
        }
        ll res = calc(0,0,0,0);
        printf("%lld\n", res);
    }
}
