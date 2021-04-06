#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define m7 1000000007
#define pb push_back
#define rep(n) for(int i=0; i<n; i++)

void fastIO(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

bool pof2(int n){	// Check whether a number is a power of 2.
    if(n < 1)
        return false;
    double logn = log2(n);
    return floor(logn) == ceil(logn);
}

int powers2(ll n){
    int count = 0;
    while(n % 2 == 0){
        count++;
        n/=2;
    }
    return count;
}

int main() {

    fastIO();

    int t;
    cin >> t;

    while(t--){

        ll n;
        cin >> n;

        if(powers2(n) % 2){
            cout << "Lose" << endl;
            string lose;
            cin >> lose;
            if(lose == "WA")
                exit(-1);
        }
        else{
            cout << "Win" << endl;
            string win;
            
            while(n > 0){
                if(n == 1){
                    cout << "-1" << endl;
                    n -= 1;
                }
                else if(n % 2){
                    if(powers2(n-1) % 2){
                        cout << "-1" << endl;
                        n -= 1;
                    }
                    else{
                        cout << "+1" << endl;
                        n += 1;
                    }
                }
                else{
                    cout << "/2" << endl;
                    n /= 2;
                }
                cin >> win;
                if(win == "WA")
                    exit(-1);
                if(win == "+1")
                    n += 1;
                else if(win == "-1")
                    n -= 1;
                else if(win == "/2")
                    n /= 2;
                if(n == 0 && win != "GG")
                    exit(-1);
            }
        }
    }
}