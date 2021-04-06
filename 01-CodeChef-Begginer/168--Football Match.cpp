#include<bits/stdc++.h>
#include<cstring>
using namespace std;
int main()
{
	int t,i,j,k,m,n;
	cin>>t;
	for(i=0;i<t;i++){
		cin>>n;
		char s1[n+50],s2[n+50],s3[n+50];
		k=0,m=0;
		for(j=0;j<n;j++){
			cin>>s1;
			if(j==0){
				k++;
				strcpy(s2,s1);
			}
			else{
				if(strcmp(s1,s2)==0)
					k++;
				else{
					if(m==0)
					    strcpy(s3,s1);
					m++;
				}
			}
		}
		if(k>m)
			cout<<s2<<endl;
		else if(m>k)
			cout<<s3<<endl;
		else
			cout<<"Draw"<<endl;
	}
	return 0;
}
