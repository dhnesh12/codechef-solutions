#include <bits/stdc++.h>
using namespace std;
int solve()
{
    int N,i,g[7][7],p[7]={0,1,2,3,4,5,6},arr[1000];
	    cin>>N;
	    memset(g,0,sizeof(g));
	    for(int i=1;i<=N;i++){cin>>arr[i];g[arr[i]][arr[i-1]]=g[arr[i-1]][arr[i]]=1;}
	    do{
	        for(i=1;i<=6;i++){if(g[i][i]){cout<<-1<<endl;return 0;}}
	        for(i=1;i<=6;i++){if(p[i]==i){break;}}
	        if(i>6){for(i=1;i<=6;i++){if(p[p[i]]!=i){break;}}}
	        if(i>6){for(i=1;i<=6;i++){if(g[i][p[i]]){break;}}}
	        if(i>6){for(i=1;i<=6;i++){cout<<p[i]<<" ";}cout<<endl;return 0;}}
	    while (next_permutation(p+1, p+7));
	    cout<<-1<<endl;
}
int main() {
	int t;
	cin>>t;
	while(t--)
	{
	    solve();
    }
	return 0;
}
