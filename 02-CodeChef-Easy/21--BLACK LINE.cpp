#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll cek(ll x, ll y){cout << "1 " << x << " " << y << endl << flush;ll a;cin >> a;return a;}
int main(){
    ll n;cin >> n;ll l = 1,r = n,mid,l1 = 1,l2 = 1,r1 = 1,r2 = 1;
    while (l <= r){mid = (l+r)/2;if (cek(1,mid) >= 1){l1 = mid;r = mid-1;}else{l = mid+1;}}l = l1,r = n;
    while (l <= r){mid = (l+r)/2;if (cek(l1,mid) == 2){l2 = mid; r = mid-1;}else{l = mid+1;}}l = 1,r = n;
    while (l <= r){mid = (l+r)/2;if (cek(mid,n) >= 1){r2 = mid;l = mid+1;}else{r = mid-1;}}l = 1,r = r2;
    while (l <= r){mid = (l+r)/2;if (cek(mid,r2) == 2){r1 = mid;l = mid+1;}else{r = mid-1;}}
    cout << 2 << " " << l1 << " " << r1 << " " << l2 << " " << r2 << endl << flush;}