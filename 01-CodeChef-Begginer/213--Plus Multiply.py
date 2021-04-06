# cook your dish here
for _ in range(int(input())):
    n = int(input())
    num = list(map(int, input().split()))
    a,b=0,0
    a=num.count(2)
    b=num.count(0)
    print(a*(a-1)//2 + b*(b-1)//2)

