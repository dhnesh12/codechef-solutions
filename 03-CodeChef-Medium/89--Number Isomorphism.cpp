#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
 
int digs[10] = {1,0,2,3,4,5,6,7,8,9};
int n_digs[12]; // digits of n
ll p10[12]; // p10[i] = 10^i
ll facdiv[11][11]; // facdiv[i][j] = j!/i!
int t_to_n[10]; // where each dig of t maps to n
int bitcount[1<<10];
 
// 'lowest' stores all possible values of F(i).
// F(k,mx) contains all values which assumes that mx digits have already been used.
// Thus, all possible values of F(i) when i has k digits is in F(k,0).
 
// 'lowest_rev' contains the digital reverses of the numbers in 'lowest', and
// 'lowest_mask' contains a 10-bit mask representing the digits present in 'lowest'.
vector<ll> lowest[12][10];
vector<ll> lowest_rev[12][10];
vector<int> lowest_mask[12][10];
 
// temporary array for faster access
ll *facdivtemp;
 
int nc;
 
ll count_occ(ll t_digs, int taken, int rem, int i) {
    // number of integers in [1,n] which is isomorphic to t
    // t_digs contains the digits of t
    if (i >= nc) {
        return 1;
    }
 
    int n_dig = n_digs[i];
    int t_dig = t_digs % 10;
    t_digs /= 10;
    if (~t_to_n[t_dig]) {
        // this digit is already processed
        if (t_to_n[t_dig] == n_dig) {
            return count_occ(t_digs, taken, rem, i+1);
        } else if (t_to_n[t_dig] < n_dig) {
            return facdivtemp[rem];
        } else {
            return 0;
        }
    }
 
    // new digit
    ll total = 0;
    int mask = 1<<n_dig;
    rem--;
    if (i++) {
        total += facdivtemp[rem] * bitcount[(mask-1) & ~taken];
        if (!(taken & mask)) {
            t_to_n[t_dig] = n_dig;
            total += count_occ(t_digs, taken | mask, rem, i);
            t_to_n[t_dig] = -1;
        }
    } else if (n_dig) {
        total += facdivtemp[rem] * bitcount[(mask-2) & ~taken];
        if (!(taken & mask)) {
            t_to_n[t_dig] = n_dig;
            total += count_occ(t_digs, taken | mask, rem, i);
            t_to_n[t_dig] = -1;
        }
    }
 
    return total;
}
 
 
int main() {
    // initialize
    for (int i = 0; i < 12; i++) p10[i] = 1;
    for (int i = 0; i < 10; i++) t_to_n[i] = -1;
    for (int i = 0; i < 12; i++) n_digs[i] = 0;
    for (int i = 1; i < 12; i++) p10[i] = p10[i-1]*10;
 
    // compute bitcount
    for (int i = 0; i < 1<<10; i++) {
        bitcount[i] = bitcount[i>>1] + (i&1);
    }
 
    // compute facdiv
    for (int i = 0; i < 11; i++) {
        facdiv[i][i] = 1;
        for (int j = i+1; j < 11; j++) {
            facdiv[i][j] = facdiv[i][j-1] * j;
        }
    }
 
    // compute base case of lowest: k = 0 (empty string of digits)
    for (int m = 0; m < 10; m++) {
        lowest[0][m].push_back(0);
        lowest_rev[0][m].push_back(0);
        lowest_mask[0][m].push_back(0);
    }
 
    // compute other cases of lowest
    for (int k = 1; k < 12; k++) {
        int l = min(12-k,10); // we don't need cases where mx + k >= 12 due to the bounds
                              // also, obviously the number of digits to use is at most 10.
        int k1 = k-1;
        ll pw = p10[k1];
        for (int mx = 0; mx < l; mx++) {
            // try already used digits
            for (int i = 0; i < mx; i++) {
                ll add = digs[i]*pw;
                for (int vi = 0; vi < lowest[k1][mx].size(); vi++) {
                    lowest[k][mx].push_back(add + lowest[k1][mx][vi]);
                    lowest_rev[k][mx].push_back(digs[i] + 10*lowest_rev[k1][mx][vi]);
                    lowest_mask[k][mx].push_back((1<<i) | lowest_mask[k1][mx][vi]);
                }
            }
            // try a new digit (the next largest one)
            ll add = digs[mx]*pw;
            int mx2 = min(9,mx+1);
            for (int vi = 0; vi < lowest[k1][mx2].size(); vi++) {
                lowest[k][mx].push_back(add + lowest[k1][mx2][vi]);
                lowest_rev[k][mx].push_back(digs[mx] + 10*lowest_rev[k1][mx2][vi]);
                lowest_mask[k][mx].push_back((1<<mx) | lowest_mask[k1][mx2][vi]);
            }
        }
    }
 
    int z;
    scanf("%d", &z);
 
    while (z--) {
        ll n, m;
        scanf("%lld%lld", &n, &m);
 
        // compute digits of n
        nc = 0;
        for (ll digs = n; digs; digs /= 10) {
            n_digs[nc++] = digs % 10;
        }
        for (int i = 0, j = nc-1; i < j; i++, j--) {
            n_digs[i] ^= n_digs[j], n_digs[j] ^= n_digs[i], n_digs[i] ^= n_digs[j];
        }
 
        ll ans = 0;
 
     
        if (p10[nc-1] == n) {
            ans += n % m;
            n--;
            nc--;
            for (int i = 0; i < nc; i++) n_digs[i] = 9;
        }
 
        for (int l = 1; l < nc; l++) {
            for (int ti = 0; ti < lowest[l][0].size(); ti++) {
                ll t = lowest[l][0][ti];
                ll count = facdiv[10-bitcount[lowest_mask[l][0][ti]]][9]*9;
                ans += t % m * count;
            }
        }

        for (int ti = 0; ti < lowest[nc][0].size(); ti++) {
            ll t = lowest[nc][0][ti];
            facdivtemp = facdiv[10-bitcount[lowest_mask[nc][0][ti]]];
            ll count = count_occ(lowest_rev[nc][0][ti],0,10,0);
            ans += t % m * count;
        }
 
     
        printf("%lld\n", ans);
    }
}
  
