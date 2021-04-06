# cook your dish here
a=int(input())
for i in range(a):
    p,q=map(int,input().split())
    print(max(0,p-q))