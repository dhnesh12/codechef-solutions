#include <iostream>
#include <map>
#include <utility>
using namespace std;

void solve(){
    string str;
    cin>>str;
    map<char,int> mapping;
    for(int i=0;i<str.length();i++){
        
        char temp = str[i];
        
        if(mapping.count(temp))
           {
               mapping[temp] += 1;
               
           }
        else{
            
        
            mapping[temp] = 1;
        }
    }
    char ans = '9';
    for(pair<char,int> p : mapping)
    {
        if(p.second == 2)
            ans = p.first;
    }
    if(ans == '9')
    cout<<-1<<"\n";
    else
    cout<<ans<<"\n";
    
}

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	    solve();
	return 0;
}
