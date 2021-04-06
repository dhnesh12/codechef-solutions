#include <iostream>

using namespace std;

int main() {
    int x;
    cin>>x;
    while(x--){
        int k,n,mn,o=0,s=0;
        cin>>n>>k;
        int a[n];
        for(int i=0;i<n;i++){
            cin>>a[i];
        }for(int i=0;i<n;i++){
            o=a[i]-k+o;
            if(o<0){
                cout<<"NO"<<" "<<i+1<<endl;
                s++;
                break;
            }
        }
        if(s==0){
            cout<<"YES"<<endl;
        }
    }
}