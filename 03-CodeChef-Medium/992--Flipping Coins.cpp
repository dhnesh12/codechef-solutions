#include <bits/stdc++.h>
using namespace std;
#define int long long
#define M  100000000000000000
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define PI 3.14159265
#define pb push_back
#define LLMX LONG_LONG_MAX
#define LLMN LONG_LONG_MIN
#define double long double
int n , m , k;   
vector < int > arr , sol; 
vector < int > graph[200005] ;
int tree[1000006] , lazy[1000006] ; 
int query( int i , int l , int r , int ql,  int qr )
{
  if( lazy[i]%2 != 0)
  {
    int siz = r - l + 1 ; 
    int sum = tree[i] ; 
    tree[i] = siz - sum ; 
    lazy[i]-- ; 
      lazy[2*i+1]++ ; 
      lazy[2*i+2]++ ;

  }
  if( l > r || ql > r || qr < l)
  return 0 ; 
 // cout << i << " " << l << " " << r << ".\n" ;
  
  if( l >= ql && r <= qr)
  {
   // cout << l << " " << r << "\n" ;
    return tree[i] ; 
  }
  int mid = (l+r)/2 ; 
  return query( 2*i + 1 , l , mid , ql , qr) + query( 2*i + 2 , mid + 1 , r , ql , qr) ; 
}
void update( int i , int l , int r , int ul , int ur)
{
  if( lazy[i]%2 != 0)
  {
    int siz = r - l + 1 ; 
    int sum = tree[i] ; 
    tree[i] = siz - sum ; 
    lazy[i]-- ; 
    lazy[2*i+1]++ ; 
    lazy[2*i+2]++ ; 
  }
  if( l > r || ul > r || ur < l)
  return  ; 
 
  if( l >= ul && r <= ur)
  {
    int siz = r - l + 1 ; 
    int sum = tree[i] ; 
    tree[i] = siz - sum ;
    lazy[2*i+1]++ ; 
    lazy[2*i+2]++ ; 
    return ; 
  }
  int mid = ( l +r)/2 ; 
  update(2*i + 1 , l , mid , ul , ur) ; 
  update(2*i + 2 , mid +1 , r , ul , ur) ;
  tree[i] = tree[2*i+1] + tree[2*i +2] ;  
}
signed main()
{
  cin >> n  >> k ; 
  while(k--)
  {
    int i , a , b ; 
    cin >> i >> a >> b ; 
    if( i == 0)
    {
      update( 0 , 0 , n -1 , a , b) ; 
    }
    else
    {
      cout << query( 0 , 0 , n -1 , a , b) << "\n" ; 
    }
    // for(int x = 0 ; x <= 12 ; x++)
    // cout << x << "\t";
    // cout << "\n" ;
    // for(int x = 0 ; x <= 12 ; x++)
    // cout << tree[x] << "\t";
    // cout << "\n" ;
    // for(int x = 0 ; x <= 12 ; x++)
    // cout << lazy[x] << "\t";
    // cout << "\n" ;
  }

}