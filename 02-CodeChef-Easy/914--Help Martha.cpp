#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
      string s;
      cin>>s;
      int n=s.length();
      int arrd[4]={0,0,0,0};
      for(int i=0; i<n; i++){
        if(s[i]=='R'){
          arrd[0]++;
        }
        else if(s[i]=='L'){
          arrd[1]++;
        }
        else if(s[i]=='U'){
          arrd[2]++;
        }
        else{
          arrd[3]++;
        }
      }
      int x1,y1;
      cin>>x1>>y1;
      int q;
      cin>>q;
      while(q--){
        bool pos=false;
        int x2,y2;
        cin>>x2>>y2;
        int xdiff= x2-x1;
        int ydiff= y2-y1;
        if(xdiff>=0){
          if(arrd[0]>=xdiff){
            if(ydiff>=0){
              if(arrd[2]>=ydiff){
                pos = true;
              }
            }
            if(ydiff<0){
              if(arrd[3]>=(-1*ydiff)){
                pos=true;
              }
            }
          }
        }
        if(xdiff<0){
          if(arrd[1]>=-1*xdiff){
            if(ydiff>=0){
              if(arrd[2]>=ydiff){
                pos = true;
              }
            }
            if(ydiff<0){
              if(arrd[3]>=(-1*ydiff)){
                pos=true;
              }
            }
          }
        }
        if(pos){
          cout<<"YES "<<abs(xdiff) + abs(ydiff)<<"\n";
        }
        else{
          cout<<"NO"<<"\n";
        }
      }
    }
    return 0;
}
