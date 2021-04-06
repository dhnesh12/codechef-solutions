for i in range(int(input())):
    (m,n)=map(int,input().split())
    if(m>n):
        print(">")
    elif(m<n):
        print("<")
    else:
        print("=")