#include <iostream>
#include <stack>
#include <algorithm>
#include <string.h>
#include <queue>
#include <cmath>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
#define FI first.first
#define SE first.second
#define TH second

const int maxN = 524288, MOD = 1e9 + 7;

int ls[maxN], cs, pr, m, arr[maxN], li[maxN];
ll n, h, a, b, sai;

void pre(int ind){
    memset(ls, -1, sizeof(ls));
    
    int i;
    for(i = 0; ls[ind] == -1; i++){
        ls[ind] = i, arr[i] = ind;
        ind = (a * ind + b) % m;
    }
    pr = ls[ind], cs = i - ls[ind];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    int t, ind;
    cin >> t;
    while(t--){
        cin >> h >> n >> m >> a >> b >> ind;
        n--;
        for(int i = 0; i < m; i++)
            cin >> li[i];
        pre(ind);
        ll tot = 0; sai = 0;
        for(int i = pr; i < pr + cs; i++)
            sai += li[arr[i]];
        
        for(int i = 0; i < min(ll(pr), n); i++)
            tot += li[arr[i]];
        if(n > pr){
            n -= pr;
            tot += (n / cs) * sai;
            
            for(int i = pr; i < pr + n % cs; i++)
                tot += li[arr[i]];
        }
        
        tot *= h;
        cout << tot / 2 << '.' << (tot & 1) * 5 << '\n';
    }
}
