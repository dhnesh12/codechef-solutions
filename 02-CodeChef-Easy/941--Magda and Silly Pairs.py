for _ in range(int(input())):
    n=int(input())
    a=list(map(int,input().split()))
    b=list(map(int,input().split()))
    s=sum(a)+sum(b)
    c1=0
    c2=0
    for i in a:
        if i%2==0:
            c1+=1
    for j in b:
        if j%2==0:
            c2+=1
    s=s-abs(c1-c2)
    print(s//2)