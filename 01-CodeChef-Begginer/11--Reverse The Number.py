# cook your dish here
t=int(input())
while(t):
    n=int(input())
    rev=0
    while(n):
        rev=rev*10+n%10
        n=int(n/10)
    print(rev)
    t-=1