#include <iostream>

using namespace std;
typedef long long ll;
void quicksort(ll x[],ll first,ll last)
{
    ll pivot,j,temp,i;

     if(first<last){
         pivot=first;
         i=first;
         j=last;

         while(i<j){
             while(x[i]<=x[pivot]&&i<last)
                 i++;
             while(x[j]>x[pivot])
                 j--;
             if(i<j){
                 temp=x[i];
                  x[i]=x[j];
                  x[j]=temp;
             }
         }

         temp=x[pivot];
         x[pivot]=x[j];
         x[j]=temp;
         quicksort(x,first,j-1);
         quicksort(x,j+1,last);

    }
}
void func(ll*a,ll x,ll y)
{
	ll i;
	x--;
	y--;
	ll u=0;
	quicksort(a,x,y);
	for(i=x;i<=y;i++)
        cout<<a[i];
    cout<<endl;
	for(i=x;i<=y;i++)
	{
		if(a[i]==a[i+1])
        {
            continue;
        }
        else
        {
            u++;
        }
	}
	cout<<u<<endl;
}
int main()
 {
	ll n,q,a[100099],b[100099];
	cin>>n>>q;
	for(ll i=0;i<n;i++)
    {
        cin>>a[i];
        b[i]=a[i];
    }
    while(q--)
    {
        ll x,p,q;
        cin>>x>>p>>q;
        if(x==5)
        {
            func(b,p,q);
            for(ll i=0;i<n;i++)
            {
                b[i]=a[i];
            }
        }
    }
	return 0;
}
