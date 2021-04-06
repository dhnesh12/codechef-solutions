for _ in range(int(input())):
    n = int(input())
    p = list(map(int, input().split()))
    profit, a = 0, 0
    p = sorted(p, reverse=True)
    for i in p:
        if i - a > 0:
            profit += i - a
            a += 1
        else:
            break
    print(profit % 1000000007)
