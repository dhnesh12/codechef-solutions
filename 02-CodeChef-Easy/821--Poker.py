# cook your dish here
test=int(input())
for _ in range(test):
  a=[j for j in input().split(" ")]
  a.sort()
  if a[0][1] == a [1][1] == a[2][1] == a[3][1] == a[4][1]:
    if a[0][0] == "A" and a[1][0] == "J" and a[2][0] == "K" and a[3][0] == "Q" and a[4][0] == "T":
      print("royal flush")
    elif (a[0][0] == "9" and a[1][0] == "J" and a[2][0] == "K" and a[3][0] == "Q" and a[4][0] == "T") or (a[0][0] == "8" and a[1][0] == "9" and a[2][0] == "J" and a[3][0] == "Q" and a[4][0] == "T") or (a[0][0] == "7" and a[1][0] == "8" and a[2][0] == "9" and a[3][0] == "J" and a[4][0] == "T") or (a[0][0] == "6" and a[1][0] == "7" and a[2][0] == "8" and a[3][0] == "9" and a[4][0] == "T") or (a[0][0] == "2" and a[1][0] == "3" and a[2][0] == "4" and a[3][0] == "5" and a[4][0] == "A") or (ord(a[4][0]) - ord(a[3][0]) == ord(a[3][0]) - ord(a[2][0]) == ord(a[2][0]) - ord(a[1][0]) and ord(a[1][0]) - ord(a[0][0]) == 1):
      print("straight flush")
    else:
      print("flush")
  elif (a[0][0] == a[1][0] == a[2][0] == a[3][0]) or (a[1][0]== a[2][0] == a[3][0] == a[4][0]):
    print("four of a kind")
  elif (a[0][0] == a[1][0] == a[2][0] and a[3][0] == a[4][0]) or (a[0][0] == a[1][0] and  a[2][0] == a[3][0] == a[4][0]):
    print("full house")
  elif (a[0][0] == "9" and a[1][0] == "J" and a[2][0] == "K" and a[3][0] == "Q" and a[4][0] == "T") or (a[0][0] == "8" and a[1][0] == "9" and a[2][0] == "J" and a[3][0] == "Q" and a[4][0] == "T") or (a[0][0] == "7" and a[1][0] == "8" and a[2][0] == "9" and a[3][0] == "J" and a[4][0] == "T") or (a[0][0] == "6" and a[1][0] == "7" and a[2][0] == "8" and a[3][0] == "9" and a[4][0] == "T") or (a[0][0] == "2" and a[1][0] == "3" and a[2][0] == "4" and a[3][0] == "5" and a[4][0] == "A") or (ord(a[4][0]) - ord(a[3][0]) == ord(a[3][0]) - ord(a[2][0]) == ord(a[2][0]) - ord(a[1][0]) and ord(a[1][0]) - ord(a[0][0]) == 1):
    print("straight")
  elif (a[0][0] == a[1][0] == a[2][0]) or (a[1][0] == a[2][0] == a[3][0]) or (a[2][0] == a[3][0] == a[4][0]) or (a[3][0] == a[4][0] == a[5][0]):
    print("three of a kind")
  elif (a[0][0] == a[1][0] and a[2][0] == a[3][0]) or (a[0][0] == a[1][0] and a[3][0] == a[4][0]) or (a[2][0] == a[3][0] and a[4][0] == a[5][0]):
    print("two pairs")
  elif a[0][0] == a[1][0] or a[1][0] == a[2][0] or a[2][0] == a[3][0] or a[3][0] == a[4][0]:
    print("pair")
  else:
    print("high card")