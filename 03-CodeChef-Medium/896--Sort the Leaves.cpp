#include <bits/stdc++.h>
using namespace std;

struct node {
	int r,l,val,mi,ma;
};

node arr[100005] ;

int solve(int root ){
	if(arr[root].l==-1){
		return 0 ; 
	}
	int lcnt = solve(arr[root].l) ; 
	int rcnt = solve(arr[root].r) ;
	if(lcnt ==-1 || rcnt == -1)
		return -1;
	int lmi = arr[arr[root].l].mi ; 
	int lma = arr[arr[root].l].ma ;
	int rmi = arr[arr[root].r].mi ; 
	int rma = arr[arr[root].r].ma ;
	if(!(rma<=lmi || rmi>=lma))
		return -1 ;
	arr[root].ma=max(lma,rma) ;
	arr[root].mi = min(lmi,rmi) ; 
	return lcnt+rcnt + (rma<=lmi ? 1:0) ;
}

int main() {
	int t ; cin>>t ; 
	while(t--){
		int n ;
		cin>>n; 
		for(int i = 1 ;i<=n;i++){
			int l , r ; 
			cin>>l>>r;
			if(l==-1){
				arr[i].l=arr[i].r=-1;
				arr[i].val = r ; 
				arr[i].mi=arr[i].ma=r;
			}
			else 
				arr[i].l=l;arr[i].r=r;
		}
		cout<<solve(1)<<endl; 
	}
	return 0;
}