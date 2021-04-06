# cook your dish here
def find_sum(elements):
    total = 0
    while(elements > 0):
        total += int(elements % 10)
        elements = int(elements / 10)
    return total

test_case = int(input())
for i in range(test_case):
    size_of_list = int(input())
    count_1 = 0
    count_2 = 0
    for j in range(size_of_list):
        chef, morthy = map(int, input().split())
        chef_total = find_sum(chef)
        morthy_total = find_sum(morthy)
        if chef_total > morthy_total:
            count_1 += 1
        elif chef_total == morthy_total:
            count_1 += 1
            count_2 += 1
        else:
            count_2 += 1
    if count_1 > count_2:
        print(0, count_1)
    elif count_1 < count_2:
        print(1, count_2)
    else:
        print(2, count_1)