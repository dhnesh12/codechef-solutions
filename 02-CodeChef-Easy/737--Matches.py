for _ in range(int(input())):
    m,n=map(int,input().split())
    m,n=max(m,n),min(m,n)
    c=0
    while m%n!=0 and m//n==1:
        c+=1
        m,n=n,m%n
    if c%2==0:
        print('Ari')
    else:
        print('Rich')