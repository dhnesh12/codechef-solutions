
n, m, k = map(int, input().split())
A = list(map(int, input().split()))
P = list(map(int, input().split()))

for i in range(n):
    A[i] += k

print(*A)
