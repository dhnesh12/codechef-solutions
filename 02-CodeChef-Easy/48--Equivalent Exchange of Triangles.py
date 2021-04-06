# cook your dish here
def answer():
    d=dict()
    v,ans=0,0
    d[v]=-1
    for i in range(n):
        v ^= (1 << (a[i]-1))
        for j in range(30):
            vd=v
            vd ^= (1 << j)
            if(vd in d.keys()):
                ans=max(ans,i-d[vd])

        if(v not in d.keys()):d[v]=i

    return ans//2
                
    
for T in range(int(input())):
    n=int(input())

    a=list(map(int,input().split()))

    print(answer())
