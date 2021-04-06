#include<iostream>
#include<bits/stdc++.h>
#include<string>
using namespace std;
int main(){
   
    int t;
    cin>>t;
     
    while(t--){
       vector<int>v(26);
        int n;
        cin>>n;
        int c=n;
        int j=0;
        while(n--){
            string s;
            cin>>s;
            for(int i=0;i<s.length();i++){
                if(v[s[i]-'a']==j){
                v[s[i]-'a']++;
                }
            }
            j++;
            
    }
    int count=0;
    for(int i=0;i<26;i++){
        if(v[i]==c){
            count++;
        }
    }
    cout<<count<<endl;
    }
    return 0;
}
