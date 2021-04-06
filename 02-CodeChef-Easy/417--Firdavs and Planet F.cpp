#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define m7 1000000007
#define pb push_back
#define ff first
#define ss second
#define rep(n) for(int i=0; i<n; i++)

void fastIO(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

bool pof2(int n){	//Check whether a number is a power of 2.
    if(n < 1)
        return false;
    double logn = log2(n);
    return floor(logn) == ceil(logn);
}

int main() {

    fastIO();

    int t;
    cin >> t;

    while(t--){

        int n,q;
        cin >> n >> q;

        int a[n], b[n];
        rep(n){
            cin >> a[i];
            b[i] = a[i];
        }
        sort(b, b+n);

        rep(q){
            int x,y;
            cin >> x >> y;
            x--,y--;
            int cost = abs(a[x] - a[y]) + y - x; 
            int len  = upper_bound(b,b+n,max(a[x],a[y])) - b;
            len -= lower_bound(b,b+n,min(a[x],a[y])) - b;

            cout << cost << " " << len << '\n';
        }
    }
}