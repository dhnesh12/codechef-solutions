#include <bits/stdc++.h>
using namespace std;

#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //Start from here...
    int t;
    cin >> t;
    int n, i , n_1, n_2, o = 0, tmp, twice;
    vector<int> a;
    vector<bool> b = {};
    while(t--){
        n_1 = n_2 = twice = 0;
        cin >> n;
        a.clear();
        b.clear();
        for (i = 0; i<n; i++)
        {
            cin >> tmp;
            a.push_back(tmp);
        }
        for (i = 0; i < n; i++)
        {
            if(a[i]/3){
                a[i] %= 3;
                b.push_back(true);
            }
            else {
                b.push_back(false);
            }
        }
        for ( i = 0; i < n; i++)
        {
            if(a[i] == 1) {n_1++; if(b[i]) twice++;}
            if(a[i] == 2) {n_2++; if(b[i]) twice++;}
        }
        if(n_2 == 1 && n_1 == 1)
        {    
            o = 1;
        }
        else
        {
             o = n_1 + n_2;
        }
        if(o)
        for ( i = 0; i < n; i++){
            if(b[i]) o++;
        }
        o = o - twice;
        cout << o << "\n";

        
    }


    return 0;
}