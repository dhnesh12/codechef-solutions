for t in range(int(input())):
    n,u,d=map(int,input().split())
    a=[int(i) for i in input().split()]
    jumps,para=0,1
    for i in range(0,n-1):
        if a[i+1]-a[i]<=u and a[i+1]>=a[i]:
            jumps+=1 
        elif a[i]-a[i+1]<=d and a[i]>=a[i+1]:
            jumps+=1 
        elif a[i]-a[i+1]>d and para>0:
            jumps+=1 
            para-=1 
        else:
            break
    print(jumps+1)

