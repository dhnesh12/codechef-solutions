# cook your dish here

def result(str):
    k=len(str)
    a=1
    for j in range(1,k):
        if(str[j]>=str[j-1]):
            a+=ord(str[j])-ord(str[j-1])
        else:
            a+=(26-(ord(str[j-1])-ord(str[j])))

    if(a>(10*k)):
        return "NO"
    else:
        return "YES"



def main():
    for t in range(int(input())):
        str=input()
        print(result(str))

def test():
    inputs = ["helloworld", "mississippi"]
    for input in inputs:
        print(result(input))
if __name__ == '__main__':
    main()
    # test()
