# cook your code here
n = int(raw_input())
a = raw_input().split(' ')
v = [0] * n
t = [0] * n
count = 0
while n > 0:
    p = a[n - 1]
    i = n - 1
    while a[i] == p:
        v[count] = i + 1
        t[count] = 1
        i -= 1
        if i == -1:
            break
    if a[n - 1] != a[n - 2]:
        for J in range(2, min(n, 43)):
            k = 1
            j = J
            while n - j > 0 and a[n - j - 1] == p:
                v[count] = n - j
                t[count] = J
                a.pop(n - j -1)
                j += J
                k += 1
            if k != 1 or n - j < 0:
                break
    if t[count] == 1:
        n = i + 1
    else:
        n -= k
    count += 1
print count
for i in range(count):
    print v[i], t[i] 