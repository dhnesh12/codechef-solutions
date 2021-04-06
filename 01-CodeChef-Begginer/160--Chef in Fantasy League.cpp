#include<iostream>
using namespace std;
int main()
{
	int i,j,k,m,n,total,mina,minb;
	cin>>n;
	for(i=0;i<n;i++){
		cin>>m>>total;
		int array[m];
		mina=1000;
		minb=1000;
		for(j=0;j<m;j++){
			cin>>array[j];
		}
		for(j=0;j<m;j++){
			cin>>k;
			if(k==0){
				if(mina>array[j])
					mina=array[j];
			}
			if(k==1){
				if(minb>array[j])
					minb=array[j];
			}
		}
		total+=minb+mina;
		if(total<=100)
			cout<<"yes"<<endl;
		else
			cout<<"no"<<endl;
	}
	return 0;
}
