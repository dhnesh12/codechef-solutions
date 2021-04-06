# cook your dish here
try:
    n,x,y=[int(i) for i in input().split(' ')]
    a=[int(i) for i in input().split(' ')]
    b=[int(i) for i in input().split(' ')]
    di=dict(zip(a,b))
    fi=dict(zip(b,a))
    c=0
    
    
    if(x<=y):
        a.sort()
        c+=sum(a[-x:])
        for i in range(n):
            if(n-i>x):
                c+=di[a[i]]
    elif(y<x):
        b.sort()
        c+=sum(b[-y:])
        for i in range(n):
            if(n-i>y):
                c+=fi[b[i]]
    
    print(c)
except EOFError:
    pass