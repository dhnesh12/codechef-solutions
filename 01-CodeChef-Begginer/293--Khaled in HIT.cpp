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
         int n, bit = 0;
         cin>>n;
         int arr[n];
         vector<int> l(n);
         vector<int>::iterator it;
         for(int i = 0; i < n ; i++){
             cin>>arr[i];
         }
         sort(arr,arr+n);
         if(bit == 0)
             it = set_intersection(arr, arr + n/4 , arr + n/4, arr + n/2 , l.begin());
         if(it - l.begin() != 0) bit = 1;
         if(bit == 0)
             it = set_intersection(arr + n/4, arr +n/2, arr+ n/2 , arr + n/4 + n/2 , l.begin());
         if(it - l.begin() != 0) bit = 1;
         if(bit == 0)
             it = set_intersection(arr + n/2 , arr + n/4 + n/2, arr + n/4 + n/2, arr + n, l.begin());
         if(it - l.begin() != 0) bit = 1;
         if(bit == 1){
             cout<<-1<<endl;
         }
         else{
             cout<<arr[n/4]<<" "<<arr[n/2]<<" "<<arr[n/2 + n/4]<<endl;
         }
     }
	return 0;
}
