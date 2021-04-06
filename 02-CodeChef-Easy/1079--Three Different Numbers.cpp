#include<bits/stdc++.h>
using namespace std;
#define loop(i,n,t) for(int i=n;i<t;i++)
#define fo(i,t) for(i=0;i<t;i++)
#define input(x) for(auto &w:x) cin>>w; 
#define output for(auto w:arr) cout<<w<<" "; 
#define beg(x) x.begin(),x.end()
#define cout(x) cout<<x<<endl;
#define deb(x) cout<<#x<<" "<<x<<endl;
#define mod 1000000007
#define ff first
#define ss second
#define pb push_back
#define mk make_pair
#define ff first
typedef vector<int> veci;
typedef vector<float> vecf;
typedef vector<string> vecs;
typedef vector<pair<int,int>> vecp;
typedef long long int ll;
typedef pair<int,int>pair;
#define start int t; cin>>t;
#define MAX 1e9+7
const ll Modd = 1e9+7;
void fast()
{
    ios_base::sync_with_stdio(true);
    cin.tie(0),cout.tie(0);
}
int main()
{   fast();
    start;
    while(t--)    
    {
    ll arr[3];
    cin>>arr[0]>>arr[1]>>arr[2];
    sort(arr,arr+3);
    ll n1 = arr[0] % Modd;
    ll n2 = (arr[1] - 1) % Modd;
    ll n3 = (arr[2] - 2) % Modd;
    ll Ans = (((n1 * n2) % Modd) * n3) % Modd;
    cout << Ans << "\n";
    }
}