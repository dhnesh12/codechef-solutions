#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin>>T;
    while(T--){
        int n;
        double del, d, sum;
        cin>>n;
        bool isPos = true;
        double r1[n], r2[n];
        for(int i=0;i<n;i++) {
            cin>>r1[i];
            if(r1[i] == 0 && i != 0) isPos = false;
        }
        for(int i=0;i<n;i++) {
            cin>>r2[i];
            if(r2[i] == 0 && i != n-1) isPos = false;
        }
        if(r1[n-1] == r2[0] && r1[0] == 0 && r2[n-1] == 0){
            d = r2[0];
            for(int i=1;i<(n-1);i++){
                if(!isPos) break;
                del = r1[i] - r2[i];
                del = (del >= 0) ? del : -1*del;
                sum = r1[i] + r2[i];
                if(!(sum >= d && del <= d)){
                    isPos = false;
                    break;
                }
            }
        } else {
            isPos = false;
        }
        if(isPos) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}
