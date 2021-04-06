# cook your dish here
import math


def get_x(base, string):
    x = 0
    for i in range(len(string)):
        char = string[-(i+1)]
        try:
            value_of_char = int(char)
        except:
            value_of_char = int(9+(ord(char)-64))
        if value_of_char < base:
            x+= math.pow(base,i)*value_of_char
        else:
            return -1
    return int(x)




t = int(input())
for _ in range(t):
    n = int(input())
    original_set = set()
    
    for j in range(n):
        b, string = input().split()
        b = int(b)
        
        set_of_possible_values = set()
        if b != -1:
            X = get_x(b, string)
            if X != -1 and X <= math.pow(10,12):
                set_of_possible_values.add(X)
        
        else:
            for k in range(2, 37):
                X = get_x(k, string)
                if X != -1 and X <= math.pow(10,12):
                    set_of_possible_values.add(X)
        
        if not j:
            original_set = set_of_possible_values
            continue
        else:
            original_set = original_set.intersection(set_of_possible_values)
        
        
    if original_set:
        print(sorted(original_set)[0])
    else:
        print(-1)