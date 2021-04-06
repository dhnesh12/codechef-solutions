# cook your dish here
N = int(input())
stack = []
for n in range(N):
    line = input().strip().split()
    if int(line[0])==-1:
        # do exercise
        if(len(stack)!=0):
            [problems, books, name] = stack.pop()
            print(books, name)
        
    else:
        # add book
        problems = int(line[0])
        if problems==0:
            continue
        if len(stack)!=0 and problems>stack[-1][0]:
            stack[-1][1] += 1
        else:
            stack.append([problems, 0, line[1]])