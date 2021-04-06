n=int(input())
arr=[]
for i in range(1,n+1):
    arr.append(i)
if(n%2==0):
    d=arr[:n//2]
    v=arr[n//2:]
    for i in range(1,len(d)):
        print(d[i],end=" ")
    print(d[0],end=" ")
    for i in range(1,len(v)):
        print(v[i],end=" ")
    print(v[0])
    
        
    
else:
    c=(n-1)//2
    d=arr[:c]
    v=arr[c:]
    for i in range(1,len(d)):
        print(d[i],end=" ")
    print(d[0],end=" ")
    for i in range(1,len(v)):
        print(v[i],end=" ")
    print(v[0])
    
print(n,end=" ")
for i in range(1,n):
    print(i,end=" ")
print("  ")
    
