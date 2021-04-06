for _ in range(int(input())):
    A,B=map(int,input().split())
    if A-2==B or A+2==B:
        print("YES")
    elif A%2==0 and A-1==B:
        print("YES")
    elif A%2==1 and A+1==B:
        print("YES")
    else:
        print("NO")
        
        