mod = 1000000007
fact = [1]
for i in range(1,5003):
    fact.append((i*fact[i-1])%mod)
inv = []
for j in range(5003):
    nv = pow(fact[j] , mod-2 , mod)
    inv.append(nv)


for j in range(int(input())):
    l = input()
    four = l.count('4')
    seven = l.count('7')
    if (four == 0 or seven == 0 ):
        print(1)
    else:
        ans = (fact[len(l)]*inv[four]*inv[len(l) - four])%mod
        ans = (ans - fact[len(l)-2]*inv[four-1]*inv[len(l)-1-four])%mod
        print (ans%mod)