def bfs(start,G,N):
    s = [start]
    A = [1 for i in range(N)]
    visited = [False for i in range(N)]
    while(len(s)>0):
        x = s.pop()
        visited[x]=True
        for i in G[x]:
            if(not visited[i]):
                if(A[x]==1):
                    A[i] = 2
                else:
                    A[i] = 1
                s.append(i)
    return A

T = int(input())
ans = []

for _ in range(T):
    N = int(input())

    G = {}
    for i in range(N-1):
        u,v = [int(i)-1 for i in input().split()]
        if(u in G):
            G[u].append(v)
        else:
            G[u] = [v]
        if(v in G):
            G[v].append(u)
        else:
            G[v] = [u]
    t = bfs(0,G,N)
    s = ''
    for i in t:
        s += str(i) + ' '
    ans.append(s.strip())

for i in ans:
    print(i)
