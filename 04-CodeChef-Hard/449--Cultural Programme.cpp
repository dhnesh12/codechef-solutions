#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define print(x) cout << x << endl
#define pb push_back
#define vi vector<int>
#define mod 1000000007
#define MIN_INT -2147483648
#define index(c) (((int) c) - 97)
//#define int long long

#define range(i, a, b) for(int i = a; i < b; i++)
typedef long long ll;

void print_array(int A[], int N) {
    range(i, 0, N) cout << A[i] << ' ';
    cout << endl;
}

static int A[10000001];

void solve(){

    range(i, 0, 10000001) A[i] = 0;
    int N;
    cin >> N;
    int a, b;
    range(i, 0, N){
        cin >> a >> b ;
        A[a] = 1;
        A[b] = -1;
    }
    int mx = 0;
    int rightNow = 0;
    range(i, 1, 10000001){
        rightNow += A[i];
        mx = max(mx, rightNow);
    }
    cout << mx << endl;

}


int32_t main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);



    int T = 1;
//    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}