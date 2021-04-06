#include <bits/stdc++.h>
typedef long long ll;

using namespace std;
#define ma -1e18;
#define mi 1e18;

int main() {

int n;
cin>>n;
int maxm=0,cnt=0,a;
for(int i=0;i<n;i++){
    cin>>a;
    if(a!=0){
        cnt++;
    }
    else{
        
        cnt=0;
    }
    if(cnt>maxm){
        maxm=cnt;
    }
}
cout<<maxm<<endl;
	return 0;
}