
//#include<iostream>
#include<bits/stdc++.h>
//#include<vector>
using namespace std;
#define ll   long long int
#define svl vector<long long int>
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define all(x) x.begin(),x.end()
#define svi vector<int>
#define svb vector<bool>
#define svvl vector<vector<ll> >
#define svvi vector<vector<int> >
#define spl pair<ll,ll>
#define pb push_back
#define PI 3.14159265

#define smp make_pair
#define sfri(s,n) for(ll i=s;i<n;i++)
#define sfrj(s,n) for(ll j=s;j<n;j++)
#define st(i) ll i=1;cin>>i;while(i--)
#define vsi vector<set<ll> >
#define pii pair<ll,ll>
#define vpii vector<pair<int,int> >
#define mod 1e9+7

/*#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>,rb_tree_tag,tree_order_statistics_node_update> pbds;
*/
int main()
{ios_base::sync_with_stdio(false);cin.tie(0);cin.tie(0);
int t;
cin>>t;
while(t--)
{int n;
cin>>n;
int x;
long long sum=0;
int a=0;
sfri(0,n)
{cin>>x;
sum+=x;
if(x==0)
a++;
}
if((sum-n+a)<100 and sum>=100)
cout<<"YES\n";
else
cout<<"NO\n";


}
return 0;}
