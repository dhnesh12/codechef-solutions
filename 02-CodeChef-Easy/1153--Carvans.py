# cook your dish here
T=int(input())
for _ in range(T):
    n=int(input())
    lst=list(map(int,input().split()))
    cnt=1
    for i in range(n-1):
        if(lst[i]>=lst[i+1]):
            cnt+=1
        else:
            lst[i+1]=lst[i]
    print(cnt)