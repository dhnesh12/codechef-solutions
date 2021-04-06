#include <iostream>
#include <string.h>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--)
	{
	    char ch1[10]={0},ch2[10]={0};
	    cin>>ch1;
	    cin>>ch2;
	    int n=strlen(ch1);
	    int c=0;
	    for(int i=0;i<n;i++){
	        if(ch1[i]==ch2[i] || ch1[i]=='?' || ch2[i]=='?') c=1;
	        else {c=0; break;}
	    }
	    if(c==1) cout<<"Yes"<<endl;
	    else cout<<"No"<<endl;
	}
	return 0;
}
