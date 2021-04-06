#include <bits/stdc++.h>
typedef long long ll;

using namespace std;
#define maxm -1e18;
#define mi 1e18;

int main() {
int t;
cin>>t;
while(t--){
        int n;

    cin>>n;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int sum=0;
    int sum1=0;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(a[i]>a[j]){
                sum++;
            }
        }
        if(a[i]>a[i+1]){
            sum1++;
        }
    }
    if(sum==sum1){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
}
	return 0;
}