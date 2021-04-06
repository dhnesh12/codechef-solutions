# cook your dish here
T = int(input())
for _ in range(T):
    N = int(input())
    arr = [x for x in map(int, input().split())]
    K = int(input())
    a = arr[K-1]
    arr.sort()
    print(arr.index(a)+1)