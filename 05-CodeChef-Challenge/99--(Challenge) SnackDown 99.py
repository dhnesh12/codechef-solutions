N, M = [int(x) for x in input().split()]
S = [int(x) for x in input().split()]
W = [int(x) for x in input().split()]
for i in range(M):
    src, des = [int(x) for x in input().split()]
for i in range(len(W)):
    W[i] = [W[i], i]
W.sort(reverse=True)
for i in range(len(W)-1):
    print(i+1)
    [int(x) for x in input().split()]
    ele, index = W.pop()
print(-1)
ans = ""
for i in range(N):
    if i%2:
        ans +="G"
    else:
        ans += "C"
print(ans)