#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2004;
int dp1[maxn][maxn];
int dp2[maxn][maxn];
int tc;
int n,p;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>tc;
    while(tc--) {
        cin>>n>>p;
        for(int i=0 ; i<=2*n ; i++) {
            for(int j=0 ; j<=n ; j++) {
                dp1[i][j]=dp2[i][j]=0;
            }
        }
        dp2[1][0]=1;
        for(int i=2 ; i<=2*n ; i++) {
            dp2[i][0]=1;
            for(int j=1 ; j<=i/2 ; j++) {
                if(i!=2*n&&i==2*j) continue;
                int k=i-2*j+1;
                dp2[i][j]=(dp2[i-1][j-1]*k+dp2[i-1][j])%p;
				dp1[i][j]=(dp1[i-1][j-1]*k+dp2[i-1][j-1]*k*(k-1)/2)%p;
				dp1[i][j]+=dp1[i-1][j];
				dp1[i][j]%=p;
            }
        }
        cout<<dp1[2*n][n]<<'\n';
    }
}
