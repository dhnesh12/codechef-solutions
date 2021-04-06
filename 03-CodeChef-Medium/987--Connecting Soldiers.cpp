#include<bits/stdc++.h>

using namespace std;

int min_gen(int s, int e){
    int mid = (e+s)/2;
    if (e-s <= 1) return 0;
    return (e-s) + min_gen(s, mid) + min_gen(mid, e);
}

int main(){
    int t;
    cin>>t;

    for(int i=0; i<t; i++){
        int n, m;
        cin>>n>>m;
        int max_val = ((n+1)*(n+2))/2 - 1;
        int min_val = min_gen(0, n+1);
        if(m>=max_val){
            cout<<m-max_val<<endl;
        }
        else if(m < min_val){
            cout<<-1<<endl;
        } else {
            cout<<0<<endl;
        }
    }

    return 0;
}