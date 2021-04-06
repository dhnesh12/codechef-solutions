for _ in range(int(input())):
    n = int(input())
    nums = [int(x) for x in input().split(' ')]
    
    failed = [x for x in nums if x <= 2]
    full = [x for x in nums if x == 5]
    if len(failed) >= 1 or len(full) == 0:
        print("No")
        continue
    
    avg = sum(nums) / n
    if avg >= 4.0:
        print("Yes")
    else:
        print("No")
    