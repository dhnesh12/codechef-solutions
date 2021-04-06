#include <iostream>
using namespace std;

int main() {
long long int a,b,c,d,e,f;
cin>>a;
for(b=0;b<a;b++)
{
      cin>>c;
      long long int arr[c],arr2[c],x;
      x=0;
      for(d=0;d<c;d++)
     { cin>>arr[d];
     arr2[d]=2*arr[d];
     
     
     x=x^arr2[d];

     }
     cout<<x<<endl;
}
	return 0;
}
