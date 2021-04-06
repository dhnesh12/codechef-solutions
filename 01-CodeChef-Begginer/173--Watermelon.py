t = int(input())
for _ in range(t):
    n =  int(input())
    a = list(map(int, input().split()))
    s = sum(a)
    
    if s >= 0:
        print('YES')
    else:
        print('NO')