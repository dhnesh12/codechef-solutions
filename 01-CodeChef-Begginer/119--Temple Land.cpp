#include <iostream>
using namespace std;

typedef long long int ll;

int main() {
	int T, length;
	cin>>T;
	while(T--){
	    cin>>length;
	    int odd = 1; //flag variable
	    if((length%2) == 0){
	        odd = 0;
	    }
	    int arr[length];
	    for(int i=0; i<length; i++){
	        cin>>arr[i];
	    }
	    int mid = length/2;
	    int maxi = -1; //guard variable
	    for(int i=0; i<length; i++){
	        maxi = max(maxi, arr[i]);
	    }
	    int highest = 0; //flag variable
	    if(maxi == arr[mid]){
	        highest = 1;
	    }
	    int starts1 = 0; //flag variable
	    if(arr[0] == 1 && arr[length-1] == 1){
	        starts1 = 1;
	    }
	    int incr_diff = 0; //flag variable
	    int count1 = 0;
	    for(int i=0; i<mid; i++){
	        if((arr[i+1]-arr[i]) == 1){
	            count1++;
	        }
	    }
	    if(count1 == mid){
	        incr_diff = 1;
	    }
	    int decr_diff = 0; //flag variable
	    int count2 = 0;
	    for(int i=mid; i<length-1; i++){
	        if((arr[i]-arr[i+1]) == 1){
	            count2++;
	        }
	    }
	    if(count2 == (length-1-mid)){
	        decr_diff = 1;
	    }
	    if(highest == 1 && starts1 == 1 && incr_diff == 1 && decr_diff == 1 && odd == 1){
	        cout<<"yes"<<"\n";
	    }
	    else{
	        cout<<"no"<<"\n";
	    }
	}
	return 0;
}
