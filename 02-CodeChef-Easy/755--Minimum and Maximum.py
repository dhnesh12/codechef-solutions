n=int(input())
for i in range(0,n):
    t=int(input())
    k=int(input())
    if k%t==0:
        print(0)
    else:
        if k%t==t-k%t:
            print(2*(k%t)-1)
        else:
            print((2*min((k%t),t-k%t)))
        
    
