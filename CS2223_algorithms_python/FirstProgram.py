# CS2223 Project 2 Nikolas Gamarra B17

#import libraries
import time
from memory_profiler import memory_usage
from memory_profiler import profile
import sys
import math
import copy

def dist(a,b):#helper function for euclidian distance
    return math.sqrt((a[0]-b[0])**2+(a[1]-b[1])**2)

def closestPairBF(array):#finds the closest distance by checking all possible paris
    i=0
    result=[float('inf'),0,0]
    while i <len(array):#loop through first checking element
        j=i+1
        while j <len(array):#loop through uncompaired other elements
            d = dist(array[i],array[j])
            if d<result[0]:#if smaller save
                result=[d,i,j]
            j=j+1
        i=i+1
    r= [result[0],array[result[1]],array[result[2]]]
    return r[0]#return the distance

def closestPairRec(P,Q):#finds the closest distance recursively
    if len(P)<=3:
        result=closestPairBF(P)
    else:
        x=0
        PL=[]
        QL=[]
        PR=[]
        QR=[]
        while x <len(P)/2:#copy first half of input into left sub array
            PL.append(P[x])
            QL.append(Q[x])
            x=x+1
        while x<len(P):#copy second half of input into right sub array
            PR.append(P[x])
            QR.append(Q[x])
            x=x+1
        DL=closestPairRec(PL,QL)#recursive call
        DR=closestPairRec(PR,QR)
        d=min(DL,DR)#find which recursive call had the smaller result
        n=int(len(P))#save length of input
        m=P[(n/2)-1][0]#find the half way value of p.x
        S=[]#setup array 
        #copy all the points of Q for which |x-m|<d into array S[0...num-1
        for element in Q:#copy elements of Q for which the x-m<d
            if math.fabs(element[0]-m)<d:
                S.append(element)
        dminsq=d**2#square the smaller recursive result
        num = len(S)
        i=0
        k=1
        while i < num-2:#loop through and find the shortest answer
            while (k<= num-1 )and(((S[k][1]-S[i][1])**2) < dminsq):
                var=dist(S[k],S[i])
                dminsq=min(var**2,dminsq)
                k=k+1
            i=i+1
        result=math.sqrt(dminsq)
    return result#return the distance

def effREC(points):#function to test the recursive function
    print('\nTesting Recursive\n')
    P=copy.copy(points)#copy the data so it can be sorted
    Q=copy.copy(points)
    P.sort(key=lambda tup: tup[0])#sort by x
    Q.sort(key=lambda tup: tup[1])#sort by y
    t0=time.time()
    result=closestPairRec(P,Q)
    t1=time.time()
    T=t1-t0
    print('The distance of the closest pair: '+str(result)+' Was calculated in time: '+str(T)+' seconds.\n')
    return

def effBF(points):#function to test the brute force function
    print('\nTesting Brute Force\n')
    t0=time.time()
    result=closestPairBF(points)
    t1=time.time()
    T=t1-t0
    print('The distance of the closest pair: '+str(result)+' Was calculated in time: '+str(T)+' seconds.\n')
    return


if __name__ == '__main__':
    print('\nCS2223 Project2 Nikolas Gamarra')
    print('This program finds two closest points in a set of n points\n')
    if len(sys.argv)>1:
        filename=str(sys.argv[1])
    else:
        filename="input.txt"
    try:  # check of invalid inputs
        f = open(filename, "r")
        array = f.read()
        for char in "][":
            array = array.replace(char, '')
        array.split("),(")
        for char in ")(":
            array = array.replace(char, '')
        array.split(",")
        array = array.split(',')
        if len(array) % 2 != 0:#check that there is an even nuber of numbers in the array
            raise ValueError
        i = 0
        newArray = []
        while i < len(array):#run through the array
            x = int(array[i])#extract x as an int
            y = int(array[i + 1])#extract y as an int
            point = (x, y)# put into tupl
            newArray.append(point)#add tupl to array 
            i = i + 2
    except IOError:
        print'Could no read file:', filename  # Primpt user to correct their input
        sys.exit()
    except ValueError:
        print "Value Error: make sure input is valid"
        sys.exit()
    else:
        #break
        print '\nThe input from ' +filename+' is: \n'
        print newArray
        print '\nLength: '+str(len(newArray))
        effBF(newArray)
        effREC(newArray)
