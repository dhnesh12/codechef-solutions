from numpy import *
if __name__=='__main__':
  for _ in range(int(input())):
    k=int(input())
    c=1
    a=array([['O','X','X','X','X','X','X','X'],
         ['X','X','X','X','X','X','X','X'],
         ['X','X','X','X','X','X','X','X'],
         ['X','X','X','X','X','X','X','X'],
         ['X','X','X','X','X','X','X','X'],
         ['X','X','X','X','X','X','X','X'],
         ['X','X','X','X','X','X','X','X'],
         ['X','X','X','X','X','X','X','X']])
    for i in range(8):
      for j in range(8):
        if i==0 and j==0:
          continue
        else:
          if c<k:
            a[i][j]='.'
            c=c+1
    for i in range(8):
      for j in range(8):
        print(a[i][j],end="")
      print()
  