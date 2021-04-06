t=int(input())
for i in range(t):
    n=int(input())
    l=list(map(int,input().split()))
    l.sort()
    l=l[::-1]
    s=0
    k=0
    for i in range(n):
        if(i%4==0 or i%4==1):
            s+=l[i]
    print(s)
        
        
        
        