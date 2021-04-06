
def test():
    n = int(input())
    a = list(map(int,input().split()))
    ans = sum(a)
    k = int(input())
    x = int(input())
    d = [(a[i]^x)-a[i] for i in range(n)]
    d.sort(reverse=True)
    pre = [0 for i in range(n+1)]
    pre[0] = 0
    for i in range(1,n+1):
        pre[i] = pre[i-1]+d[i-1]
    c = 0
    for i in range(n):
        if d[i]>0:
            c+=1
    i=0
    j=k
    sm = 0
    while i<j:
        dd = j-i
        kk = c//dd
        kk = kk*dd
        sm = max(sm,pre[kk])
        if dd+kk <= n:
            sm = max(sm,pre[dd+kk])
        i+=1
        j-=1
        if k==n:
            break
    ans += sm
    print(ans)


tt = int(input())
for _ in range(tt):
    test()