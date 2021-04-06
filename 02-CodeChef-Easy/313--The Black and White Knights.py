def main():
    t = int(input())
    for i in range(0,t):
        nm = str(input())
        n = int(nm.split(" ")[0])
        m = int(nm.split(" ")[1])
        if (n == 1 or m == 1):
            if (n == 1 and m == 1):
                total = 0
            else:
                greater = n if (n != 1) else m
                total = greater * (greater - 1)
        else:
            total = n*m*(n*m-1)-8*n*m+12*n+12*m-16
        print(total)
    
main()