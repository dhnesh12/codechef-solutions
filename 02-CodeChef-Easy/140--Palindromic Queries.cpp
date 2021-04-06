#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<ll,ll> PII;
const int mx=100010, Pr = 19937;

ull Suja_Hash[mx],ulta_Hash[mx],Pow[mx];

ull SameOrderHash(int i,int j)
{
    if(i>j)
        return 0;
    return Suja_Hash[j]-Suja_Hash[i-1]*Pow[j-i+1];
}
ull ReverseOrderHash(int i,int j)
{
    if(i>j)
        return 0;
    return ulta_Hash[i]-ulta_Hash[j+1]*Pow[j-i+1];
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,q;
    string s;
    cin>>s;
    n = s.size();
    s = " "+ s;

    Suja_Hash[0] = ulta_Hash[0] = Pow[0] = 1;
    for(int i = 1 ; i <= n; i++)
    {
        Suja_Hash[i] = Suja_Hash[i-1]* Pr + s[i];
        Pow[i] = Pow[i-1] * Pr;
    }
    for(int i=n; i>=1; i--)
        ulta_Hash[i] = ulta_Hash[i+1] * Pr + s[i];

    cin>>q;
    while(q--)
    {
        int i,j,l,r;

        cin >> i >> j >> l >> r ;
        if(i > r || l > j)
        {
            if(SameOrderHash(l,r) == ReverseOrderHash(l,r))
                cout << "Yes" << "\n";
            else
                cout << "No" << "\n";
        }
        else
        {
            ull Left  = ReverseOrderHash(i,j);
            ull Right =    SameOrderHash(i,j);
            if(i<l)
            {
                Left  = ReverseOrderHash(i,i+j-l);
                Right =    SameOrderHash(i,i+j-l);
            }
            if(j>r)
            {
                Left  = ReverseOrderHash(j-r+i,j);
                Right =    SameOrderHash(j-r+i,j);
            }

            i= max(i,l);
            j= min(j,r);
            ull LL = ( SameOrderHash( l,i-1 ) * Pow[j-i+1] + Left ) * Pow[ r - j ] + SameOrderHash( j+1 , r );

            ull RR = ( ReverseOrderHash ( j + 1,r ) * Pow[ j - i + 1 ] + Right ) * Pow [ i - l ] + ReverseOrderHash ( l, i-1 );

            if( LL == RR )
                cout<<"Yes"<<"\n";
            else cout<<"No"<<"\n";
        }
    }
}

