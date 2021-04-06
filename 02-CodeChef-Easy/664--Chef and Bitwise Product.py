def func(x,y,z):
    return (x&z)*(y&z) 
def recursion(lo,ans):
    global l,r
    if lo&(lo-1)==0:
        x=lo|ans 
        return x  
    else:
        y=recursion(lo&(lo-1),ans)
        if y>=l :
            return y   
        return lo|ans
for _ in range(int(input())):
    x,y,l,r=map(int,input().strip().split(' '))
    q=x|y  
    if x==0 or y==0:
        print(l)
    
    elif q>=l and q<=r:
        print(q) 
    else:
        maxx=func(x,y,r) 
        ans=r
        z=r  
        while z:
            temp=z-1  
            if temp<l:
                break 
            if func(x,y,temp)>=maxx:
                maxx=func(x,y,temp)
                ans=temp 
            z=z&(z-1)   
        if func(x,y,l)>=maxx:
            maxx=func(x,y,l)
            ans=l 
        
        s=ans&q
        if s>=l:
            print(s)
        else:
            x=recursion(l,s)
            print(x)