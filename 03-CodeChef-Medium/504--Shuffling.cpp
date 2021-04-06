#define fo(i,n) for(i=0;i<n;i++)
#define print(p) printf("%d\n",p)
#define take(n) scanf("%d",&n)
#include<stdio.h>
#include<vector>
#include<iostream>
using namespace std;
int main()
{
    int t,m,x,y,s,i;
    take(t);
    while(t--)
    {
        vector <int> A,B,C;
        scanf("%d%d%d",&m,&x,&y);
        for(i=1;i<=m;i++)
            A.push_back(i);
        while(m>2){
        fo(i,m)
        {
            B.push_back(A[i]);
            i++;
            C.push_back(A[i]);
        }
        s=((m/2)*x)/y;
        B.erase(B.begin()+s);
        m--;
        C.erase(C.begin()+s);
        m--;
        A.clear();
        A.insert(A.begin(),B.begin(),B.end());
         A.insert(A.end(),C.begin(),C.end());
        B.clear();
        C.clear();
            }
        print(A[0]^A[1]);
    }
}
