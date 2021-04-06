#include<bits/stdc++.h>
using namespace std;
 
#define ll long long int
#define FIO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define mod 1000000007
#define N 1000000
 
int main(){
    FIO;
            
    int i,j;
    int numOfDivisors[N+1]={0};
    int ans[N+1]={0};
    
    for(i=1;i<=N;i++)
        for(j=i;j<=N;j+=i){
            numOfDivisors[j]++;
            ans[j]++;
        }
    
    for(i=1;i<=N;i++)
        for(j=i;j<=N;j+=i)
            if(numOfDivisors[j/i]==4)
                ans[j] = min(ans[j], ans[i]);
 
    cin >> i;
    while(i--){
        cin >> j;
        cout << ans[j] << "\n";
    }
    
    return 0;
}
