#include <bits/stdc++.h>
using namespace std;
typedef double dd;
int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;
       dd sum=0;
        for (int i = 0; i < n; i++)
        {
            dd p, q, d;
            cin >> p >> q >> d;
          //  dd sum ;

            dd ans = p * (d / 100);
            // cout<<ans<<"\n";
            dd  new_ans = p + ans;
            // cout<<new_ans<<endl;
            dd  discount = new_ans * (d / 100);
            // cout<<discount<<endl;
           dd  final_price = new_ans - discount;
            //cout<<final_price;
            final_price = p - final_price;
            // cout<<final_price;
            sum = sum+final_price * q;
            //  cout<<sum<<endl;
          //  cout << fixed << setprecision(9) << sum << "\n";
        }
        cout << fixed << setprecision(7) << sum << "\n";
    }
}