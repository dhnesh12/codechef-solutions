t=int(input())
while t:
    t-=1
    l,r=map(int,input().split())
    b=[]
    for i in range(l):
        a=input()
        a=list(a)
        #print(b)
        b.append(a)
        #print(a)
    c=[]
    d=[]
    for i in range(l):
        e=[]
        f=[]
        for j in range(r):
            if b[i][j]=='^':
                if j==0:
                    e.append(1)
                else:
                    cc=e[j-1]+1
                    e.append(cc)
            elif b[i][j]=='#':
                e.append(0)
            if b[i][j]=='^':
                if i==0:
                    f.append(1)
                else:
                    f.append(d[i-1][j]+1)
            elif b[i][j]=='#':
                f.append(0)
        c.append(e)
        d.append(f)
    #jdfkd
    #print(c)
    #print(d)
    ans=0
    for i in range(2,l-2):
        for j in range(2,r-2):
            z=1
            if c[i][j]<=2:
                z=0
                #print("a")
            if d[i][j]<=2:
                z=0
                #print("v")
            if c[i][j+2]!=c[i][j]+2:
                z=0
                #print("c")
            if d[i+2][j]!=d[i][j]+2:
                z=0
                #print("d")
            #print(z)
            if z==1:
                ans+=1
    print(ans)
                
    
    
    
    
    
        
            
