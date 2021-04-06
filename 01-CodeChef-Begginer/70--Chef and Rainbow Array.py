# cook your dish here
n=int(input())
for i in range(n):
    x=int(input())
    l = list(map(int,input().split()))
    z = max(l)
    if z>7:
        print("no")
    elif(l.count(1)>=1 and l.count(2)>=1 and l.count(3)>=1 and l.count(4)>=1 and l.count(5)>=1 and  l.count(6)>=1 and
    l.count(7)>=1):
        if(l==l[::-1]):
            print('yes')
        else:
            print('no')
    else:
        print('no')
    