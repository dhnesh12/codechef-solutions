#include<bits/stdc++.h>
using namespace std;
const int MX=1345;
const int N=1e6+2;
const int inf=1e9+7;
int val[MX][MX],ans[N];
vector<int> divi;
unordered_map<int,int> idx;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t,n,i,j,k,l,c;
	cin>>t;
	while(t--){
		cin>>n>>c;
		if(n==1){
			cout<<c<<'\n';
			continue;
		}
		if(c==1){
			for(i=1;i<=n;i++){
				cout<<i<<' ';
			}
			cout<<'\n';
			continue;
		}
		divi.clear();
		for(i=1;i*i<=c;i++){
			if(c%i==0){
				if(i*i==c){
					divi.push_back(i);	
				}
				else{
					divi.push_back(i);
					divi.push_back(c/i);
				}
			}
		}
		divi.push_back(0);
		sort(divi.begin(),divi.end());
		int uoc=divi.size()-1;
		for(i=1;i<=uoc;i++){
			idx[divi[i]]=i;
			if(i==1){
				for(j=1;j<=uoc;j++){
					val[i][j]=0;
				}
				continue;
			}
			for(j=1;j<=uoc;j++){
				val[i][j]=inf;
			}
			for(j=1;j<=uoc;j++){
				if(divi[i]%divi[j]==0){
					int z=j;
					if(z==1||divi[z-1]+1!=divi[z]){
					}
					else{
						z--;
					}
					val[i][z]=min(val[i][z],val[idx[divi[i]/divi[j]]][j]+1);
				}
			}
			for(j=2;j<=uoc;j++){
				val[i][j]=min(val[i][j],val[i][j-1]);
			}
			// for(j=1;j<=uoc;j++){
			// 	cout<<i<<' '<<j<<' '<<val[i][j]<<endl;
			// }
		}
		int tichnow=uoc,now=uoc;
		for(i=1;i<=uoc;i++){
			if(val[idx[divi[tichnow]/divi[i]]][i]<n){
				ans[n]=i;
				tichnow=idx[divi[tichnow]/divi[i]];
				now=i;
				break;
			}
		}
		// cout<<divi[tichnow]<<' '<<divi[now]<<endl;
		for(i=1;i<n;i++){
			int z=now;
			if(z==uoc||divi[z]+1!=divi[z+1]){
			}
			else{
				z++;
			}
			while(z){
				if(divi[tichnow]%divi[z]==0&&val[idx[divi[tichnow]/divi[z]]][z]<n-i){
					tichnow=idx[divi[tichnow]/divi[z]];
					ans[n-i]=z;
					break;
				}
				z--;
			}
			now=z;
		}
		for(i=1;i<=n;i++){
			cout<<divi[ans[i]]+i-1<<' ';
		}
		cout<<'\n';
	}
}