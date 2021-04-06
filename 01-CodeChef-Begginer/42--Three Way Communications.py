# cook your dish here
t=int(input())
for i in range(t):
    n=int(input())
    x1,y1=map(int,input().split())
    x2,y2=map(int,input().split())
    x3,y3=map(int,input().split())
    r1=((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))**0.5
    r2=((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3))**0.5
    r3=((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3))**0.5
    if n>=r1 and n>=r2:
        print("yes")
    elif n>=r1 and n>=r3:
        print("yes")
    elif n>=r2 and n>=r3:
        print("yes")
    else:
        print("no")
        