# cook your dish here
for _ in range(int(input())):
    n, k = map(int, input().split())
    m = (n+k) // 2
    a = sorted(list(map(int, input().split())))
    print(a[m])