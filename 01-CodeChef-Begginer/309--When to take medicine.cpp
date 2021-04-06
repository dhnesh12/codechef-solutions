#include<iostream>
using namespace std;
bool check(int a){
  if(a%400==0){
     return true;
   }
   if(a%100==0){
      return false;
   }
   if(a%4==0){
      return true;
   }
   else{
      return false;
   }
 }
int main(){
    int m[] = {0,31,0,31,30,31,30,31,31,30,31,30,31};
    int t;
    cin>>t;
    while(t--){
     string s;
     cin>>s;
     int ans=0;
     int x = stoi(s.substr(5,2));
     int y = stoi(s.substr(8,2));
      if(m[x]%2){
        ans = ((31-y)/2)+1;
      }
      else if(m[x]){
        ans = (30-y)/2 +(31+(y%2))/2 +1;
      }
      else{ 
       if(check(stoi(s.substr(0,4)))){
        ans = (29-y)/2 +1;
       }
       else{
         ans = (28-y)/2 +(31+(y%2))/2 +1;
       }
     }
    cout<<ans<<endl;
    }
	return 0;
}
