#pragma GCC optimization "Ofast"
#pragma GCC optimization "unroll-loop"
#pragma GCC target ("avx2")

#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define fs first
#define sc second
using namespace std;
const ll N = 100 + 9;
const ll inf = 450*100 + 9;
typedef pair<ll,ll> LL;

ll T,n,x;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    #define task "test"
    if (fopen(task".inp","r")){
        freopen(task".inp","r",stdin);
        freopen(task".out","w",stdout);
    }
    cin>>T;
    while(T--){
        cin>>n; ll sum = 0;
        ll choice = n/2 + n%2;
        bitset<inf> b[choice + 3]; b[0].set(0);
        for (ll i = 1;i <= n;i++){
            cin>>x; sum += x; //cout<<choice; return 0;
            for (ll j = choice;j > 0;j--) b[j] |= (b[j - 1] << x);
            //return 0;
        }
        //return 0;
        ll mx = sum/2;
        while(!b[choice][mx] && !b[n - choice][mx]) mx--;
        cout<<mx<<" "<<sum - mx<<"\n\n";
    }
}
