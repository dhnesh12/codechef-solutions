#include<iostream>
#include<vector>
using namespace std;
int x[10],y[10];
int a[10]={119,36,93,109,46,107,123,37,127,111};
int b[10]={6,2,5,5,4,5,6,3,7,6};
int count(int m){
	int cou=0;
	for(int i=0;i<=6;i++){
		if(((1<<i) & m)==(1<<i)){
			cou++;
		}
	}
	return cou;
}


vector<int> solve(int n){
	vector<int> vect;
	for(int i=0;i<=127;i++){
		int z=0;
		for(int j=0;j<n;j++){
			int m=i& a[x[j]];
			int k=count(m);
			if(k == y[j]){
				continue;
			}
			else{
				z=1;
				break;
			}
		}
		if(z==0){
			//cout<<i<<" ";
			vect.push_back(i);
		}
	}
	return vect;
}

int main(){
	pair<int,int> p;
	int t,n;
	int l,z;
	cin>>t;
	while(t--){
		cin>>n;
		if(n==1){
			cin>>l>>z;
			if(b[l]<z){
				cout<<"invalid"<<endl;
			}
			else{
				int m=b[l]-z;
				cout<<m<<" "<<7-z<<endl;
			}
		}
		else{
			for(int i=0;i<n;i++)
				cin>>x[i]>>y[i];
				vector<int> v;
				v=solve(n);
				int min=8;
				int max=0;
				int cou;
				for(int it=0;it<v.size();it++){
					//cout<<it<<" ";
					cou=7-count(v[it]);
					//cout<<cou<<" ";
					if(cou<min){
						min=cou;
					}
					if(cou>max){
						max=cou;
					}
				}
				if(v.empty()){
					cout<<"invalid"<<endl;
				}
				else{
					cout<<min<<" "<<max<<endl;
				}
		}
	}
	return 0;
}