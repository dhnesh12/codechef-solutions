# cook your dish here
for i in range(int(input())):
    N, M = list(map(int, input().split(' ')))
    C = [list(map(int, input().split(' '))) for _ in range(N)]
    D = [list(map(int, input().split(' '))) for _ in range(N)]

    dp = [[0]*M for _ in range(N)]
    for j in range(M):
        dp[0][j] = C[0][j]

    min_value = min(dp[0])
    for i in range(1, N):
        for j in range(M):
            dp[i][j] = min(min_value + C[i][j],
                           dp[i-1][j] + max(0, C[i][j]-D[i-1][j]))
        min_value = min(dp[i])

    print(min_value)
