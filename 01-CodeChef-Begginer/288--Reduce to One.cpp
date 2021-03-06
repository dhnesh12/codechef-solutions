#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
using namespace std;

int main() {
    vector<long long int> v(1000001);
    v[1] = 1;
    for(int i = 2; i <= 1000001; i++){
        v[i] = ((v[i-1]*i) % 1000000007);
    }
     int cases;
     cin>>cases;
     while(cases--){
         long long int n;
         cin>>n;
         cout<<v[n+1]-1<<endl;
     }
	return 0;
}
