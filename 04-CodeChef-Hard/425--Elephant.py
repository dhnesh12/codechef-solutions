a = input().split()
initial = []
for z in range(int(a[0])):
    b = int(input())
    initial.append(b)
for z in range(int(a[2])):
    b = input().split()
    c = [int(i) for i in b]
    del initial[c[0]]
    initial.insert(c[0], c[1])
    rem = []    
    cop = initial.copy()
    cop.sort()
    for i in cop[1:-1]:
        if i <= cop[0] + int(a[1]) or i >= cop[-1] - int(a[1]):
            rem.append(i)
    for i in rem:
        cop.remove(i)
    if cop[-1] <= cop[0] + int(a[1]):
        cop.pop(-1)
    print(len(cop))
