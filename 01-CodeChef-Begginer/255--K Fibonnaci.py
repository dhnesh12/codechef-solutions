n,k = list(map(int,input().split()))
a=[]
for i in range(0,n):
    if i < k:
        item=1
    else:
        item=sum(a[i-k:])
        item%=1000000007
    a.append(item)
    #print(item)
print(a[n-1])
