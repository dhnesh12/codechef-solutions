#include<bits/stdc++.h>

using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int l,d,c,flag=1;
        long long s;
        cin >> l>>d>>s>>c;
        for(int i=0;i<d-1;i++){
            s = s + s*c;
            if(s>=l){cout << "ALIVE AND KICKING"<<endl;flag=0;break;}
        }
        if(flag == 1 && s>=l){
            cout << "ALIVE AND KICKING"<<endl;
        }
        else if(flag == 1) cout << "DEAD AND ROTTING"<<endl;
    }
}
