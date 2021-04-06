#include <bits/stdc++.h>
using namespace std;

int main() {
	int num,*arr;
	cin >> num;
	arr = new int[num];
	for(int i=0;i<num;i++)
	    cin >> arr[i];
	int result[num][num];
	for(int i=0;i<num;i++)
	    for(int j=0;j<num;j++)
	        result[i][j] = 0;
	        
	int row=0,col=0;
	int res = 0,start=1;
	int temp,curr,i;
	
	while(1){
	    for(i=0;i<num;i++){
	        if(arr[i]!=0){
	            start = i+1;break;
	        }
	    }
	    if(i==num && arr[i-1] == 0)
	        break;
	    curr = start;
	    result[row][col++] = start;
	    while(arr[curr-1] != start){
	        temp = arr[curr-1];
	        result[row][col++] = temp;
	        arr[curr-1] = 0;
	        curr = temp;
	    }
	    if(arr[curr-1] == start){
    	    result[row][col++] = arr[curr-1];
    	    arr[curr-1] = 0;
    	    row++;col=0;
    	    res++;
	    }
	}
	cout << res << endl;
	for(int i=0;i<num;i++){
	    for(int j=0;j<num;j++){
	        if(result[i][j] != 0)
	            cout <<  result[i][j] << " ";
	    }
	    cout << endl;
	}
	
	
	
	return 0;
}
