for _ in range(int(input())):
    N=int(input())
    A,Val=[],1
    for _ in range(N):
        A.append(Val) 
        Val+=2
    print(*A)