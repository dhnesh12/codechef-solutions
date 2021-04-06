# cook your dish here
t = int(input())
for _ in range(t):
    n = int(input())
    a = [int(x) for x in input().split()]    
    a.sort()
    a.reverse()
    p1 = p2 = 0
    if(n==1 or n==2):
        print("first")
    else:
        p1 = a[0]
        p2 = a[1] + a[2]
        for i in range(3, n):
            if(i%2 == 1):
                p1 += a[i]
            else:
                p2 += a[i]
        if(p1 > p2):
            print("first")
        elif(p1 < p2):
            print("second")
        else:
            print("draw")