#include<stdio.h>
#include<stdlib.h>
#define MOD 1000000007
#define BUF 4096
    int arr[1000000];
    int temp1[1000000];
    int temp2[1000000];
    char ibuf[BUF];
    int ipt = BUF;
    int readInt()
    {
    while (ipt < BUF && ibuf[ipt] < '0')
    ipt++;
    if (ipt == BUF)
    {
    fread(ibuf, 1, BUF, stdin);
    ipt = 0;
    while (ipt < BUF && ibuf[ipt] < '0')
    ipt++;
    }
    int n = 0;
    while (ipt < BUF && ibuf[ipt] >= '0')
    n = (n*10)+(ibuf[ipt++]-'0');
    if (ipt == BUF)
    {
    fread(ibuf, 1, BUF, stdin);
    ipt = 0;
    while (ipt < BUF && ibuf[ipt] >= '0')
    n = (n*10)+(ibuf[ipt++]-'0');
    }
    return n;
    }
    int main()
    {
    int m,n,i,j,min,k;
    long long count=0;
    n=readInt();
    m=readInt();
    for(i=0;i<n;i++)
    arr[i]=readInt();
    temp2[0]=1;
    j=k=count=0;
    for(i=1;i<n;i++)
    {
    while(arr[i]-arr[j] > m)
    count-=temp2[j++];
    temp1[i]=temp1[j]+1;
    while(temp1[k]==temp1[j])
    count+=temp2[k++];
    temp2[i]=count%MOD;
    }
    printf("%d %d\n",temp1[n-1]-1,temp2[n-1]);
    return 0;
    }