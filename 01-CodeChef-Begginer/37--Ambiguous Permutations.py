# cook your dish here
while True: 
    n=int(input()) 
    if not n:
        break 
    l=[int(x) for x in input().split()]  
    l1=list(range(1,n+1))  
    flag=0  
    for i in range(n):
        if l[i]!=l1[i]:
            m=l[i] 
            if l[m-1]!=l1[i]:
                flag=1 
                break 
    if flag: 
        print("not ambiguous") 
    else:
        print("ambiguous")
        
    