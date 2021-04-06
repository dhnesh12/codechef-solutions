# cook your dish here
T = int(input())
for _ in range(T):
    n = int(input())
    arr = [x for x in map(int, input().split())]
    arr.sort()
    ls = []
    mid = arr[1] - arr[0]
    for i in range(0, n-1):
        diff = arr[i+1] - arr[i]
        if diff < mid:
            mid = diff
    print(mid)
