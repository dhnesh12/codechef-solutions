for _ in range(int(input())):
    n=int(input())
    count=n*n
    for i in range(3,n+1,2):
        count+=(n-i+1)**2
    print(count)
    