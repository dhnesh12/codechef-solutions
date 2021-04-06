# cook your dish here
test_case = int(input())
for i in range(test_case):
    count = 0
    row, column, moves = map(int, input().split())
    for i in range(row - moves, row + moves + 1):
        for j in range(column - moves, column + moves + 1):
            if (i > 0 and j > 0) and (i < 9 and j < 9):
                count += 1
    print(count)