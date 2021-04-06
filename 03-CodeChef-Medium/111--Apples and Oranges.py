import math

INF = 1e16
eps = 1e-6
apples = []
oranges = []

def f(m):
    res = -1
    a = INF
    b = INF * -1
    c = INF
    d = INF * -1
    for p in apples:
        val = p[1] - m * p[0]
        a = min(a, val)
        b = max(b, val)
    for p in oranges:
        val = p[1] - m * p[0]
        c = min(c, val)
        d = max(d, val)
    if a > d:
        res = a - d
    if c > b:
        res = max(res, c - b)
    if res == -1:
        return res
    else:
        return res / math.sqrt(1 + m * m)

t = int(input())

while t:
    t -= 1
    n = int(input())
    apples = []
    for i in range(n):
        y = []
        num  , num1= input().split()
        num = int(num)
        num1 = int(num1)
        y.append(num)
        y.append(num1)
        apples.append(y)
    m = int(input())
    oranges = []
    for i in range(m):
        y = []
        num  , num1= input().split()
        num = int(num)
        num1 = int(num1)
        y.append(num)
        y.append(num1)
        oranges.append(y)

    res = -1.0
    lo =0 
    hi = INF
    for iter in range(0,500):
        de = (hi-lo)/3
        m1 = lo + de
        m2 = hi - de
        if (f(m1)<f(m2)):
            lo=m1
        else:
            hi = m2
    res = f(lo)

    lo = INF * -1
    hi = 0
    for iter in range(0,500):
        de = (hi - lo) / 3
        m1 = lo + de
        m2 = hi - de
        if f(m1) < f(m2):
            lo = m1
        else:
            hi = m2       
    res = max(res, f(lo))

    if(res<0):
        print("-1")
    else:
        print(res)