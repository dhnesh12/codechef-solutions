#include<bits/stdc++.h>
#include<cstring>
#define   ll         long long
#define   ull        unsigned long long
#define   pb         push_back
#define   ff         first
#define   ss         second
#define   all(v)     (v.begin(), v.end())
#define   rall(v)    (v.rbegin(), v.rend())
#define   pi         acos(-1.0)
#define   FastRead   ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
#define   bug(a)     cerr << #a << " : " << a << endl
using namespace std;
const ll mod = 1e9+7;
const ll mx = 2e6+10;

int posx[] = {1,-1, 0, 0};
int posy[] = {0, 0, 1,-1};

int ask(int x, int y)
{
    cout << x << " " << y << endl;
    int q;
    cin >> q;
    return q;
}

int main()
{
    FastRead

    ll t=1, n, k, m, c, d;
    cin >> t;

    while(t--){
            cin >> n;
            int x=ask(1, 1);
            int left=1, right=n, pos;

            while(left<=right){
                    int mid=(left+right)>>1;
                    int q=ask(1, mid);
                    if(q==x){
                            pos=mid;
                            left=mid+1;
                    }
                    else right=mid-1;
            }
            int last=ask(1, n);
            int a=ask(1, n-pos+1);

            if(last!=a){
                    cout << 2 << " " << last << endl;
            }
            else{
                    a=ask(1, n-pos);
                    if(last==a){
                             cout << 2 << " " << x << endl;
                    }
                    else{
                             int pos2;
                             left=1, right=(n/pos);
                             while(left<=right){
                                      int mid=(left+right)>>1;
                                      int xx=ask(1, pos*mid+1);
                                      int yy=ask(1, pos*mid);

                                      if(xx!=yy){
                                             pos2=mid;
                                             left=mid+1;
                                      }
                                      else right=mid-1;
                             }
                             cout << 2 << " " << ask(1, pos*pos2+1) << endl;
                    }
            }
    }
    return 0;
}