
def solve(N, ids):
    # print(N, ids)

    mx = max(j for i in range(N) for j in ids[i])
    memo = [[-1] * (mx+1) for _ in range(1 << N)]

    def dp(people_mask, id_):
        if people_mask == (1 << N) - 1:
            return 1
        if id_ > mx:
            return 0
        if memo[people_mask][id_] != -1:
            return memo[people_mask][id_]

        ans = 0
        for bit in range(N):
            if not (people_mask & (1 << bit)):
                if id_ in ids[bit]:
                    ans += dp(people_mask | (1 << bit), id_ + 1)
        ans += dp(people_mask, id_ + 1)
        
        ans = ans % 1000000007
        memo[people_mask][id_] = ans
        return ans

    ans = dp(0, 1)
    return ans

t = int(input())
for _ in range(t):
    N = int(input())
    ids = []
    for __ in range(N):
        ids.append(set(map(int, input().split())))
    print(solve(N, ids))