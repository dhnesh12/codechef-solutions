from math import floor
n=int(input())
num=int(input())
if num%2!=0:
    print("0")
i=floor(n**0.5)
while i>=0:
    if num%(2**i)==0:
        print(i)
        break
    i-=1
