# cook your dish here
t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    m = 0

    for i in range(1, k + 1):
        if n % i > m:
            m = n % i

    print(m)