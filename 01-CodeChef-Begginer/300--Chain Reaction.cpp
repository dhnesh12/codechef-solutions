#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
using namespace std;

int main() {
     int cases;
     cin>>cases;
     while(cases--){
         int r, c, x = 0, y = 0, bit = 0;
         cin>>r>>c;
         int arr[r][c];
         for(int i = 0; i < r; i++){
             for(int j = 0; j < c; j++){
                 cin>>arr[i][j];
             }
         }
         for(int i = 0; i < r && bit == 0; i++){
             for(int j = 0; j < c && bit == 0; j++){
                 x = (i > 0) + (i < (r-1)) + (j > 0) + (j < (c -1));
                //  cout<<x<<"  ";
                //   arr1[i][j] = x;
                  if(arr[i][j] >= x)
                    bit = 1;
             }
            //  cout<<endl;
         }
         
         if(bit == 0){
             cout<<"Stable"<<endl;
         }
         else cout<<"Unstable"<<endl;
     }
	return 0;
}
