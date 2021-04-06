#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(n == 2 or n == 17){  // remove combs of 2 & 17
            cout << "Mike\n";
        }else if(n == 34 or n == 16 or n == 289){   // for these 2 from above 2 exceptions
            cout << "Tom\n";
        }else{
            int f = 0;
            for(int i=2; i*i<=n; i++){
                if(n%i==0){f = 1; break;}
            }
            cout << (f == 1 ? "Mike\n" : "Tom\n");
        }
    }
}