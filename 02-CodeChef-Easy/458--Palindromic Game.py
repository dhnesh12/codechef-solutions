# cook your dish here
from collections import Counter

for _ in range(int(input())):
    s=input()
    p=input()

    s1 = Counter(s)
    p1 = Counter(p)

    s_unique = set(s)-set(p)
    p_unique = set(p)-set(s)
 
    if not s_unique:
        win='B'
 
    elif s_unique and not p_unique:
        win='A'
     
    elif any([s1[i]>1 for i in s_unique]):
        win='A'
    else:
        win='B'

    print(win) 