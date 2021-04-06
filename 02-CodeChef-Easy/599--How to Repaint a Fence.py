# Link: https://www.codechef.com/COOK56/problems/STRBIT

def repaintFence():
    n, k = map(int, input().split())
    s = str(input())
    prefix = [0] * (n+1)
    ans = 0
    for i in range(n):
        j = i - 1 if i-1 >= 0 else 0
        prefix[i] += prefix[j]
        # print("pre ", prefix)
        if s[i] == "R" and prefix[i] % 2 == 0:
            # print(s[i], i)
            ans += 1
            prefix[i] += 1
            right = i + k if i+k <=n else n
            prefix[right] -= 1
        elif s[i] == "G" and prefix[i] % 2:
            # print(s[i], i)
            ans += 1
            prefix[i] += 1
            right = i + k if i+k <=n else n
            prefix[right] -= 1
    print(ans)



t = int(input())
for _ in range(t):
    repaintFence()
# cook your dish here
