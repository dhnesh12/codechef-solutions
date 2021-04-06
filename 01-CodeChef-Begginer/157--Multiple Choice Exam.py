t=int(input())
while t!=0:
    t-=1
    n=int(input())
    a=input()
    b=input()
    i=s=0
    while i<n:
        if a[i]==b[i]:
            s+=1
        elif b[i]=='N':
            i+=1
            continue
        else:
            i+=1
        i+=1
    print(s)    