#include<bits/stdc++.h>
using namespace std;
int main(){
  int t;
  cin>>t;

  while(t--){
int n;
cin>>n;
vector<int>v;
int n1=n;
while(n1>=1){
   v.push_back(n1);
   n1=n1/2;
}
int j=0;
reverse(v.begin(),v.end());
cout<<v.size()<<endl;
for(int i=0;i<v.size();i++){
   cout<<v[i]<<" ";
}
cout<<endl;
int k=1;
for(int i=1;i<=n;i++){
   
 vector<int>ans1;
 vector<int>ans2;
 ans1.push_back(i);
 ans2.push_back(j+1);
 if(j<(v.size()-1)){
    if(k<=v[j+1]/2 and k<=i){
       ans1.push_back(k);
       ans2.push_back(j+2);
       k++;
    }
    if(k<=v[j+1]/2 and k<=i){
       ans1.push_back(k);
       ans2.push_back(j+2);
       k++;
    }
    if(k<=v[j+1]/2 and k<=i){
       ans1.push_back(k);
       ans2.push_back(j+2);
       k++;
    }
 }
cout<<ans1.size()<<endl;
for(int l=0;l<ans1.size();l++){
   cout<<ans1[l]<<" "<<ans2[l]<<endl;
}
if(i==v[j]){
   j++;
   k=1;
}
}
  }
}