# cook your dish here
t=int(input())
for w in range(t):
    n=int(input())
    l=list(map(int,input().split()))
    ans=0
    for i in range(n-1):
        ans+=abs(l[i+1]-l[i])-1
    print(ans)