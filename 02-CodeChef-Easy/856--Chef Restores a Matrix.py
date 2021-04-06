def solve(A,N,M):
    for i in range(N):
        for j in range(M):
            # print(i,j)
            if(A[i][j]!=-1 and ( (i>0 and A[i-1][j]>A[i][j]) or (j>0 and A[i][j-1]>A[i][j]))):
                return -1
            elif(A[i][j]==-1):
                t = 1
                if(i>0):
                    t = max(t,A[i-1][j])
                if(j>0):
                    t = max(t,A[i][j-1])
                A[i][j] = t
    return A

T = int(input())
ans = []

for _ in range(T):
    N,M = [int(i) for i in input().split()]
    A = []
    for i in range(N):
        a = [int(i) for i in input().split()]
        A.append(a)

    x = solve(A,N,M)
    if(x==-1):
        ans.append(-1)
    else:
        s = ''
        for i in range(N):
            for j in range(M):
                s += str(A[i][j]) + ' '
            s += '\n'
        ans.append(s[:-1])

for i in ans:
    print(i)
