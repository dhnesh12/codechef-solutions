# cook your dish here
for _ in range(int(input())):
    n=int(input())
    s=input()
    x=0
    y=0
    k=0
    for i in s:
        if i=='L' and k!='R' and k!='L':
            x=x-1
        if i=='R' and k!='R' and k!='L':
            x=x+1
        if i=='U' and k!='U' and k!='D':
            y=y+1
        if i=='D' and k!='U' and k!='D':
            y = y - 1
        k=i
    print(x,y)