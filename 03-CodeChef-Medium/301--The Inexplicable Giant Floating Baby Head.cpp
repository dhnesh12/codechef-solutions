#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// :'(
ll bit(ll val,int pos) {
    return (val>>pos)&1;
}


void solve() {
    ll k;
    ll L,R;
    cin >> L >> R >> k;
    ll ans=0;
    ll sumL=0;
    ll sumR=0;
    L=max(L-1,0LL);
    bool flagL=true,flagR=true;
    for(int i=59;i>=0;i--) {
        ll tempL = sumL/2, tempR = sumR/2;
        ll mask = (ans|(1LL<<i));
        ll clrmask = ((1LL<<i)-1);

        if(flagL && bit(L,i)) tempL+=(L&clrmask)+1;
        if(flagR && bit(R,i)) tempR+=(R&clrmask)+1;
        
        if(tempR-tempL>=k) {
            ans=mask;
            flagL&=bit(L,i);
            flagR&=bit(R,i);
            sumL/=2;
            sumR/=2;
        } else {
            sumL|=(flagL&bit(L,i))<<i;
            sumR|=(flagR&bit(R,i))<<i;
            
        }
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while(T--) solve();
}