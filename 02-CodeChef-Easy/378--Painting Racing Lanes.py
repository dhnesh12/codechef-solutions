# cook your dish here
t = int(input())
# b for number of bubbles
for i in range(t):
    b = int(input())
    bubble = []
    # looping through each bubble
    for c in range(b):
        # bubble start (s), bubble end (e), paint line (p)
        s, e, l = map(int, input().split())
        bubble.append([l,s,e])
    bubble.sort()
    check = []
    for j in range(b):
        k = j + 1
        while k<b and bubble[k][0] - bubble[j][0] < 2:
            if bubble[k][0] - bubble[j][0] == 1:
                for z in range(bubble[k][1],bubble[k][2]+1):
                    if z>=bubble[j][1] and z<=bubble[j][2]:
                        if z not in check:
                            check.append(z)
            k += 1
    print(500 - len(check))