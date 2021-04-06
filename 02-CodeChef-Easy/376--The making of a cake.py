t=int(input())
while t:
    t-=1
    n,d=map(int,input().split())
    a=input()
    b=input()
    zz={}
    for i in range(97,123):
        zz[chr(i)]=[]
    for i in range(len(a)):
        zz[a[i]].append(i+1)
    z=[]
    for i in range(97,123):
        z.append(zz[chr(i)])
    #print(z)
    for i in range(len(b)):
        value=ord(b[i])-97
        m=1
        for j in range(len(z[value])):
            if (abs(z[value][j]-i-1))%d==0:
                m=0
                z[value].pop(j)
                break
        if m==1:
            break
    if m==1:
        print("No")
    else:
        print("Yes")
    
                       
