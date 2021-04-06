#include <bits/stdc++.h>
#include <string>
typedef long long int ll;
typedef unsigned long long int ull;
#define scn1(a)         scanf("%d", &a);
#define scn2(a, b)      scanf("%d %d", &a, &b);
#define scn3(a, b, c)   scanf("%d %d %d", &a, &b, &c);
#define lscn1(a)        scanf("%lli", &a);
#define lscn2(a, b)     scanf("%lli %lli", &a, &b);
#define lscn3(a, b, c)  scanf("%lli %lli %lli", &a, &b, &c);
#define prnt(a)         printf("%d\n", a);
#define forr(i, a, n)   for(int i=a;i<n;i++)
#define pll             pair<ll, ll>
#define pii             pair<int, int>
#define vi              vector<int>
#define vl              vector<ll>
#define mset(a, b)      memset((a), (b), sizeof(a))
#define PB              push_back
#define F               first
#define S               second
#define enl             cout << "\n";
#define tsttxt          cout << "\nHeyYou!\n";
#define CHK(a)          cout << (#a) << " = " << (a) << endl;
#define fast            ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define MX5             100005
#define MX6             1000006
#define MOD             1000000007
#define MIN             INT_MIN
#define MAX             INT_MAX
#define FI              freopen("input.txt", "r", stdin);
#define FO              freopen("output.txt", "w", stdout);
using namespace std;
void arraychk(int a[],int n) {for(int i=0;i<n;i++)cout<<a[i]<<" ";enl;}
#define LOOPCHK(a, n)   arraychk(a, n);

int q(int a, int b)
{
    int tmp;
    cout << 1 << " " << a << " " << b << endl;
    cin >> tmp;
    return tmp;
}

int main()
{

    ll tt=1;
    // cin >> tt;
    for(int cse=1; cse<=tt; cse++)
    {
        int n, lw = 0, lp = 0;
        cin >> n;
        int w[n+1], p[n+1];
        forr(i, 1, n+1)
        {
            int takingall = q(i, 10000);
            p[i] = takingall - lp;
            lp += p[i];
            int mid, l = 1 , r = 10000;
            while(l<=r)
            {
                mid = (l+r)/2;
                int tmp = q(i, mid);
                if(tmp!=takingall)
                    l = mid+1;
                else
                {
                    w[i] = mid - lw;
                    r = mid - 1;
                }
            }
            lw += w[i];
        }
        cout << 2 << endl;
        forr(i, 1, n+1) cout << w[i] << " "; cout << endl;
        forr(i, 1, n+1) cout << p[i] << " "; cout << endl;
    }
    return 0;
}
