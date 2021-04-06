from __future__ import division


def S(n):
    f = [1] * (3010)
    for i in xrange(1, 3006, 1):
        f[i] = f[i - 1] * i;
    ed = f[3003]
    en = 0
    for i in xrange(3004):
        en += ed // f[i]

    an = en
    ad = ed
    q = []
    while n > 0:
        if an == 0:
            n = 0
            continue

        an_ad = an // ad
        if an_ad >= 2:
            k = an_ad - 1
            bn, bd = an - k * ad, ad
            q.append((k * n * (n + 1) // 2, 1))
            an, ad = bn, bd
        else:
            m = n * (an - ad) // ad
            bn, bd = an, an - ad
            q.append(((n + m) * (n + m + 1) // 2, -1))
            an, ad = bn, bd
            n = m

    r = 0
    for x, s in reversed(q):
        if s < 0:
            r = -r
        r += x
    return r


def solution(s):
    result = S(long(s))
    return str(result)

def main():
    val = raw_input()
    print(solution(val))

main()
