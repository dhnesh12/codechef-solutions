#include<iostream>
using namespace std;

int main(){
	int t;
	cin>>t;
	int n,m;
	while(t--){
		cin>>n>>m;
		if(n==1){
			cout<<m<<endl;
		}
		else if(n==2){
			int l=(m/6)*4;
			int l1=m%6>1?4:2;
			if(m%6==0)
			l1=0;
			//cout<<l1;
			//cout<<l;
			int k=l1+l;
			cout<<k<<endl;
		}
		else if(n==3){
			int l=(m/6)*4;
			int l1;
			if(m==1)
			l1=3;
			else if(m>8 && m%6==0)
			l1=0;
			else if(m>8 && m%6==1){
				l1=2;
			}
			else if(m>8 && m%6==2){
				l1=3;
			}
			else if(m> 8 && m%6>2){
				l1=4;
			}
			else{
				if(m%6==0)
				l1=0;
				else if(m%6==1)
				l1=2;
				else
				l1=4;
			}
			//cout<<l1;
			//cout<<l;
			int k=l1+l;
			cout<<k<<endl;
		}
	}
}