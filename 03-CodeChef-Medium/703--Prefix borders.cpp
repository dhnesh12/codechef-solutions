#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

#define ff first
#define ss second
#define pb push_back
#define mp make_pair

#define forr(i,a,b) for (i = a; i < b; i++)
vector<ll> lps;

void lpsarray(string p)
{
    ll n = p.length();
    lps.resize(n,0);
    ll i,j;
    
    lps[0]=0;
    for(i=1;i<n;i++)
    {
        j=lps[i-1];
        while(j>0 && p[i]!=p[j])
        j=lps[j-1];
        
        if(p[i]==p[j])
        j++;
        
        lps[i]=j;
        
        
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t,i,j,n,q;
    cin>>t;
    while(t--)
    {
        cin>>n>>q;
        string s;
        cin>>s;
        lpsarray(s);
        ll p,k;
        while(q--)
        {
            cin>>p>>k;
            vector<ll> v;
            v.pb(p);
            j=lps[p-1];
            
            while(j>0)
            {
                v.pb(j);
                j=lps[j-1];
            }
            
            reverse(v.begin(),v.end());
            
            if(k>v.size())
            cout<<-1<<"\n";
            else
            {
                cout<<v[k-1]<<"\n";
            }
            
        }
    }
	// your code goes here
	return 0;
}
