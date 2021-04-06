#include<bits/stdc++.h>
#define ll long long int
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
    ll a;
    cin>>a;
    if(a%6==0 || a%6==1 || a%6==3) cout<<"yes"<<endl;
    else cout<<"no"<<endl;
    return 0;
}