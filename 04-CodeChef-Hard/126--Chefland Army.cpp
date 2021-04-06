#include<stdio.h>
#include<iostream>
#include<string.h>

using namespace std;

void task()
{
    int m,n;
    scanf("%d %d",&m,&n);

    string garbage;
    for(int i=1;i<=m;i++)
        cin>>garbage;
    int s[n];
    for(int i=0;i<n;i++)
        cin>>s[i];
    int k;
    for(int i=0;i<n;++i)
        cin >> k;
    printf("%d\n",n);
    for(int i=0;i<n;i++)
        printf("1 %d %d\n",s[i],i+1);

}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++)
        task();
    return 0;
}