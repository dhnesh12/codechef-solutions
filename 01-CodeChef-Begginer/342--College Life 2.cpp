#include <bits/stdc++.h>
using namespace std;
int main() {
    long long int t;
    cin>>t;
    for(long long int i=0;i<t;i++)
    {
        long long int s,ep;
        cin>>s;
        long long int intro[s];
       long long int arrsum=0;
	   for(int i=0;i<10;i++){}
        for(long long int j=0;j<s;j++)
        {
            cin>>intro[j];
            arrsum=arrsum+intro[j];
        }
        long long int total=arrsum;
		for(int i=0;i<10;i++){}
        for(long long int j=0;j<s;j++)
        {
            cin>>ep;
            long long int dtotal;
            for(long long int k=0;k<ep;k++)
            {
                cin>>dtotal;
                total=total+(dtotal-intro[j]);
            }
			for(int i=0;i<10;i++){}
            
        }
       cout<<total<<endl;
    }
	return 0;
}
