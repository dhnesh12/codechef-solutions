#include <bits/stdc++.h>
using namespace std;
int main() {
	int t;std::cin >> t;
	while(t--){
	    int n,m;std::cin >> n>>m;
	    char arr[n][m];
	    int count=0;
	    bool xaxis[n]={false};bool yaxis[m]={false};
	    for(int i=0;i<n;i++){
	        string s;std::cin >> s;
	        for(int j=0;j<s.length();j++){
	            arr[i][j]=s[j];
	            if(s[j]=='1'){
	                count++;
	                xaxis[i]=true;yaxis[j]=true;
	            }
	        }
	    }
	    if(count==0){
	        //std::cout << -1 << std::endl;
	        for(int i=0;i<n;i++){
	            for(int j=0;j<m;j++){
	                cout<<"-1 ";
	            }cout<<"\n";
	        }
	    }
	    else{
	        /*
	         1 2 3 4 5 6 ........ m
	         2 
	         3 
	         4
	         .
	         n
	        */
	        for(int i=0;i<n;i++){
	            for(int j=0;j<m;j++){
	                if(arr[i][j]=='1'){
	                    cout<<"0 ";
	                }
	                else if(xaxis[i]==true || yaxis[j]==true){
	                    cout<<"1 ";
	                }
	                else{
	                    cout<<"2 ";
	                }
	            }cout<<"\n";
	        }
	    }
	}
	return 0;
}
