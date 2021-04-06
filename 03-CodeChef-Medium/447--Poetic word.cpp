#include<iostream>
#include<memory.h>
using namespace std;
int m=26,n;
int num[30];
bool r[250][30];
bool used[30]; 
int link[30][250];
char ans[250];

bool find(int x){
	for(int i=1;i<=m;i++){
		if(r[x][i]&&!used[i]){
			used[i]=1;
			if(link[i][0]<num[i]){
				link[i][0]++;
				link[i][link[i][0]]=x;
				return true;
			}
			for(int j=1;j<=num[i];j++){
				if(find(link[i][j])){
					link[i][j]=x;
					return true;
				}
			}
		}
	}
	return false;
}
int hungary(int x){
	int re=0;
	for(int i=1;i<=m;i++)link[i][0]=0;
	for(int i=x;i<=n;i++){
		memset(used,0,sizeof(used));
		if(find(i))re++;
	}
	return re;
}
bool DFS(int x){
	if(x>=n+1)return true;
	for(int i=1;i<=m;i++){
		if(!num[i])continue;
		if(!r[x][i])continue;
		num[i]--;
		ans[x]='a'+i-1;
		if(hungary(x+1)==n-x&&DFS(x+1))return true;
		num[i]++;
	}
	return false;
}
int main(){
	int T;
	for(int i=1;i<205;i++){
		for(int j=1;j<=26;j++){
			if(i%j==0)r[i][j]=1;
			else r[i][j]=0;
		}
	}
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=m;i++){
			scanf("%d",&num[i]);
		}
		if(DFS(1)){
			for(int i=1;i<=n;i++){
				printf("%c",ans[i]);
			}
			printf("\n");
		}
		else{
			printf("#rekt\n");
		}
	}
}