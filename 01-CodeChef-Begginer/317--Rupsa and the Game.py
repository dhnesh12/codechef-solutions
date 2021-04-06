for _ in range(int(input())):
    n = int(input())
    l=list(map(int,input().split()))
    a=l[0]
    k=1
    j=0
    for i in range(1,n+1):
        j=2*j+2*a*l[i]%1000000007
        a=a+k*l[i]%1000000007
        k=(k*2)%1000000007
    ans=j%1000000007
    print(ans)