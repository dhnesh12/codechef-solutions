#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t>0){
		t--;
		int n;
		cin>>n;
		int time=0;
		map<int,int>m;
		int a[n];
		set<int>s;
	    for(int i=0;i<n;i++){
	    cin>>a[i];
		s.insert(a[i]);
		}
		int min=*min_element(a,a+n);
		sort(a,a+n);
		for(int i=0;i<n-1;i++){
			while(a[i]==a[i+1]&& i<n-1){
				i++;
			}
			time++;
			i++;
		}
		cout<<s.size()<<endl;
		s.clear();
	}
}