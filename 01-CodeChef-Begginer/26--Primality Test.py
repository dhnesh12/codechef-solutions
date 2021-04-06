t = int(input())
for item in range(t):
    n = int(input())
    c = 0
    if n == 1:
        print("no")
        continue
    else:
        i = 2
        while i*i <= n:
            if n % i == 0:
                print("no")
                c = 1
                break
            i += 1
    if c == 1:
        continue
    print("yes")