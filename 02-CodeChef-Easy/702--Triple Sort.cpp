#include<bits/stdc++.h>
using namespace std;


int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		int k;
		cin>>n>>k;
		int a[n+1];
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		bool swap[n+1];
		for(int i=1;i<=n;i++){
			if(a[i]!=i){
				swap[i]=true;
			}
			else{
				swap[i]=false;
			}
		}
		
		vector<pair<int,int>> extra_swaps;
		vector<tuple<int,int,int>> ans;
		int flag=1;

		for(int i=1;i<=n;i++){
			if(swap[i]==false){
				continue;
			}
			else{
				int j=i;
				vector<int> index;
				int cycle_length=0;
				while(swap[j]==true){
					index.push_back(j);
					swap[j]=false;
					j=a[j];
					cycle_length++;
				}

				while(index.size()>2){
					int num1=index.back();
					index.pop_back();
					int num2=index.back();
					index.pop_back();
					int num3=index.back();
					if(index.size()==1){
						index.pop_back();
					}
					ans.push_back(tie(num3,num2,num1));
					k--;
				}
				if(index.size()==2){
					extra_swaps.push_back(make_pair(index[0],index[1]));
				}
			}
			while(extra_swaps.size()>1){
				ans.push_back(tie(extra_swaps[0].first,extra_swaps[0].second,extra_swaps[1].first));
				ans.push_back(tie(extra_swaps[0].first,extra_swaps[1].second,extra_swaps[1].first));
				k-=2;
				extra_swaps.clear();
			}
			if(k<0){
				flag=-1;
				break;
			}
		}
		if(extra_swaps.size()>0){
			flag=-1;
		}
		if(flag==-1){
			cout<<-1<<'\n';
		}
		else{
			cout<<ans.size()<<'\n';
			for(int i=0;i<ans.size();i++){
				cout<<get<0>(ans[i])<<' '<<get<1>(ans[i])<<' '<<get<2>(ans[i])<<'\n';
			}
		}		
	}

	return 0;
}