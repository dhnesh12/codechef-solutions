# cook your dish here
from scipy.spatial import ConvexHull


def polygonArea(X,Y,n): 
  
    area = 0.0
    
    j = n - 1
    for i in range(0,n): 
        area += (X[j] + X[i]) * (Y[j] - Y[i])
        j = i   

    return abs(area / 2.0)
    

if __name__ == "__main__":
    n=int(input())
    points=[]
    pointsind=dict()
    for _ in range(n):
        x,y=map(int,input().split())
        points.append([x,y])
        pointsind[str([x,y])]=(_+1)
    z=input()
    while len(points)>2:
        try:
            hull=ConvexHull(points)
            temp = []
            for element in hull.vertices:
                temp.append(points[element])
            #print(temp)
            total_area=[]  
            for element in temp:
                pts=points.copy()
                pts.remove(element)
                try:
                    hull1=ConvexHull(pts)
                except:
                    total_area.append([float("-inf"),element])
                    break
                temp1=[]
                for each in hull1.vertices:
                    temp1.append(pts[each])
                X=[]
                Y=[]
                for each in temp1:
                    X.append(each[0])
                    Y.append(each[1])
                total_area.append([polygonArea(X,Y,len(X)),element])
            #print(total_area)
            smallest=[]
            small=float("inf")
            for each in total_area:
                if small > each[0]:
                    smallest=[]
                    small=each[0]
                    smallest.append(each[1])
                elif small == each[0]:
                    smallest.append(each[1])
            #print(smallest)
            smallest=list(sorted(smallest,key=lambda x: (x[0],x[1])))
            points.remove(smallest[0])
            print(pointsind[str(smallest[0])],end=" ")
        except:
            break
    #points.reverse()
    while len(points) != 0:
        print(pointsind[str(points.pop())],end=" ")
                
            

