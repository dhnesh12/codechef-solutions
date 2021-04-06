#include <bits/stdc++.h>
using namespace std;
int main() {
	int t;std::cin >> t;
	while(t--){
	    int n,m;std::cin >> n>>m;
	    string s;std::cin >> s;
	    unordered_map<int,int>tejus;
	    int maxrow=0;int maxcol=0;
	    int minrow=0;int mincol=0;
	    int row=0;int column=0;
	    for(int i=0;i<s.length();i++){
	        if(s[i]=='U'){
	            row--;
	        }
	        else if(s[i]=='D'){
	            row++;
	        }
	        else if(s[i]=='L'){
	            column--;
	        }
	        else{
	            column++;
	        }
	        if(mincol>column){
	            mincol=column;
	        }
	        if(maxcol<column){
	            maxcol=column;
	        }
	        if(minrow>row){
	            minrow=row;
	        }
	        if(maxrow<row){
	            maxrow = row;
	        }
	    }
	    int totalrows = maxrow + 1 + abs(minrow);
	    int totalcol = maxcol + 1 +abs(mincol);
	    if(totalcol<=m && totalrows<=n){
	        std::cout << "safe" << std::endl;
	    }
	    else{
	        std::cout << "unsafe" << std::endl;
	    }
	}
	return 0;
}
