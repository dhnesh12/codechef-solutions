import math,sys,bisect,heapq
from collections import defaultdict,Counter,deque
from itertools import groupby,accumulate
from functools import lru_cache
#sys.setrecursionlimit(200000000)
int1 = lambda x: int(x) - 1
#def input(): return sys.stdin.readline().strip()
input = iter(sys.stdin.buffer.read().decode().splitlines()).__next__
aj = lambda: list(map(int, input().split()))
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
#MOD = 1000000000 + 7
def Y(c):  print(["NO","YES"][c])
def y(c):  print(["no","yes"][c])
def Yy(c):  print(["No","Yes"][c])
    
for _ in range(int(input())):
    n,m = aj()
    A = []
    for i in range(n):
        s = input()
        A.append(s)
    dp = [[0]*m for i in range(n)]
    dp[n-1][m-1] = 1
    for i in range(n-1,-1,-1):
        for j in range(m-1,-1,-1):
            if A[i][j] != '#':
                if i > 0 and A[i-1][j] != '#':
                    dp[i-1][j] = dp[i][j] or dp[i-1][j]
                if j > 0 and A[i][j-1] != '#':
                    dp[i][j-1] = dp[i][j-1] or dp[i][j]
                    
    ans = [A[0][0]]
    que = set([(0,0)])
    for steps in range(n+m-2):
        v = set()
        ch = 'z'
        for i,j in que:
            if i < n-1 and dp[i+1][j]:
                ch = min(ch,A[i+1][j])
                v.add((A[i+1][j],(i+1,j)))
            if j < m-1 and dp[i][j+1]:
                ch = min(ch,A[i][j+1])
                v.add((A[i][j+1],(i,j+1)))
        que = set()
        for c,loc in v:
            if c == ch:
                que.add(loc)
        ans.append(ch)
    print("".join(ans))
            
            