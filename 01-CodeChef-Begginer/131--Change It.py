for _ in range(int(input())):
    n = int(input())
    a = list(map(int,input().split()))
    if len(set(a))==1:
        print(0)
    else:
        max1=0
        for i in set(a):
            max1=max(max1,a.count(i))
        print(n-max1)