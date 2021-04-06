#include <iostream>
#include <vector>
#include <set> 
#include <map>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;
typedef long long int ll;
unsigned X; // we assume that unsigned is a 32bit integer type

void srand1(unsigned S){
  X = S;
}

unsigned nextInteger1(void){
  X = X * 1103515245 + 12345;
  return (X / 65536) % 32768;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        int n;
        n=s.length();
        int status=0;
        for(unsigned i=0;i<=132000;++i){
            srand1(i);
            int j;
            for(j=0;j<n;++j){
                char ch=nextInteger1()%2+48;
                if(ch!=s[j]){
                    break;
                }
            }
            if(j==n){
                cout<<"LCG"<<endl;
                status=1;
                break;
            }
        }
        if(status==0)cout<<"Xorshift"<<endl;
    }
    return 0;
}