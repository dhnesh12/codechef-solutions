import math,string,itertools,fractions,heapq,collections,re,array,bisect,sys,copy,functools
import random

sys.setrecursionlimit(10**7)
inf = 10**20
eps = 1.0 / 10**10
mod = 10**9+7
dd = [(-1,0),(0,1),(1,0),(0,-1)]
ddn = [(-1,0),(-1,1),(0,1),(1,1),(1,0),(1,-1),(0,-1),(-1,-1)]

def LI(): return list(map(int, sys.stdin.readline().split()))
def LLI(): return [list(map(int, l.split())) for l in sys.stdin.readlines()]
def LI_(): return [int(x)-1 for x in sys.stdin.readline().split()]
def LF(): return [float(x) for x in sys.stdin.readline().split()]
def LS(): return sys.stdin.readline().split()
def I(): return int(sys.stdin.readline())
def F(): return float(sys.stdin.readline())
def S(): return input()
def pf(s): return print(s, flush=True)
def pe(s): return print(str(s), file=sys.stderr)


def main():
    t = I()

    rr = []

    for ti in range(t):
        n = I()
        a = LI()
        m = max(a)
        c = [0] * (m+1)
        for b in a:
            c[b] += 1

        if c[0] < 1:
            rr.append('No')
            continue

        r = [0]
        c[0] -= 1
        rf = 1
        while m > 0:
            f = 1
            if c[0] > 0:
                for k in range(m-1,0,-1):
                    if c[k] < 2:
                        f = 0
                        break
                if f:
                    for k in range(m-1,0,-1):
                        c[k] -= 2
                    l = list(range(1,m))
                    rp = None
                    if r[-1] != 0:
                        rp = r[-1]
                        r = r[:-1]
                    if len(l) > 0:
                        r.append(l)
                    if c[m] > 1:
                        r.append([m,m])
                        c[m] -= 2
                    else:
                        r.append(m)
                        c[m] -= 1
                    if len(l) > 0:
                        r.append(l[::-1])
                    r.append(0)
                    if rp:
                        r.append(rp)
                    c[0] -= 1
            else:
                f = 0

            if not f:
                f = 1
                for k in range(m,0,-1):
                    if c[k] < 1:
                        rf = 0
                        break
                    c[k] -= 1
                if not rf:
                    break
                if r[0] == 0:
                    r = [list(range(m,0,-1))] + r
                elif r[-1] == 0:
                    r.append(list(range(1,m+1)))
                else:
                    rf = 0
                    break

            if not rf:
                break

            while m > 0 and c[m] < 1:
                m -= 1

        if sum(c[1:]) > 0 or not rf:
            rr.append('No')
        else:
            if c[0] > 0:
                for i in range(len(r)):
                    if r[i] == 0:
                        r[i] = [0] * (c[0] + 1)
                        break
            for i in range(len(r)):
                if isinstance(r[i], list):
                    r[i] = ' '.join(map(str, r[i]))
            rr.append('Yes\n{}'.format(' '.join(map(str, r))))

    return '\n'.join(rr)


print(main())
