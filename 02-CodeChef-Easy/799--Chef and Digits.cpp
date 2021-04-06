#include <bits/stdc++.h>
using namespace std;
int main() {
	int n,m;std::cin >> n>>m;
	string s;cin>>s;
	int arr[n+1];
	for(int i=1;i<=s.length();i++){
        char jk=s[i-1];
        //std::cout << int(jk) - '0' << std::endl;
        arr[i]=int(jk) - '0';
	}
	
	int count[n+1][10]={0};
	count[1][arr[1]]++;
	for(int j=2;j<=n;j++){
	    for(int x=0;x<10;x++){
	        count[j][x]=count[j-1][x];
	    }
	    count[j][arr[j]]++;
	}
	while(m--){
	    int x;std::cin >> x;
	    int current=arr[x];
	    int b1=0;
	    int b2=0;
	    for(int i=0;i<10;i++){
	        int noofapp=count[x][i];
	        int dif=current-i;
	        dif*=noofapp;
	        if(i==current){
	            continue;
	        }
	        else if(i>current){
	            b1 = b1+dif;
	        }
	        else{
	            b2 = b2+dif;
	        }
	    }
	    std::cout << b2-b1 << std::endl;
	}
	return 0;
}
