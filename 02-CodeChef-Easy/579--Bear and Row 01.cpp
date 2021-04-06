#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<ll,ll>
#define mp make_pair
#define f first
#define s second
#define pb push_back


ll cnt[100005],prefix[100005];

int main(){
    int t;
    cin>>t;
    while(t--) {
        string s;
        cin>>s;
        int n = s.size();
        cnt[n] = s[n-1]=='0';
        for(int i=n-1;i>=1;i--) {
            cnt[i] = cnt[i+1];
            if(s[i-1]=='0' && s[i]=='1') {
                cnt[i]++;
            }
        }
        int sold = 0;
        for(int i=n;i>=1;i--) {
            prefix[i] = n-sold;
            if(s[i-1]=='1') sold++;
        }
        ll ans = 0;
        for(int i=1;i<=n;i++) {
            if(s[i-1]=='1') {
                ans += (prefix[i]-i);
            }
        }
        for(int i=1;i<=n;i++) {
            if(s[i-1]=='1') ans += cnt[i];
        }
        cout<<ans<<endl;
    }
}