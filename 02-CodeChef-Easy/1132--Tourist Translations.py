T,m = input().split(" ")
M = m.upper()
d = {}
d["_"] = " "
for i in range(26):
    d[chr(ord('a') + i)] = m[i]
    d[chr(ord('A') + i)] = M[i]
for _ in range(int(T)):
    s = input()
    res = ""
    for i in s:
        add = d.get(i,i)
        res = res + add
    print(res)
