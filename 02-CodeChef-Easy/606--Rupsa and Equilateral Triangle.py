import math as m
try:
    t=int(input())
    while(t!=0):
        x=int(input())
        v=0
  
    
        def ma():
            for i in range(1,x):
                v= ((x**2)-(i**2))
                z=(float(str(m.sqrt(v)).split('.')[0]+'.'+str(m.sqrt(v)).split('.')[1][0]))**2
                if(v==z):
                    #print(2*m.sqrt((x**2)-(i**2)))
                    return ('YES')
            return ('NO')
        
        print(ma())
        t-=1
except EOFError as e:
    pass