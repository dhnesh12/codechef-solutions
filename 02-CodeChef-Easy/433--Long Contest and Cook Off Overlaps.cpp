#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int is_leap(int n){
	    if(n%400==0) return 1;
	    if(n%4==0 && n%100!=0) return 1;
	    return 0;
	}

void display(int arr[],int n){
	    for(int i=1;i<n;i++) cout<<arr[i]<<" ";
	    cout<<endl;
	}

int main() {
	// your code goes here
	
	int leap_year[401];
	for(int i=1;i<401;i++){
	    leap_year[i] = is_leap(i);
	}
	int feb_date[401];
	feb_date[1] = 2;
	for(int i=2;i<401;i++){
	    if(leap_year[i-1]) feb_date[i] = feb_date[i-1]-2;
	    else feb_date[i] = feb_date[i-1]-1;
	    if(feb_date[i]<=0) feb_date[i] = (feb_date[i]+7)%8;
	}
	int overlap_array[401]{};
	for(int i=1;i<401;i++){
	    if(feb_date[i]==7) overlap_array[i]=1+overlap_array[i-1];
	    else if(feb_date[i]==6 && !leap_year[i]) overlap_array[i]=1+overlap_array[i-1];
	    else overlap_array[i] = overlap_array[i-1];
	}
	int val = overlap_array[400] - overlap_array[0];
// 	display(overlap_array,401);
    int t;
    cin>>t;
    while(t--){
        long long m1,m2,y1,y2;
        cin>>m1>>y1>>m2>>y2;
        if(m1>2) y1++;
        if(m2<2) y2--;
        long long val1 = overlap_array[y2%400]+(y2/400)*val;
        long long val2 = overlap_array[(y1-1)%400]+((y1-1)/400)*val;
        long long result = val1-val2;
        cout<<result<<endl;
    }
	return 0;
}
