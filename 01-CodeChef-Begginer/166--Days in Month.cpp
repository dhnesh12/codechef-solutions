#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int i,j,k,t,n;
	cin>>t;
	for(i=0;i<t;i++){
		char s1[10];
		cin>>n>>s1;
		if(strcmp(s1,"mon")==0)
            j=0;
        else if(strcmp(s1,"tues")==0)
            j=1;
        else if(strcmp(s1,"wed")==0)
            j=2;
        else if(strcmp(s1,"thurs")==0)
            j=3;
        else if(strcmp(s1,"fri")==0)
            j=4;
        else if(strcmp(s1,"sat")==0)
            j=5;
        else if(strcmp(s1,"sun")==0)
            j=6;
		k=n/7;
		int array[7]={k,k,k,k,k,k,k};
		k=n%7;
		for(;k>=1;k--,j++){
			j%=7;
			array[j]++;
		}
		for(j=0;j<7;j++)
			if(j==0)
				cout<<array[j];
			else
				cout<<' '<<array[j];
		cout<<endl;
	}
	return 0;
}

