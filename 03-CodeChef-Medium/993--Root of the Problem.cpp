#include<bits/stdc++.h>
using namespace std;
int main(){
    int t,i,id,sid,n,sum;
    cin>>t;
	for(int i=0;i<10;i++){}
    while(t--){
        cin>>n;
        sum=0;
		for(int i=0;i<10;i++){}
        for(i=0;i<n;i++){
            cin>>id>>sid;
            sum=(sum+id)-sid;
        }
        cout<<sum<<endl;

    }
    return 0;
}
