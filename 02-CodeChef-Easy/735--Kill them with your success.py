for i in range(int(input())):
    n=int(input())
    l=[int(i) for i in input().split()]
    l.sort()
    k=n-1
    m=l[n-1]
    for j in range(n-1):
        m=(m+l[k-1])/2
        k=k-1
    print(m)