test_case = int(input())
for i in range(test_case):
    num_1, num_2, raise_to_power = map(int, input().split())
    if raise_to_power % 2 == 0:
        if abs(num_1) > abs(num_2):
            print(1)
        elif abs(num_1) < abs(num_2):
            print(2)
        else:
            print(0)
    else:
        if num_1 == num_2:
            print(0)
        elif num_1 > num_2:
            print(1)
        elif num_1 < num_2:
            print(2)  