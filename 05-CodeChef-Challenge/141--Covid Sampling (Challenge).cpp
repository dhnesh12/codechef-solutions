#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
using namespace std; 
typedef long long ll;



void testcases(int Case)
{
    int N , P;
    cin >> N >> P;
    
    int arr[N+2][N+2];
    int X;
    for(int i = 1; i <= N ; i ++){
      for(int j = 1 ; j<= N  ; j ++){
        cout << 1 << " " << i << " " << j << " " << i << " " << j << endl;
        cin >> X;
        arr[i][j] = X;
      }
    }
  cout << 2 << endl;
  for(int i = 1;i <= N ; i ++){
    for(int j = 1 ; j <= N ; j ++){
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
  cin >> X;
  if(X==-1)
    return ;
}

  
int main()
{
 // sieve();
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
    ll t;
    t = 1;
    cin >> t;
    ll Case =1 ;
    while(t--)
    {
      testcases(Case++);
    }
}