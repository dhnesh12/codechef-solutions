#include<bits/stdc++.h>
using namespace std;
struct Node{
	int x,y;
	Node(){}
	Node(int a,int b):x(a),y(b){}
	Node operator +(const Node &w) {return Node(x+w.x,y+w.y);}
	Node operator -(const Node &w) {return Node(x-w.x,y-w.y);}
	Node operator *(const int  &w) {return Node(x*w,y*w);}
}a[12],b[12];
string s;
int main(){
	int t,z;
	cin>>t>>z;
	while(t--){
		for(int i=0;i<12;i++){
			cin>>s;
			if (s[0]=='W') break;
			cin>>a[i].x>>a[i].y;
			if(i<2) b[i]=a[i]*2;
			if(i==2) b[i]=(a[i]-a[i-1])*3+b[i-1];
			if(i==3) b[i]=b[i-1]+b[i-2]-a[i];
			if(i==4) b[i]=a[i]*4-a[i-1]*3;
			if(i==5) b[i]=b[i-2]+b[i-3]-a[i];
			if(i==6) b[i]=a[1]+a[i];
			if(i==7) b[i]=a[i]*2-a[i-1];
			if(i==8) b[i]=b[i-1]*2-b[i-2];
			if(i==9) b[i]=a[i-3];
			if(i==10) b[i]=a[i-1];
			cout<<"BLOCK "<<b[i].x<<" "<<b[i].y<<endl;
		}
	}
	return 0;
}