#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define MAX 10005
#define int long long
#define MOD 1000000007
#define inf 100000000000000000

int32_t main()
{
    IOS;
    int t;cin>>t;
    while(t--)
    {
        int n,m;cin>>n>>m;
        int cnt=0;
        int mn_row = INT_MAX,mn_col = INT_MAX, mx_row = INT_MIN, mx_col = INT_MIN;
        vector<vector<char> > a(n,vector<char> (m));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin>>a[i][j];
                if(a[i][j]=='*'){
                    cnt++;
                    mn_row = min(mn_row,i);
                    mx_row = max(mx_row,i);
                    mn_col = min(mn_col,j);
                    mx_col = max(mx_col,j);
                }
            }
        }
        if(cnt==0)
            cout<<"0"<<endl;
        else{
            int p = max(abs(mn_row-mx_row),abs(mn_col-mx_col));
            cout<<1+((p+1)/2)<<endl;
        }
    }
    return 0;
}


