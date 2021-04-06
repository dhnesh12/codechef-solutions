#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int solve(int a, int b, int c){
    if((a+b)==c || (b+c)==a || (a+c)==b)
        return 1;
    return 0;
}

int main() {
    int cases;
    cin>>cases;
    while(cases--){
       vector<int> res(26,0);
       vector<int> v;
       string s;
       cin>>s;
       int ans = 1;
       for(int i = 0 ; i < s.size(); i++){
           res[s[i]-97]++;
       }
        for(int i = 0 ; i < 26; i++){
            if(res[i] != 0)
              v.push_back(res[i]);
       }
    //   sort(v.begin(),v.end());
      if(v.size() >= 3){
           for( int i = 0; i < v.size()-2 && ans == 1; i++){
                  ans = solve(v[i] , v[i+1] , v[i+2]);    
             }
         }
      else {
          ans = 1;
      }
      if(ans == 1){
          cout<<"Dynamic"<<endl;
      }
      else cout<<"Not"<<endl;
    }
	return 0;
}
