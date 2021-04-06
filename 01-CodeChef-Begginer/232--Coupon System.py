t = int(input())
while t > 0:
    t -= 1
    n = int(input())
    b1=b2=b3=0
    e1=e2=e3=1000
    for i in range(n):
        c,l,x = list(map(int,input().split()))
        if l==1:
            if x>b1:
                b1=x
                e1=c
            elif x==b1:
                e1 = min(c,e1)
        if l==2:
            if x>b2:
                b2=x
                e2=c
            elif x==b2:
                e2 = min(c,e2)
        if l==3:
            if x>b3:
                b3=x
                e3=c
            elif x==b3:
                e3 = min(c,e3)
    print(b1,e1)
    print(b2,e2)
    print(b3,e3)