# cook your dish here
t=int(input())
for i in range(t):
    a=set(input())
    b=set(input())
    c=a.intersection(b)
    if len(c)==0:
        print("No")
    elif len(c)>0:
        print("Yes")