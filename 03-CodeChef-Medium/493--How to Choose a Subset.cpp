#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
const int mod=1000000000+7;
int T,N,K,B;
int dp[31][31][(1<<7)+10];
int a[31],num;
int count(int x){
	int num=0;
	while(x){
		if (x&1) num^=1; 
		x>>=1;
	}
	return num;
}
int main(){
	cin>>T;
	while(T--){
		cin>>N>>K>>B;N++;
		num=0;
		while(N){
			a[num++]=N%2;
			N>>=1;
		}
		for (int i=0;i<num/2;i++){
			swap(a[i],a[num-i-1]);
		}
		memset(dp,0,sizeof(dp));
		dp[0][0][0]=1;
		for (int i=0;i<num;i++)
			for (int j=0;j<=B;j++)
				for (int k=0;k<(1<<K);k++)if (dp[i][j][k])
					for (int mask=0;mask<(1<<K);mask++){
					//	cout<<i<<' '<<j<<' '<<k<<endl;
						int nextk=k;
						if (!(k&1)){
							int t1=(mask&1),t2=a[i];
							if (t1>t2)continue;
							if (t1<t2)nextk|=1;
						}
						bool flag=true;
						for (int l=1;l<K;l++)
							if (!(k&(1<<l)))
							{
								int t1=((mask&(1<<l))>0);
								int t2=((mask&(1<<(l-1)))>0);
								if (t1>t2){
									flag=false;break;
								}
								if (t1<t2)nextk|=(1<<l); 
							}
						if (!flag) continue;
						int cnt=count(mask);
						dp[i+1][j+cnt][nextk]+=dp[i][j][k];
						if (dp[i+1][j+cnt][nextk]>mod)
							dp[i+1][j+cnt][nextk]-=mod;
					}
		cout<<dp[num][B][(1<<K)-1]<<endl;
	}
	return 0;
}