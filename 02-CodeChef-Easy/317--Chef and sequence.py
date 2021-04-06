def main():
    n, k = map(int, input().split())
    a = [int(i) for i in input().split()]
    w_a = float('inf')
    w_d = float('inf')

    for i in range(0, k+1):
        for j in range(n-1, n-2-k+i, -1):
            L = i
            R = j
            D = int((a[R]-a[L])/(R-L))
            a_0 = a[L] - (D*L)
            chg = 0
            # check if this is a valid solution by counting # of changes needed
            for l in range(0, n):
                if(a[l] != a_0 + (D*l)):
                    chg+=1
            #if # of changes is <= k, check if its better
            if(chg <= k):
                if(a_0 < w_a or (a_0 == w_a and D < w_d)):
                    w_a = int(a_0)
                    w_d = int(D)
    
    # print ans
    for i in range(n):
        a[i] = str(w_a+(i*w_d))
    print(" ".join(a)) 
            

main()
