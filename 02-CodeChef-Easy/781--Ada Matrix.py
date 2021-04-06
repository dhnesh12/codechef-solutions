# cook your dish here
for _ in range(int(input())):
    n=int(input())
    l = [list(map(int,input().split())) for _ in range(n)]
    b = [False]*n
    for i in range(n):
        if l[0][i]==(i+1):
            b[i]=True
    count=0
    for i in range(n-1,0,-1):
        if b[i]==True:continue
        else:
            count+=1
            for j in range(i,0,-1):
                b[j]=False if b[j] else True
    print(count)
            
