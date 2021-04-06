
#include <bits/stdc++.h>
#define mod 1000000007 
using namespace std;
    typedef long long int ll;


   void solve(){
       int v,e;
       cin>>v>>e;
       
       
      vector<int> edges[v];

       for(int i=0 ; i<e ; i++){
           int st,ed;
           cin>>st>>ed;
           st--,ed--;
           edges[st].push_back(ed);
           edges[ed].push_back(st);
           
       }
       
       for(int i=0;i<v;i++){
           sort(edges[i].begin(),edges[i].end());
       }
       
       
       
        
       map<vector<int>,int> m;
      
       for(int i=0;i<v;i++){
         m[edges[i]]++;
       }
       
   
       
       vector<int> s(v);
       for(int i=0;i<v;i++)
       s[i]=0;
       map<vector<int>,int> :: iterator it=m.begin();
       int count=0;
       bool flag=true;
       while(it!=m.end()){
           if(it->first.size()+it->second==v){
               count++;
               if(flag){
               for(int i=0;i<v;i++)
                   s[i]=1;
               for(int i=0;i<(it->first).size();i++){
                   s[(it->first).at(i)]=0;
               }
               flag=false;

           }
           }
           
           
           it++;
       }
       
       cout<<count<<endl;
       for(int i=0;i<v;i++)
       cout<<s[i];
       cout<<endl;
       
  
       
       
       
       
   } 


int main(){
     
  int t;
    cin>>t;
    while(t--){
        solve();
    }
      
    
}

