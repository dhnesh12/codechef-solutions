# cook your dish here
t=int(input())
for _ in range(t):
    n=int(input())
    a1=[]
    a2=[]
    for i in range((4*n)-1):
        a,b=map(int,input().split())
        a1.append(a)
        
        a2.append(b)
   
    xorsum1=0
    xorsum2=0
    for i in range((4*n)-1):
        
        xorsum1=xorsum1^a1[i]
     
    for i in range((4*n)-1):
        
        xorsum2=xorsum2^a2[i]   
    
        
    print(xorsum1,xorsum2)