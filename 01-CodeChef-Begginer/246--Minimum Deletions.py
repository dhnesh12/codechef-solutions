def gcd(a,b):
  while(b):
    a,b = b,a%b
  return a  
for _ in range(int(input())):
    n = int(input())
    ar = sorted(list(map(int, input().split())))
    t = gcd(ar[0],ar[1])
    if(t==1):
        print(0)
    else:
        print(-1)