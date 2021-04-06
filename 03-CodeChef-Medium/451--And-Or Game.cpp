//Yash Patel
//SEAS,auto
//DSA

#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include<vector>

#define Yash ios_base::sync_with_stdio(false);cin.tie(NULL);
#define Patel cin.tie(NULL); cout.tie(NULL);
#define cases  long long int t=1;cin>>t; while(t--) { solve();} return 0
#define vec vector<int>
#define all(v) v.begin(),v.end()
#define pi 3.14159265358993

using namespace std;

int main(){
    Yash Patel

    long long int T;
    scanf("%lld",&T);
    
    while(T--){
        //
        long long int a,b;
        scanf("%lld %lld",&a,&b);
        
        vector<long long int>x(a);
        vector<long long int>y(b);
        
        for(long long int j=0; j<a; j++)
            scanf("%lld",&x[j]);
            
        for(long long int j=0; j<b; j++)
            scanf("%lld",&y[j]);
            //s-unos
        unordered_set<long long int> unos;
        unos.insert(0);
        
        stack<long long int> full;
        
        full.push(0);
        //temp-ans
        while(!full.empty()){
            
            long long int ans=full.top();
            
            full.pop();
            
            for(long long int j=0; j<a; j++){
                
                int foo=1;
                long long int res=(ans|x[j]);
                
                if(unos.find(res) != unos.end())
                // j=0; j<a; j++
                    foo=0;
                    
                if(foo==1){
                    unos.insert(res);
                    // (unos.find(res) != unos.end())
                    // foo=0;
                    full.push(res);
                }
            }
            for(long long int j=0; j<b; j++){
                
                int foo=1;
                //res-pls
                long long int pls=ans&y[j];
                
                if(unos.find(pls) != unos.end())
                   // foo=1
                    foo=0;
                    //full.pop();
                    
                if(foo==1){
                    //
                    unos.insert(pls);
                    full.push(pls);
                }
            }
        }
        printf("%lld\n",unos.size());
    }
    //
    return 0;
}