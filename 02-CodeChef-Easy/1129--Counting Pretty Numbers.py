# cook your dish here
t=int(input())
for i in range(t):
    a,b= map(int,input().split())
    count=0
    while b>=a:
        b=str(b)
        a=str(a)
        if a[-1]=="2"or a[-1]=="3" or a[-1]=="9":
            count+=1
        a=int(a)
        b=int(b)
        a+=1
    print(count)