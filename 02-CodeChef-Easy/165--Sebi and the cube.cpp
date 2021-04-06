#include <iostream>
using namespace std;
long long int mtrx[101][1000001];

string check(long long int k,long long int c){
    long long int m=k*k*k;
    long long int s=m-c;
    if(c==0 || mtrx[k][s]==1){
        return "YES";
    }
    return "NO";
}
int main() {
    long long int t,m,v;
	for(long long int i=1;i<101;i++){
		m=i*i*i;
		for(long long int j=0;j<m;j++){
			v=(j*j*j)%m;
			mtrx[i][v]=1;
		}
	}
    cin>>t;
    for(long long int i=0; i<t; i++){
        long long int k,c;
        cin>>k>>c;
        cout<<check(k,c)<<endl;
    }
	return 0;
}
