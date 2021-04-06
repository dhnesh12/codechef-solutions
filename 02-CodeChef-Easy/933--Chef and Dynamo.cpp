#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--)
    {
        ll n,a,s,b,c,d,e,check;
        cin>>n>>a;
        ll val=(long long)pow(10,n);
        s=2*val+a;
        cout<<s<<endl;
        cin>>b;
        c=val-b;
        cout<<c<<endl;
        cin>>d;
        e=val-d;
        cout<<e<<endl;
        cin>>check;
        if(check==-1)
        exit(0);
        fflush(stdin);
        
    }
    return 0;
}
