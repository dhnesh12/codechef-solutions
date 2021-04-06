#include <algorithm>
#include <assert.h>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
 
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
 
int R,C;
char A[50][50];
bool valid[25][25];
int B[30][30][30][30];
 
bool check(int x,int y){
	if(x>=0 && x<R && y>=0 && y<C && A[x][y]=='^')
		return true;
	return false;
}
 
int get_num(int x1,int y1,int x2,int y2){
	int i,j,b,x,y;
	x=x2-x1;y=y2-y1;
	if(x2<x1 || y2<y1){
		return 0;
	}
	if(B[x1][y1][x2][y2]!=-1){
		return B[x1][y1][x2][y2];
	}
	bool myset[1000];
	memset(myset,false,sizeof(myset));
	for(i=x1;i<=x2;i++){
		for(j=y1;j<=y2;j++){
			if(valid[i][j]){
				b=0;
				b^=get_num(x1,y1,i-1,j-1);
				b^=get_num(x1,j+1,i-1,y2);
				b^=get_num(i+1,y1,x2,j-1);
				b^=get_num(i+1,j+1,x2,y2);
				myset[b]=true;
			}
		}
	}
	for(i=0;i<1000;i++){
		if(!myset[i]){
			B[x1][y1][x2][y2]=i;
			return i;
		}
	}
}
 
int main(){
	int T,i,j,x,k,l;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&R,&C);
		for(i=0;i<R;i++){
			scanf("%s",A[i]);
		}
		memset(valid,true,sizeof(valid));
		for(i=0;i<R;i++)
			for(j=0;j<C;j++)
				for(k=1;k<=2;k++)
					if(!check(i,j-k) || !check(i,j+k) || !check(i-k,j) || !check(i+k,j) || A[i][j]=='#')
						valid[i][j]=false;
		for(i=0;i<25;i++)
			for(j=0;j<25;j++)
				for(k=0;k<25;k++)
					for(l=0;l<25;l++)
						B[i][j][k][l]=-1;
		for(i=0;i<R;i++){
			for(j=0;j<C;j++){
				if(valid[i][j]){
					B[i][j][i][j]=1;
				}
				else{
					B[i][j][i][j]=0;
				}
			}
		}
		x=get_num(0,0,R-1,C-1);
		if(x>0){
			cout << "Asuna" << endl;
		}
		else{
			cout << "Kirito" << endl;
		}
	}	
	return 0;
} 