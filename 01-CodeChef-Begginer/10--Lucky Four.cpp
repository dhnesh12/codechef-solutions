#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin>>t;
    
    string str;
    
    while(t--) {
        cin>>str;
        cout<<count(str.begin(), str.end(),'4')<<"\n";
    }

    return 0;
}