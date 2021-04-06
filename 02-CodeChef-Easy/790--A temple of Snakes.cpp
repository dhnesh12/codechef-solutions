#include <iostream>
#define ll long long
using namespace std;

int main()
{
    ll t;
    cin >>t;
    while(t--)
    {
        ll sum  = 0;
        ll n;
        cin >> n;
        ll a[n];
        for(ll  i = 0;i<n;i++)
        {
                cin >> a[i];
              sum += a[i];
        }
        ll left[n],right[n];

        left[0] = 1;
        for(ll i = 1;i<n;i++)
            left[i] = min(left[i-1]+1,a[i]);


      //  for(int i= 0;i<n;i++)cout << left[i] << " ";

        right[n-1] = 1;



        for(ll i = n-2;i>=0;i--)
            right[i] = min(right[i+1]+1,a[i]);

        //for(int i= 0;i<n;i++)cout << right[i] << " ";

        ll ma = -1;

        for(ll i = 0;i<n;i++)
        {
            ma = max(ma,min(left[i],right[i]));
        }

        cout << sum - ma*ma  << endl;
    }
    return 0;
}
