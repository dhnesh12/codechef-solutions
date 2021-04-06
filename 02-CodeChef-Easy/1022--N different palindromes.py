t=int(input())
s="abc"
for i in range(t):
    n=int(input())
    if n==0:
        print("-1")
    string=s*(n//3)+s[:n%3]
    print(string)
    

