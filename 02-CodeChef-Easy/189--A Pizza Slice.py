import math
def solve1(n, x, y, z):
	q = 2 * n + 1
	if((y - x) * (z - y) > 0):
	    p = q - z
	else:
		p = x
	return(p, q)
def solve2(n, x, y, z):
	q = 2 * n + 1
	if((y - x) * (z - y) > 0):
		p = q - 2 * y
	else:
		p = 0
	return(p, q)
def solve3(n, x, y, z):
	q = 2 * n + 1
	if(y > x and z > y):
		if(x == 0):
			p = q
		else:
			p = z + q - 2 * y
	if(y > x and z < y):
		p = y - 1
	if(y < x and z < y):
		p = q - x
	if(y < x and z > y):
		p = z
	return(p, q)
def solve4(n, x, y, z):
	q = 2 * n + 1
	if((y - x) * (z - y) < 0):
		p = 0
	else:
		p = q - x - z
	return(p, q)
T = int(input())
for t in range(0, T):
	n, t, x, y, z = map(int, input().split())
	if(t == 1):
		p, q = solve1(n, x, y, z)
	if(t == 2):
		p, q = solve2(n, x, y, z)
	if(t == 3):
		p, q = solve3(n, x, y, z)
	if(t == 4):
		p, q = solve4(n, x, y, z)
	if(int(p)):
		print(int(p / math.gcd(p, q)), int(q / math.gcd(p, q)))
	else:
		print(int(p), int(q))