#include <bits/stdc++.h>
using namespace std;
int main()
{
   int t;
   cin>>t;
   while(t--){
         long long int n;
         cin>>n;
         int arr[n];
         for(int i=0;i<n;i++){
             scanf("%d",&arr[i]);
         }
         int cont=0;
         int dist=0;
         int wait=0;
         for(int i=n-1;i>-1;i--){
            if(arr[i]==0&&dist>0){
                if(dist+wait>cont){cont=dist+wait;}
                wait++;
            }
            else if(arr[i]==1){
                wait--;
                dist++;
            }
            if(wait<0){wait=0;}

         }
         cout<< cont<<endl;
   }
}
