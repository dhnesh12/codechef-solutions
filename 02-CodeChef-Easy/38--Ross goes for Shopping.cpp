#include<iostream>
#include<cstring>
using namespace std;
int A[100001];
int mass[20][1<<20];
int cal[20][100000];
int cal1[20];
int solve(int n,int m,int X[],int mask,int z,int start){
	if(z==m){
		return 0;
	}
	if(mass[z][mask]!=-1){
		return mass[z][mask];
	}
	else{
		int min=999999999;
		for(int i=0;i<m;i++){
			if((mask & (1<<i))==0)
			continue;
			int total=0;
			int j;
			if(start==0)
			total=cal1[i]-cal[i][cal1[i]-1];
			else{
				total=cal1[i]-cal[i][cal1[i]+start-1]+cal[i][start-1];
			}
			/*for(j=start;j<start+cal[i];j++){
				if(X[j]!=(i+1))
				total++;
			}*/
			//cout<<total<<" ";
			total=total+solve(n,m,X,(mask ^ (1<<i)),z+1,cal1[i]+start);
			//cout<<total<<endl;
			if(min>total)
			min=total;
		}
		return mass[z][mask]=min;
	}
}


int main(){
	memset(mass,-1,sizeof(mass));
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>A[i];
		cal1[A[i]-1]++;

		for(int j=0;j<m;j++){
			if(A[i]-1==j){
				if(i==0){
					cal[j][i]=1;
				}
				else{
					cal[j][i]=cal[j][i-1]+1;
				}
			}
			else{
				if(i==0){
					cal[j][i]=0;
				}
				else{
					cal[j][i]=cal[j][i-1];
				}
			}
		}
		
	}
	//for(int i=0;i<m;i++)
	//cout<<cal1[i];
	int ans=solve(n,m,A,(1<<m)-1,0,0);
	cout<<ans;
}