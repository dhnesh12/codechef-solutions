#include <iostream>
using namespace std;

// ans is 1 if it's not a palindrome.......final ans 2
bool chk_palin(string s){
    
    int len = s.length();
    for(int i=0; i<=len/2; i++)
    {
        if(s[i] != s[len-i-1])
            return true;
    }
    return false;
}

int main() {
	// your code goes here
	int t; cin>>t;
	while(t--)
	{
	    string s; cin>>s;
	    cout<<chk_palin(s) + 1<<endl;
	}
	return 0;
}
