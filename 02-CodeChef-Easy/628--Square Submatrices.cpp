#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t,n,x,inp,sum; cin >> t;
    vector<int>arr;
    vector<int>sums;
    unordered_map<int,int>freq;
    vector<int>lengths;
    while(t--) {
        arr.clear();
        lengths.clear();
        arr.push_back(0);
        cin >> n >> x;
        sum = 0;
        for(int i=0;i<n;i++) {
            cin >> inp;
            sum+=inp;
            arr.push_back(sum);
            if (x%(i+1)==0 and i+1<=ceil(sqrt(x))) lengths.push_back(i+1); 
        }
        int ans = 0;
        for(int len: lengths) {
            sums.clear();
            freq.clear();
            for(int i=0;i+len<=n;i++) {
                if (arr[i+len]-arr[i]<=x/len) {
                    sums.push_back(arr[i+len]-arr[i]); 
                    freq[arr[i+len]-arr[i]]++; }
            }
            for(int i:sums) 
                ans+=freq[(x/len)-i];
        }
        cout << ans << "\n";
    }
    return 0;
}
