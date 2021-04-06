def rearrangeCartons(positionArray):
    swaps = 0
    for i in range(1, len(positionArray)):
        for j in range(i):
            if positionArray[i] < positionArray[j]:
                swaps += 1
                t = positionArray[i]
                positionArray[i] = positionArray[j]
                positionArray[j] = t
    return swaps
n=int(input())

A = [int(x) for x in input().split()]
B = [int(x) for x in input().split()]

positionArray = []

for i in range(n):
    x = B.index(A[i])
    positionArray.append(x)
print(rearrangeCartons(positionArray))

