// Smit Vavliya

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = (1LL<<60) - 1;
const int mod = 998244353;

const int N = 1e6 + 5;
int arr[N], pref[N];
int n;

vector<int> t[4 * N];
struct SegmentTree {
    void build(int node, int start, int end) {
        if (start == end) {
            t[node].push_back(pref[start]);
            return;
        }
        int mid = (start+end) / 2;
        build(2*node,start,mid);
        build(2*node+1,mid+1,end);
        int i=0,j=0;
        while (i<t[node*2].size()&&j<t[node*2+1].size()) {
            if (t[node*2][i]<=t[node*2+1][j])
                t[node].push_back(t[node * 2][i]), i++;
            else 
                t[node].push_back(t[node * 2 + 1][j]), j++;
        }
        while (i<t[node*2].size())
            t[node].push_back(t[node * 2][i]), i++;
        while (j<t[node*2+1].size())
            t[node].push_back(t[node * 2 + 1][j]), j++;
    }

    int query(int node, int start, int end, int l, int r, int k) {
        if (r<start||end<l) return 0;
        if (l<=start&&end<=r) {
            int res = upper_bound(t[node].begin(), t[node].end(), k) - t[node].begin();
            return res;
        }
        int mid = (start+end) / 2;
        int left = query(2*node,start,mid,l,r,k);
        int right = query(2*node+1,mid+1,end,l,r,k);
        return left+right;
    }
} SegmentTree;

// (A[i] + . . . + A[j]) / (j - i + 1) >= K
// (A[i] + . . . + A[j]) >= K * (j - i + 1) = K + . . . + K (j - i + 1 times)
// (A[i] - K) + . . . + (A[j] - K) >= 0
// (B[i] + . . . + B[j]) >= 0

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int k;
    cin>>n>>k;
    pref[0]=0;
    for(int i=1; i<=n;i++) {
        cin>>arr[i];
        arr[i]-=k;
        pref[i]=pref[i - 1] + arr[i];
    }
    SegmentTree.build(1,1,n);
    int ans=0;
    for(int i = 1; i <= n; i++) {
        if(pref[i] >= 0) ans++;
        int res = SegmentTree.query(1,1,n,1,i-1,pref[i]);
        ans+=res;
    }
    cout<<ans<<"\n";
}
