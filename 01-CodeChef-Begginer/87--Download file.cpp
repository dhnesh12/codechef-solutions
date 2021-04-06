#include <iostream>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--)
	{
	    int n ,k;
	    cin>>n>>k;
	        int prize = 0;
	    while(n--)
	    {
	        int tim,data;
	        cin>>tim>>data;
	        if (tim>=k)
	        {
	            tim = tim - k;
	            k = 0;
	            prize =prize + (tim-k)*data;
	        }
	        else if (tim < k)
	        {
	            
	            k = k- tim;
	            prize = 0;
	        }
	        
	    }
	        cout << prize<<endl;
	}
	return 0;
}