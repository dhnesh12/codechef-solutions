from itertools import combinations
T = int(input())
while T != 0:
	N = int(input())
	points = []
	for i in range(N):
		x,y = map(int,input().strip().split())
		points.append([x,y])
	kill = 0
	total = (N*(N-1)*(N-2)*(N-3))/6
	comb = combinations(points,3)
	for x in list(comb):
		[x1,y1] = x[0]
		[x2,y2] = x[1]
		[x3,y3] = x[2]
		area = (x1 - x2)*(y2 - y3) - (y1 - y2)*(x2 - x3)
		if area == 0:
			continue
		x12 = x1 - x2
		x13 = x1 - x3
		y12 = y1 - y2
		y13 = y1 - y3
		y31 = y3 - y1
		y21 = y2 - y1
		x31 = x3 - x1
		x21 = x2 - x1
		sx13 = pow(x1, 2) - pow(x3, 2)
		sy13 = pow(y1, 2) - pow(y3, 2)
		sx21 = pow(x2, 2) - pow(x1, 2)
		sy21 = pow(y2, 2) - pow(y1, 2)
		f = (((sx13) * (x12) + (sy13) * (x12) + (sx21) * (x13) + (sy21) * (x13)) / (2 * ((y31) * (x12) - (y21) * (x13))))
		g = (((sx13) * (y12) + (sy13) * (y12) + (sx21) * (y13) + (sy21) * (y13)) / (2 * ((x31) * (y12) - (x21) * (y13))))
		c = (-pow(x1, 2) - pow(y1, 2) - 2 * g * x1 - 2 * f * y1)
		for i in points:
			if i in x:
				continue
			else:
				if (pow(i[0],2) + pow(i[1],2) + 2*g*i[0] + 2*f*i[1] + c) <= 0.000001:
					kill = kill+1
	prob = kill/total
	print(prob)
	T = T-1