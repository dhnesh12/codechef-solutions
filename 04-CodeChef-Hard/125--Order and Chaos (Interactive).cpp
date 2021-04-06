#include<bits/stdc++.h>
#define ll long long
#define INF 9000000000000000000
using namespace std;
ll T,r,c,ar,ac;
ll parovi[6][6]={
   {-1, 1, 10, 10, 04, -1},
   {2, 5, 14, 15, 5, 3},
   {11, 13, 7, 7, 16, 12},
   {11, 13, 8, 8, 16, 12},
   {4, 6, 14, 15, 6, 1},
   {-1, 3, 9, 9, 2, -1}
};
char znak;
int main(){
   cin>>T;
   while(T--){
      cout<<"CHAOS"<<endl;
      for(int i=1;i<=18;i++){
         cin>>r>>c>>znak;
         if(r==1 and c==1){
            cout<<"6 6 "<<znak<<endl;
            continue;
         }
         if(r==1 and c==6){
            cout<<"6 1 "<<znak<<endl;
            continue;
         }
         if(r==6 and c==1){
            cout<<"1 6 "<<znak<<endl;
            continue;
         }
         if(r==6 and c==6){
            cout<<"1 1 "<<znak<<endl;
            continue;
         }
         if(znak=='X')
            znak='O';
         else
            znak='X';
         for(int j=1;j<=6;j++)
            for(int i=1;i<=6;i++)
               if(parovi[r-1][c-1]==parovi[i-1][j-1] and (i!=r or j!=c)){
                  ar=i;
                  ac=j;
               }
         cout<<ar<<" "<<ac<<" "<<znak<<endl;
      }
   }
   return 0;
}
