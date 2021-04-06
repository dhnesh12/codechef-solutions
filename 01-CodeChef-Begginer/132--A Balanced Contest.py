for _ in range(int(input())):
    n,p=map(int,input().split())
    a=list(map(int,input().split()))
    h=0
    c=0
    for i in range(n):
        if a[i]>=p//2:
            c=c+1
        elif a[i]<=p//10:
            h=h+1
    if h==2 and c==1:
        print("yes")
    else:
        print("no")