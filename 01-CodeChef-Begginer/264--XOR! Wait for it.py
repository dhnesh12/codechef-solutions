# cook your dish here
from operator import xor

def calculate_xor(num):
    remainder = num % 4
    if remainder == 0:
        return num
    elif remainder == 1:
        return 1
    elif remainder == 2:
        return num + 1
    elif remainder == 3:
        return 0

def find_xor(left, right):
    return (xor(calculate_xor(left - 1), calculate_xor(right)))

test_case = int(input())
for i in range(test_case):
    left, right = map(int, input().split())
    ans = find_xor(left, right)
    if ans % 2 == 0:
        print('Even')
    else:
        print('Odd')