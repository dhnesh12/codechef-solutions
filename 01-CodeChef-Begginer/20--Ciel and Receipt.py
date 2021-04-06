t=int(input())
for kk in range(t):
    a=[]
    for i in range(0,12):
        a.append(2**i)
    a=a[::-1]
    p=int(input())
    c=0
    z=0
    n=p
    for i in range(len(a)):
        if(n>=a[i]):
            x=int(n/a[i])
            c=c+x
            n=n-int(a[i]*x)
        if(n==0):
            break
    print(c)
            