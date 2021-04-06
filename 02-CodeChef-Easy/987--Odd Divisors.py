def odd_div(n):
    s=0 
    for i in range(1,n+1,2):
        s+=((n//i)*i)
    return s

for _ in range(int(input())):
    l,r=map(int,input().split())
    print(odd_div(r)-odd_div(l-1))