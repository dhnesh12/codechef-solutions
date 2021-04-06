#include <iostream>
using namespace std;
typedef long  long ll;
#define p 1000000007
ll power(ll  n ,ll  m,ll k)
{  
  if(m==0)
  {
    return 1;
  }
  if(m%2==0)
  {
   return power((n*n)%k,m/2,k);  
  }
  else
  {
    return ((n%k)*power((n*n)%k,m/2,p))%k;
  }
}
 
ll modInverse(int n, int l)
{
    return power(n, l-2, l);
}
int main() {
 
 
   ll n,k;
   cin>>n>>k;
      
      
      ll p1 =power(2,n-1,p);
      ll val1= modInverse(p1,p);
      ll val2=(p1-n+p)%p;
      ll result = (val2%p*val1%p)%p;
      
      cout<<result<<endl;
} 