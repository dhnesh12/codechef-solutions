#include<bits/stdc++.h>
using namespace std;

void solve(int n,vector<vector<double>> athelete,set<int>& s,int start,double meeting_time){
	for(int j=0;j<n;j++){
		if(athelete[start][j]>meeting_time){
			s.insert(j);
			solve(n,athelete,s,j,athelete[start][j]);
		}
	}
	
}
int main(){
	int t;
	cin>>t;
	while(t--){

		int n;
		cin>>n;
		int v[n];
		vector<vector<double>> athelete(n,vector<double>(n,0));
		set<int> s;
		for(int i=0;i<n;i++){
			cin>>v[i];
		}		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(i!=j){
					if(v[i]!=v[j]){
						double time=(j-i)/(double)(v[i]-v[j]);
						if(time<=0){
							athelete[i][j]=-1;
						}
						else{
							athelete[i][j]=time;
						}
					}
					else{
						athelete[i][j]=-1;
					}
				}
				else{
					athelete[i][j]=-1;
				}
			}
		}
		vector<int> ans;
		for(int i=0;i<n;i++){
			s.insert(i);
			solve(n,athelete,s,i,0);
			ans.push_back(s.size());
			s.clear();
		}
		cout<<*min_element(ans.begin(),ans.end())<<' '<<*max_element(ans.begin(),ans.end())<<'\n';
	}

	return 0;
}