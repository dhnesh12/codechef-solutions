for _ in range(int(input())):
  N=int(input())
  W = list(map(int,input().split()))

  V=W[0]
  for i in range(1,len(W)):
    if V >= W[i]+i:
      pass
    else:
      V=W[i]+i
      
  print(V)