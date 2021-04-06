#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int cases;
    cin>>cases;
    while(cases--){
        int n, temp = 0, temp1 = 0, j;
        cin>>n;
        vector<int> arr(32) ;
        arr.assign(32,0);
        for(int i = 0; i < n; i++){
           cin>>temp>>temp1;
           for(j = temp ; j <= 31; j++ ){
               arr[j] += temp1;
           }
        }
        cin>>n;
        for(int i = 0; i < n; i++){
            cin>>temp>>temp1;
            if(arr[temp] >= temp1){
                cout<<"Go Camp"<<endl;
            }
            else 
              cout<<"Go Sleep"<<endl;
        }
    }
	return 0;
}
