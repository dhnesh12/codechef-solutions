# cook your dish here
t=int(input())
while t:
    a,b=map(int,input().split())
    ans=a+b
    n=0
    ds=0
    while a>0 and b>0:
        c=a%10
        d=b%10
        if(c+d)>=10:
            n=n+1
        a=int(a/10)
        b=int(b/10)
    ds=int('1'*n+'0')
    print(ans-ds)
    t=t-1
        
        
    
    