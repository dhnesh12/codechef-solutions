import random as rand
import sys
t,n,h = map(int,input().split())
alpha = ['a','b','c','d','e','f','g','h','i','j','k'
,'l','m','n','o','p','q','r','s','t','u','v','x','y','z']

for _ in range(t):
  for printing in range(n):
    a = ''
    s = a.join(rand.choice(alpha) for i in range(8))
    print(s,flush=True)
  score = int(input())
