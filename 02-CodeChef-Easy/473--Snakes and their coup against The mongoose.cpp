#include<bits/stdc++.h>
using namespace std;
#define ll long long

string arr[2];
int cnt[2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        cin>>arr[0]>>arr[1];
        cnt[0] = 0;
        cnt[1] = 0;
        //int cnt[1] = 0;
        for(int i=0;i<2;i++) {
            for(int j=0;j<n;j++) {
                if(arr[i][j]=='*') cnt[i]++;
            }
        }
        int ans = 0;
        if(cnt[0] && cnt[1]) {
            ans=1;
            cnt[0] = 0;
            cnt[1] = 0;
            for(int i=0;i<n;i++) {
                if(arr[0][i]=='*') cnt[0]++;
                if(arr[1][i]=='*') cnt[1]++;
                if(cnt[0]>1 || cnt[1]>1) {
                    ans++;
                    cnt[0] = 0;
                    cnt[1] = 0;
                    i--;
                }
            }
        }
        else if((cnt[0] && cnt[1]==0) || (cnt[0]==0 && cnt[1])) {
            ans = max(cnt[0],cnt[1])-1;
        }
        cout<<ans<<endl;
    }
}