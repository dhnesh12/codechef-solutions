#include <iostream>
#include <string>
#include <cmath>
using namespace std;
long long int check(long long int temp)
{
    long long int sum=0;

       while(temp>0)
       {
            sum=sum+temp%10;
            temp=temp/10;
       }
if(sum/10==0)
   return sum;
else
   return check(sum);

}
int main()
{
    long long int t;
    cin>>t;
    while(t--)
    {
        long long int a,n;
        cin>>a>>n;
        long long int ans;
            ans=check(pow(a,n));

        cout<<ans<<endl;
    }

    return 0;
}