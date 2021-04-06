#include<bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){
    FASTIO
    int t;
    cin>>t;
    while(t--){
         int n,k,cnt=0;
    cin>>n>>k;
    string str,s="";
    cin>>str;
    for(auto i: str){
        if(i==':'){
            s+=i;
        }
        s+=i;
    }
    int i,j=0;
    queue<int> qm,qi;
    for(auto i:s){
        if(i=='I'){
            while(!qm.empty() && qm.front()+k<j)
                qm.pop();
            if(!qm.empty()){
                cnt++;
                qm.pop();
            }
            else
                qi.push(j);
        }
        else if(i=='M'){
            while(!qi.empty() && qi.front()+k<j)
                qi.pop();
            if(!qi.empty()){
                cnt++;
                qi.pop();
            }
            else
                qm.push(j);
        }
        else if(i=='X'){
            while(!qm.empty())
                qm.pop();
            while(!qi.empty())
                qi.pop();
        }
        j++;
    }
    cout<<cnt<<endl;
    }
    return 0;
}
