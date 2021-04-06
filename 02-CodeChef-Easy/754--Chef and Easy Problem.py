# cook your dish here
n,q=map(int,input().split())
arr=list(map(int,input().split()))
bit=[[0 for i in range(n+1)] for j in range(32)]

for i in range(n):
    for j in range(31):
        bit[j+1][i+1]=bit[j+1][i]
        if arr[i]&(1<<j):
            bit[j+1][i+1]+=1

for i in range(q):
    l,r=map(int,input().split())
    out=0
    for j in range(1,32):
        if (r-l+1)%2:
            if bit[j][r]-bit[j][l-1]<=(r-l+1)//2:
                out+=1<<(j-1)
        else:
            if bit[j][r]-bit[j][l-1]<(r-l+1)//2:
                out+=1<<(j-1)
    print(out)