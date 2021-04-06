#include <bits/stdc++.h>
#define X INT_MAX;
#define endl '\n'
using namespace std;

int compare(const void* a, const void* b)
{
	const int* x = (int*) a;
	const int* y = (int*) b;

	if (*x > *y)
		return 1;
	else if (*x < *y)
		return -1;

	return 0;
}

int main()
{
    int n,m,k,l,t;
    int rem,initial,total_tym,tym_min;
    cin>>t;
    int b[t];
    for(int j=0;j<t;j++)
    {
        tym_min=X;
        cin>>n>>m>>k>>l;
        int a[n];
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
        }
        qsort(a,n,sizeof(int),compare);
        initial=m;
        for(int i=0;i<n;i++)
        {
            if(a[i]>k)
                break;
            rem=0;
            initial=initial-(a[i]/l);
            rem=a[i]%l;
            initial++;
            total_tym=(initial*l)-rem;
            if(tym_min>total_tym)
            {
                tym_min=total_tym;
            }
            m++;
            initial=m;
        }
        b[j]=min(tym_min,(++initial)*l-k);
    }
    for(int j=0;j<t;j++)
    {
        cout<<b[j]<<endl;
    }
 return 0;
}
