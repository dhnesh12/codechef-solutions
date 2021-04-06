#include<bits/stdc++.h> 
using namespace std;
#define ll long long int
#define pb push_back
#define pii pair<int,int>
#define mk make_pair
#define ff first
#define ss second
#define mod 1000000007
#define endl '\n'
void solve(){
    int n,m;
    cin>>n>>m;
    int a[n];
    int ans = INT_MAX;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int rep =0;rep<2;rep++){
        int last_non = -1;
        bool increasing = true;
        int turns = 0;
        int pre = a[0];
        if(pre==-1){
            pre = 1;
        }
        else{
            last_non = 0;
        }
        for(int i =1;i<n;i++){
            if(a[i]!=-1){
                int j = last_non;
                if(j!=-1){
                    if((i-j)%2!=abs(a[i]-a[j])%2 || abs(a[i]-a[j])>abs(i-j)){
                        cout<<-1<<endl;
                        return ;
                    }
                }
                last_non = i;
            }
            if(increasing&&pre==m){
                turns++;
                increasing = !increasing;
            }
            if(!increasing&&pre==1){
                turns++;
                increasing = !increasing;
            }
            if(increasing)pre++;
            else pre--;
            if(a[i]!=-1){
                if(increasing&&pre<=a[i]){

                }
                else if(!increasing&&pre>=a[i]){

                }
                else{
                    turns++;
                    increasing =!increasing;
                }
                pre = a[i];
            }
        }
        ans = min(ans,turns);
        for(int&x : a){
            if(x>=1&&x<=m){
                x=m+1-x;
            }
        }
    }
    cout<<ans<<endl;
    return;
}
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}