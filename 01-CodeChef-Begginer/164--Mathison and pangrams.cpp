#include<iostream>
using namespace std;
int main()
{
	int i,j,cost,t,array[26],c[26];
	char s[50500];
	cin>>t;
	for(i=0;i<t;i++){
		for(j=0;j<26;j++)
			c[j]=0;
		for(j=0;j<26;j++)
			cin>>array[j];
		cin>>s;
		for(j=0;s[j]!='\0';j++){
			c[s[j]-'a']++;
		}
		cost=0;
		for(j=0;j<26;j++){
			if(c[j]==0)
				cost+=array[j];
		}
		cout<<cost<<endl;
	}
	return 0;
}
