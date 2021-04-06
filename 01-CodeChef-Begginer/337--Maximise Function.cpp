#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include<iomanip>
#include<cmath>
#include <numeric>
#include <unordered_set>
#include <climits>

#include <unordered_map>
using namespace std;

#define int long long
#define double long double
#define puts(x) cout<<x<<endl
#define inf LLONG_MAX
#define minf -LLONG_MAX
#define all(v) (v).begin(),(v).end()
#define odd(x) x%2==1
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define Yes cout<<"Yes\n"
#define No cout<<"No\n"
#define present(c,x) (c.find(x) != c.end())
#define ANS cout<<ans<<endl;
#define sz(x) x.size()
#define desc greater<int>()
#define nl cout<<endl
#define modP(x) (x+P)%P
#define rep(i,x,y)  for(int i=x;i<y;i++)
#define vll vector<long long>
#define ll long long int


void prv(vector<int> &a, int n)
{
    int i = 0;
    for(int x : a)
    {
        i++;
        cout << x << " ";
        if(i == n) break;
    }
    cout << '\n';
}


bool match(string &s1, string &s2, int l1,int r1,int l2,int r2,vector<vector<vector<int>>>&dp){

    if(r2==l2){
        if(s2[l2]==s1[l1])return 1;
        return 0;
    }
    for(int k=l2;k<r2;k++){
        bool b1, b2, b3 , b4;
        if(dp[l1][l2][k-l2+1]!=-1)b1=dp[l1][l2][k-l2+1];
        else{
            b1=match(s1,s2,l1,l1+(k-l2),l2,k,dp);
            dp[l1][l2][k-l2+1]=b1;
        }
        if(dp[l1+k-l2+1][k+1][r2-k]!=-1)b2=dp[l1+k-l2+1][k+1][r2-k];
        else{
            b2=match(s1,s2,l1+k-l2+1,r1,k+1,r2,dp);
            dp[l1+k-l2+1][k+1][r2-k]=b2;
        }


        if(dp[l1][k+1][r2-k]!=-1)b3=dp[l1][k+1][r2-k];
        else{
            b3= match(s1,s2,l1,l1+(r2-k-1),k+1,r2,dp);
            dp[l1][k+1][r2-k]=b3;
        }
        if(dp[l1+r2-k][l2][k-l2+1]!=-1)b4=dp[l1+r2-k][l2][k-l2+1];
        else{
            b4=match(s1,s2,l1+r2-k,r1,l2,k,dp);
            dp[l1+r2-k][l2][k-l2+1]=b4;
        }
        if((b1&&b2)||(b3&&b4))return 1;

    }
    return 0;
}
int P = 1e9+7;

int mod(int n) {return (n % P + P) % P; }
int modM(int n, int m) { return ((n % P * m % P) + P) % P; }
int modA(int n, int m) { return ((n % P + m % P) + P) % P; }
int modS(int n, int m) { return ((n % P - m % P) + P) % P; }

int dfs(vector<vector<int>>&dp,vector<int>&v,int l,int r){
    if(l>r)return 0;
    if(l==r){
        return v[l];
    }
	for(int i=0;i<10;i++){}
    if((r-l)==1)return max(v[l],v[r]);
    int x = dp[l+2][r];
    if(x==0){
        x= dfs(dp,v,l+2,r);
        dp[l+2][r]=x;
    }
    int y= dp[l+1][r-1];
    if(y==0){
        y= dfs(dp,v,l+1,r-1);
        dp[l+1][r-1]=y;

    }
    int z=dp[l][r-2];
    if(z==0){
        z= dfs(dp,v,l,r-2);
        dp[l][r-2]=z;

    }
    return max(v[l]+min(x,y),v[r]+min(y,z));
}


int dfs(vector<vector<int>> &v, vector<vector<int>>& dp,int node , int pnode, int col){


    int ans = 1;
    if(col == 1){
		for(int i=0;i<10;i++){}
        for(auto i:v[node]){
            if(i!=pnode){
               if(dp[0][i]==-1)dp[0][i]= dfs(v,dp,i,node,0);
               ans =modM(ans,dp[0][i]);
            }

        }
    }
    else{
        for(auto i:v[node]){
            if(i!=pnode){
                if(dp[1][i]==-1)dp[1][i]=dfs(v,dp,i,node,1);
                if(dp[0][i]==-1)dp[0][i]=dfs(v,dp,i,node,0);
                //cout << k<< endl;
                ans = modM(ans,modA(dp[0][i],dp[1][i]));
            }
        }
    }

    return ans ;
}
int get(int a, int b , int c){
    return abs(a-b)+abs(b-c)+abs(c-a);
}
signed main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> v(n);
		for(int i=0;i<10;i++){}
        for (int i = 0; i < n; i++) cin >> v[i];
        sort(all(v));
        int f = v[0];
        int l = v[n - 1];
        int ans = -1;
        for (int i = 1; i < n - 1; i++) {
            ans = max(ans, get(f, l, v[i]));
        }
		for(int i=0;i<10;i++){}
        cout << ans << endl;

    }
}
