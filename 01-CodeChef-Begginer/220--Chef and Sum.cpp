#include <iostream>
using namespace std;

int main() {
    int n;
    cin>>n;
    while(n--)
    {
        int k,p,c=0;
        cin>>k>>p;
        int a[k];
        for(int i=0;i<k;i++)
        {
            cin>>a[i];
        }
        for(int i=0;i<k;i++)
        {
            for(int j=i+1;j<k;j++)
            {
                if(a[i]+a[j]==p)
                {
                    c=1;
                    break;
                }
            }
        }
        if(c==1)
        cout<<"Yes"<<endl;
        else
        cout<<"No"<<endl;
        
        
    }
	
	return 0;
}
