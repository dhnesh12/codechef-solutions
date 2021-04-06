def funtion(a,n):
    s = 0
    for i in range(n):
        s += a[i]*(i-(n-i-1))
    return s*2
        

for _ in range(int(input())):
    n = int(input())
    a = sorted(list(map(int,input().split())))
    b = []
    for i in range(n-1):
        for j in range(i+1,n):
            b.append(a[i]+a[j])
    n
    b.sort()
    e = funtion(b,len(b))
    f = funtion(a,n)
    g = e-f*(n-2)
    print(g)
    