#include <bits/stdc++.h>
using namespace std;

long long int dp[51][1280];


int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int row=51;
    int col=1280;
    
    long long int M=1000000007;
    
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            dp[i][j]=0;
        }
    }

    for(int i=0;i<row;i++){dp[i][0]=1;}

    for(int i=1;i<row;i++){
        for(int j=1;j<col;j++){
            dp[i][j]=dp[i-1][j];
            if(j-i>=0){
                dp[i][j]+=dp[i-1][j-i];
            }
        }
    }

    for(int i=1;i<row;i++){
        for(int j=col-2;j>=0;j--){
            dp[i][j]+=dp[i][j+1];
        }
    }

    int t,n;
    cin>>t;

    while(t--){
        cin>>n;
        
        long long int temp=0;
        int i=n-1;
        int j=n+1;
        
        while(i>=0 && j>=0){
            temp+=dp[i][j];
            temp%=M;
            i--;
            j--;
        }
        
        cout<<temp<<"\n";
    }


    return 0;
}