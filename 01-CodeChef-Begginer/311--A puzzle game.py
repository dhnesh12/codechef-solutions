# cook your dish here
#required
primes=[2,3,5,7,11,13,17]
e=[(0,1),(1,2),(3,4),(4,5),(6,7),(7,8),(0,3),(1,4),(2,5),(3,6),(4,7),(5,8)]
original=[1,2,3,4,5,6,7,8,9]

def bfs():
    q=[[0,original[:]]]
    ans[tuple(original)]=0
    while(q!=[]):
        for i in e:
            x=q[0][1][:]

            if(x[i[0]]+x[i[1]] in primes):
                x[i[0]],x[i[1]]=x[i[1]],x[i[0]]

                if(tuple(x) not in ans.keys()):
                    ans[tuple(x)]=q[0][0]+1
                    q.append([q[0][0]+1,x[:]])
        q.pop(0)       

ans=dict()
bfs()

for T in range(int(input())):

    input().split() #for blank space

    a=[]
    for i in range(3):a+=list(map(int,input().split()))

    try:print(ans[tuple(a)])
    except:print(-1)
