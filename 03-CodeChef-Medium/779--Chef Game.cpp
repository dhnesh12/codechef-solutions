#include<bits/stdc++.h>
using namespace std;
#define D(x) cout<<#x<<" = "<<x<<endl
#define ll long long


ll t, k, n, odd, even, swE, swO, x;


bool parity[100];

ll gameVal() {

    ll gval = 1LL<<50, ret = 0;
    ret = parity[0]? gval : -gval;
    bool change = false;
    for(int i = 1; i<n; i++) {
        if(parity[i] != parity[i-1]) change = true;
        if(change) gval = gval>>1;
        ret += parity[i]? gval : -gval;
    }
    return ret;
}


int main() {
    cin>>t;
    while(t--) {
        cin>>k;
        ll gval = 0;
        while(k--) {
            cin>>n;
            vector<int>vi(n);
            for(int &x: vi) cin>>x;
            sort(vi.begin(),vi.end());
            for(int i = 0; i<n; i++) parity[i] = vi[i] & 1;
            gval+=gameVal();
        }
        if(!gval) puts("DON'T PLAY");
        else if(gval>0) puts("ODD");
        else puts("EVEN");
    }
    return 0;
}
