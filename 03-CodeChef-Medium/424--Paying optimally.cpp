#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VII vector < VI >
#define PII pair<int, int>
#define VPII vector< PII >
#define pb push_back
#define mp make_pair
#define ff first
#define ss second

const LL S = 507, N = 63, INF = 2e18;
LL c, s, k;

LL dp[N][S], p[N];

void calc()
{
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i=1; i<N; i++) {
        for (int j=0; j<S; j++) {
            for (int k=0; k<c; k++) {
                if (j-k>=0) {
                    dp[i][j] += dp[i-1][j-k];
                    if (dp[i][j] > INF) dp[i][j] = INF;
                }
            }
        }
    }
}

LL find() {
    LL ans = 0;
    LL sum = s;
    for (int i = N-1; i>=0; i--) {
        ans*=c;
        int d;
        LL cum = 0, precum=0;;
        for (d = 0; d<c && d<=sum; d++)
        {
            LL next = cum + dp[i][sum-d];
            if (next>=k)  break;
            cum = next;
        }
        ans += d;
        sum-=d;
        k-=cum;
        //cout<<i<<" "<<d<<" "<<sum<<endl;
    }
    return ans;
}

int main()
{
    int t;
    cin>>t;

    while (t--) {
        cin>>c>>s>>k;
        calc();
        //for (int i=0; i<5; i++)
          //  for (int j=0; j<5; j++)
            //    cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
        cout<<find()<<endl;;
    }
}



