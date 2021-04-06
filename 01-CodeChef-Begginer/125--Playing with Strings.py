# cook your dish here
t = int(input())
for _ in range(t):
    n = int(input())
    s = input()
    r = input()
    countSzero = s.count('1')
    countRzero = r.count('1')
    if countRzero == countSzero:
        print('YES')
    else:
        print('NO')