#include <bits/stdc++.h>

using namespace std;
//#define gc getchar_unlocked

//void scanint(int &x)
//{
  //  register int c = gc();
   // x = 0;
   // for(;(c<48 || c>57);c = gc());
   // for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
//}
bool isSubsetSum(int sett[],int l,int r, int sum)
{
   // Base Cases
   if (sum == 0)
     return true;
   if (l-1 == r && sum != 0)
     return false;

   // If last element is greater than sum, then ignore it
   if (sett[r-1] > sum)
     return isSubsetSum(sett,l, r-1, sum);

   /* else, check if sum can be obtained by any of the following
      (a) including the last element
      (b) excluding the last element   */
   return isSubsetSum(sett,l, r-1, sum) || isSubsetSum(sett,l, r-1, sum-sett[r-1]);
}
/*bool isSubsetSum(int set[], int n, int sum)
{
    // The value of subset[i][j] will be true if there is a subset of set[0..j-1]
    //  with sum equal to i
    bool subset[sum+1][n+1];

    // If sum is 0, then answer is true
    for (int i = 0; i <= n; i++)
      subset[0][i] = true;

    // If sum is not 0 and set is empty, then answer is false
    for (int i = 1; i <= sum; i++)
      subset[i][0] = false;

     // Fill the subset table in botton up manner
     for (int i = 1; i <= sum; i++)
     {
       for (int j = 1; j <= n; j++)
       {
         subset[i][j] = subset[i][j-1];
         if (i >= set[j-1])
           subset[i][j] = subset[i][j] || subset[i - set[j-1]][j-1];
       }
     }

     // uncomment this code to print table
     for (int i = 0; i <= sum; i++)
     {
       for (int j = 0; j <= n; j++)
          printf ("%4d", subset[i][j]);
       printf("\n");
     }

     return subset[sum][n];
}*/
int main()
{
    int n,q;
    int i,a[100099];
    //scanint(n);
    //scanint(q);
    scanf("%d%d",&n,&q);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    while(q--)
    {
        int x;
        scanf("%d",&x);
        if(x==1)
        {
            int q,w;
            cin>>q>>w;
            a[q-1]=w;
        }
        else if(x==2)
        {
            int l,r;
            cin>>l>>r;
            l--;
            r--;
            int tt=r;
            for(int j=l;j<=(l+r)/2;j++)
            {
                /*int temp=a[j];
                a[j]=a[tt];
                a[tt]=temp;*/
                swap(a[j],a[tt]);
                tt--;
            }
        }
        else if(x==3)
        {
            int l,r,w;
            cin>>l>>r>>w;
            //int temp[100099];
            /*int j=0;
            for(i=l-1;i<r;i++)
            {
                temp[j]=a[i];
                j++;
            }*/
            if(isSubsetSum(a,l,r,w))
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }

        }
        /*cout<<"arr is  ";
        for(i=0;i<n;i++)
        {
            cout<<a[i]<<" ";
        }
        cout<<endl;*/
    }
    return 0;
}
