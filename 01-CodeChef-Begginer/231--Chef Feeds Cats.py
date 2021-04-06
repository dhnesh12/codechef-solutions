t = int(input())
while t > 0:
    t -= 1
    n, m = map(int,input().split())
    arr = list(map(int,input().split()))
    b = 0
    k = 1
    while b < m:
        if len(set(arr[b:b+n])) != len(arr[b:b+n]):
           k = 0
           break
        b = b+n 
    print("YES" if k == 1 else "NO")