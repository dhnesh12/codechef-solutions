#include <iostream>
using namespace std;

int main() {
    long long int t;
    cin>>t;
    while(t--)
    {
        long long int n,k,x=0;
        cin>>n>>k;
        if(k==0)
        {
            cout<<n<<endl;
        }
        else
        {
            x=n%k;
            cout<<x<<endl;
        }
    }
	return 0;
}
