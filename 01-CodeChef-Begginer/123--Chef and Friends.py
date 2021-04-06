# cook your dish here
t = int(input())
count = 0
for _ in range(t):
    str = input()
    if 'chef'  in str or 'ch'  in str or 'che'  in str or 'hef'  in str or 'he'  in str or 'ef'  in str:
        count +=1
print(count)