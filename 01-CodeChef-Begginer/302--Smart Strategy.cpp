#include <iostream>
using namespace std;

int main() {
     int cases;
     cin>>cases;
     while(cases--){
         int n, q;
         cin>>n>>q;
         long long int x;
         unsigned long long int y = 1;
         for(int i = 0; i < n; i++){
             cin>>x;
             if(y < 1e9)
               y *= x;
         }
         for(int i = 0; i < q; i++){
             cin>>x;
             if(y > 1e9 ){
                 cout<<0<<' ';
             }
             else 
               cout<<x/y<<' ';
         }
        cout<<endl;
     }
	return 0;
}
