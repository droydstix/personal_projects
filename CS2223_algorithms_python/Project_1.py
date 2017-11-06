m=10
n=10
#CIC
def cic(m,n):
    while(true):
        t = min(m,n)
        if(m%t==0 and n%t==0):
            return t
        else:
            t = t-1
print(t)
