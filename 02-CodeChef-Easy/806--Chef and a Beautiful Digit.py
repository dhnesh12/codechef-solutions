# cook your dish here
t = int(input())
while t:
    N,d = input().split()
    N = list(N)
    
    minz = N.index(min(N))
    p = [min(N[minz],d)]
    count = minz
    for i in range(minz+1,len(N)):
        while N[i] < p[-1]:
            count+=1
            p.pop()
        if N[i]<d:
            p.append(N[i])
        else:
            count+=1
    
    x = ''.join(p) + count*d
    print(x)
    t-=1