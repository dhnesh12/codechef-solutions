#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
		
	int size;
	cin >> size;
	while(size--){
		int num,a=0;
		cin >> num;
		int arr[num];
		for(int i=0;i<num;i++){
			cin >> arr[i];
		}
		sort(arr,arr+num);
		for(int i=0;i<num;i++){
			if(arr[i]==arr[i+1]){
				a++;
			}
		}
		cout << a << endl;
	}
	return 0;
}