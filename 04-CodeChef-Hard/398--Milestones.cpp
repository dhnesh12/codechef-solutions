#include<cstdio>
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

const int MAXN = 1e5 + 5;

int x[MAXN],y[MAXN];

int main(){
	srand(time(NULL));
	
	int T;
	
	scanf("%d",&T);
	
	while (T--){
		int ans = 1;
		int n;
		scanf("%d",&n);
		
		for (int i = 1;i <= n;i++){
			scanf("%d%d",&x[i],&y[i]);
		}
		
		if (n <= 2){
			printf("%d\n",n);
			continue;
		}
		
		for (int k = 1;k <= 1000;k++){
			int u = rand() % n + 1;
			int v = rand() % n + 1;
			
			while (u == v){
				u = rand() % n + 1;
				v = rand() % n + 1;
			}
			
			int cnt = 0;
			
			for (int i = 1;i <= n;i++){
				int dis1 = (x[u] - x[v]) * (y[u] - y[i]);
				int dis2 = (x[u] - x[i]) * (y[u] - y[v]);
				
				if (dis1 == dis2){
					cnt++;
				}
				
			}
			ans = max(ans,cnt);
			
		}
		
		printf("%d\n",ans);
	}
	
	return 0;
}