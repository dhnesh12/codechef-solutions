# cook your dish here
try:
    t=int(input())
    for i in range(t):
        n,k=map(int,input().split())
        l=list(map(int,input().split()))
        l=sorted(l)
        s=0
        c=0
        for i in range(k,len(l)-k):
            s=s+l[i]
            c=c+1
        print(s/c)
except:
    pass