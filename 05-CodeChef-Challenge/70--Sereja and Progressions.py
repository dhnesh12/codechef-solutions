[n,k,d]=raw_input().split()
n=int(n)
k=int(k)
d=int(d)
arr=[int(i) for i in raw_input().split()]
for i,elem in enumerate(arr):
	arr[i]=arr[i]-(i*2)
l=[i for i in sorted(enumerate(arr),key=lambda x:x[1])]
print 0,2
temp=0
for i in range(0,k):
	print 1,l[i][0]+1,i+1
l=l[::-1]
for i in range(0,d):
	print 2,l[i][0]+1
print "-1"