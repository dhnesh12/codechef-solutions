#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;cin>>t;
    while(t--)
    {
        long long int n,k,c;
        cin>>n>>k>>c;
        long long int a[n];
        for(int i=0;i<n;i++)cin>>a[i];
        sort(a,a+n);
        long long int low=0,high=n+1;
        while(low<high-1)
        {
            long long int mid = low+ ((high-low)/2);
            vector<long long int> vec[mid];
            int nw=0;
            for (int i=0;i<n;i++){
				if(vec[nw].size()==k) {
					break ;
				}
				else if(vec[nw].empty()||(vec[nw].back()*c<=a[i])) {
					vec[nw].push_back(a[i]) ;
					nw=(nw+1)%mid;
				}
			}
		//	cout<<vec[mid-1].size()<<endl;
            if((vec[mid-1].size()==k)) {
				low=mid;
			}
			else {
				high=mid;
			}
        }
        cout<<low<<endl;
    }
	// your code goes here
	return 0;
}
