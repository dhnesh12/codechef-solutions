#include<bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;
int N,q;

int lp[1000006];

vector<int>prime;

void FindLowestPrimeFactor(){
    for(int i=2;i<=1000003;i++){
        if(lp[i]==0){
            lp[i]=i;
            prime.pb(i);
        }
        for(int j=0;j<prime.size();j++){
            if(lp[i]<prime[j])break;
            if(i*prime[j]>1000003)break;

            lp[i*prime[j]]=prime[j];
        }
    }
}

void input();

void solve(){
    FindLowestPrimeFactor();
    for(int i=0;i<q;i++){
        int u ,v;
        cin>>u>>v;
        if(u==v){
            cout<<0<<"\n";
        }
        else{
            if(__gcd(u,v)>1){
                int ans =1;
                if(lp[min(u,v)]!=min(u,v))ans++;
                cout<<ans<<"\n";
            }
            else{
                if((ll)lp[u]*lp[v]<=(ll)N){
                    int ans =2;
                    if(lp[u]!=u)ans++;
                    if(lp[v]!=v)ans++;
                    cout<<ans<<"\n";
                }
                else if(lp[u]*2<=N and lp[v]*2<=N){
                    int ans = 4;
                    if(lp[u]!=u)ans++;
                    if(lp[v]!=v)ans++;
                    cout<<ans<<"\n";
                }
                else{
                    cout<<-1<<"\n";
                }
            }
        }
    }
}

void Clear(){

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    input();
    solve();
    Clear();
}

void input(){
    cin>>N;
    cin>>q;
}
