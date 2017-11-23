## Project 2
## Guillermo Rivera
import time
import sys
import math
import copy
import ast

print("Welcome to Guillermo's Closest Pair program")
print("Please follow the on screen Instructions")
print(" ")


def dist(x,y):#distance equation
    return math.sqrt((x[0]-y[0])**2+(x[1]-y[1])**2)

def BF(values):#Brute force checks all pairs
    i=0
    val=[float('inf'),0,0]
    while i <len(values): 
        j=i+1
        while j <len(values):#loop rest of array
            d = dist(values[i],values[j])
            if d<val[0]:
                val=[d,i,j]
            j=j+1
        i=i+1
    r= [val[0],values[val[1]],values[val[2]]]
    return r[0]#return the distance

def Rec(in1,in2):#Recursive check
    if len(in1)<=3:
        result=BF(in1)
    else:
        x=0
        Pl=[]
        Pr=[]
        Ql=[]
        Qr=[]
        while x <len(in1)//2:#first half
            Pl.append(in1[x])
            Ql.append(in2[x])
            x=x+1
        while x<len(in1):#second half
            Pr.append(in1[x])
            Qr.append(in2[x])
            x=x+1
        Dl=Rec(Pl,Ql)#callback
        Dr=Rec(Pr,Qr)
        d=min(Dl,Dr)
        n=int(len(in1))
        m=in1[(n//2)-1][0]
        S=[]
        for element in in2:
            if math.fabs(element[0]-m)<d:
                S.append(element)
        dminsq=d**2
        num = len(S)
        i=0
        k=1
        while i < num-2:
            while (k<= num-1 )and(((S[k][1]-S[i][1])**2) < dminsq):
                var=dist(S[k],S[i])
                dminsq=min(var**2,dminsq)
                k=k+1
            i=i+1
        result=math.sqrt(dminsq)
    return result#return the distance

def effRec(inputval):#time efficiency recursive
    in1=copy.copy(inputval)
    in2=copy.copy(inputval)
    in1.sort(key=lambda t: t[0])# x
    in2.sort(key=lambda t: t[1])# y
    t0=time.time()
    result=Rec(in1,in2)
    t1=time.time()
    T=t1-t0
    print('The distance calculated by Recursion : '+str(result)+' took a time of: '+str(T))
    return

def effBF(inputval):#time efficincy brute force
    t0=time.time()
    result=BF(inputval)
    t1=time.time()
    T=t1-t0
    print('The distance calculated by Brute Force : '+str(result)+' took a time of: '+str(T))
    return

def effall(inputval): #run all
    effBF(inputval)
    effRec(inputval)
    return




#effBF(points)
#effRec(points)

while(True):
    userval= str(input("input the name of the file IE= 'input.txt' :"))
    print(" ")
    print("Your input was: "+userval+"\n Testing Brute Force and Recurssion for closest pair...")
    print(" ")
    # Get Input
    f=open(userval, 'r')
    userval = ast.literal_eval(f.read())
    effall(userval)
    continue


