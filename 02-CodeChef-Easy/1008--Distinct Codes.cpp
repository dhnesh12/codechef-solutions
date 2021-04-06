/******************************************
* AUTHOR : Avirup Aditya *
* NICK : WarChild *
******************************************/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 100005
#define mod 1000000007
#define dd double
#define rep(i, n) for(int i = 0; i < n; i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define rep1(i,b) for(int i=1;i<=b;i++)
#define pb push_back
#define mp make_pair
#define vi vector<int>
#define mi unordered_map<int, int>
#define clr(x) x.clear()
#define sz(x) ((int)(x).size())
#define ff first
#define ss second
#define endl "\n"


int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ios_base& scientific (ios_base& str);


  #ifndef ONLINE_JUDGE
      freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);
  #endif

    int t;
    cin>>t;
    
    while(t--){
        string s; cin >> s;
        set<string> temp;

        REP(i,1,sz(s)){
            char t[2];
            t[0] = s[i-1]; t[1] = s[i];
            temp.insert(t);
        }

        cout << sz(temp) << endl;
    }
    return 0;
}
