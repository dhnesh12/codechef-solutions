# cook your dish here
n,m=map(int,input().split())
while m>0:
    m-=1
    k=int(input())
    f=abs(2*n+1-k)
    ans=n-f
    if ans<=0:
        print(0)
    else:
        print(ans)