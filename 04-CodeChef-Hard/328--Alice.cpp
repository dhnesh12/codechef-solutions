#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define INF INT_MAX
#define pb push_back
#define mp make_pair

typedef long long int ll;
typedef vector< pair<int,int> > vii;
typedef vector<int> vi;
typedef vector<long long int> vll;
typedef pair<int,int> pii;

int main()
{
    std::ios::sync_with_stdio(0);


    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;

        if(n==1)
        {
             cout<<0<<" "<<0<<" "<<1<<" "<<1<<endl;

         cout<<1<<" "<<0<<" "<<0<<" "<<1<<endl;

        }
        else
        {
            for(int i=1;i<=n-1;i++)
            {
                int c=2*i-1;
                int d=2*i;

                if(c<=n)
                    cout<<0<<" "<<c<<" ";
                else
                    cout<<c-n<<" "<<n<<" ";

                 if(d<=n)
                    cout<<d<<" "<<0<<endl;
                else
                    cout<<n<<" "<<d-n<<endl;
            }
            		cout << 0 << " " << 0 << " " << 1 << " " << n << endl;
		cout << n << " " << 0 << " " << n-1 << " " << n << endl;

        }
    }
    return 0;
}