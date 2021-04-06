for _ in range(int(input())):
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))

    s, m = sum(arr), max(arr)

    if s % k != 0:  print("NO")
    else:
        if m > s // k:  print("NO")
        else:  print("YES")