n, m = map(int, input().split())
a = list(map(int, input().split()))
x = 0
for _ in range(m):
    b, c = map(str, input().split())
    if b =="R":   
        print(a[((int(c)+x-1)%n)])
    else:
        if b == "A":
            x -= int(c)
        elif b == "C":
            x += int(c)