#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MOD 1000000007
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL);
#define all(v) (v).begin() , (v).end()
#define sumof(v) accumulate(all(v), 0LL, plus<ll>())
#define maxof(v) max_element(all(v))
#define minof(v) min_element(all(v))
#define inf INT_MAX
#define VI vector<ll>
#define VII vector<pair<ll, ll>>

int main(){
    FASTIO
    int testCases = 1;
    cin>>testCases;
    while(testCases--){
        ll n; cin>>n;
        VI H(n), D(n);
        for(int i=0; i<n; ++i){
            cin>>H[i];
        }
        for(int i=0; i<n; ++i){
            cin>>D[i];
        }
        if(n==2){
            if(H[0]-D[0] != D[1]-H[1]) cout<<"-1"<<endl;
            else {
                ll r = H[0] - D[0];
                ll t = max(-r, 0ll);
                cout<<2*t+r<<endl;
            }
            continue;
        }
        ll h = sumof(H), d = sumof(D);
        if((d-h)%(n-2)!=0 || (d-h)/(n-2) < 0 ){
            cout<<"-1"<<endl;
        }
        else{
            ll s = (d-h)/(n-2);
            bool valid = true;
            ll s1 = 0;
            for(int i=0; i<n; ++i){
                ll temp = (s+H[i]-D[i])/2;
                if((s+H[i]-D[i])%2!=0 || temp<0){
                    valid = false;
                    break;
                }
                s1 = s1 + temp;
            }
            if(!valid) cout<<"-1"<<endl;
            else{
                cout<<s1<<endl;
            }
        }
    }
}