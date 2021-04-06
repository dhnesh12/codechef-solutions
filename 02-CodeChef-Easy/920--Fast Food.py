t=int(input())
for j in range(t):
    n=int(input())
    a=list(map(int,input().split()))
    b=list(map(int,input().split()))
    prefixa=[0]*n
    prefixb=[0]*n
    prefixa[0]=a[0]
    for i in range(1,n):
        prefixa[i]=prefixa[i-1]+a[i]
    prefixb[n-1]=b[n-1]    
    for i in range(n-2,-1,-1):
        prefixb[i]=prefixb[i+1]+b[i]
    maxi=0    
    for i in range(n+1):
        if i==0:
            temp=prefixb[0]
        elif i==n:
            temp=prefixa[n-1]
        else:
            temp=prefixa[i-1]+prefixb[i]
        if temp>maxi:
            maxi=temp
    print(maxi)        
            