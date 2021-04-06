# cook your dish here
# cook your dish here
t = int(input())
while t :
    n,k = list( map( int,input().split() ) )
    a = list( map( int,input().split() ) )
    nis = 1
    while k:
        nm = a.count( min(a) )
        if nm >= k:
            for i in range(k):
                nis *= nm - i
            kf = 1
            for i in range(2,k+1):
                kf *= i
            nis /= kf
            break
        else:
            k -= nm
            a = [x for x in a if x != min(a)]
    print(int(nis))
    t -= 1