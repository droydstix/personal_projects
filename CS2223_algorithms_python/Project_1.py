import time
#from memory_profiler import memory_usage 
#from memory_profiler import profile
#process = psutil.Process(os.getpid())
#print(process.memory_info().rss)
# downloaded these for memory but at initialiazing received "from memory_profiler import memory_usage
# ModuleNotFoundError: No module named 'memory_profiler"
i=0

# Get User Input
firstin= int(input("Enter the first digit: "))
secondin= int(input("Enter the second digit: "))
print(" ")


# Find GCD with Euclid Algorithm
def Euclid(m, n): #input
        while(n != 0):
                r = m % n
                m = n
                n = r
        return m
    
# Find GCD with Consecutive Integer Checking
def CIC(m,n):
    t=min(m,n)#step1
    run=1
    step=2
    while run==1:
        if step==2:#step2
            if m % t==0:#step2
                step=3
            else:
                step=4 #go to step4
        if step==3:
            if n % t==0:
                run=0
            else:
                step=4 #go to step4
        if step==4:#step4
            t-=1
            step=2#step2
    return t
    
# Prime factorization for Middle School Procedure
def primeFactors(val):
    factors = []
    unit = 2
    while(unit != val and val != 1):
        if(val % unit == 0):
            val = val / unit
            factors.append(unit)
        else:
            unit += 1
    factors.append(int(val))
    return factors

# Find GCD with Middle School Procedure
def MSP(m,n):
    primeofm=primeFactors(m)#call prime factorization
    primeofn=primeFactors(n)#call prime factorization
    primeofmn=[]
    for i in primeofm:
        if i in (primeofm and primeofn):
            primeofmn.append(i)
    final=1
    for f in primeofmn:
        final=f*final
    return final

#Efficiency for EUCLID
def effGDCeuc(m,n):
        start = time.clock()
        valgcd=Euclid(m,n)
        elapsed = (time.clock()-start)
        print("The Euclid method took a time of "+str(elapsed))
        print("The GDC for Euclid is "+str(valgcd))
        print(" ")

#Efficiency for CIC
def effGDCcic(m,n):
        start = time.clock()
        valgcd=CIC(m,n)
        elapsed = (time.clock()-start)
        print("The CIC method took a time of "+str(elapsed))
        print("The GDC for CIC is "+str(valgcd))
        print(" ")

#efficiency for MSP
def effGDCmsp(m,n):
        start = time.clock()
        valgcd=MSP(m,n)
        elapsed = (time.clock()-start)
        print("The MSP method took a time of "+str(elapsed))
        print("The GDC for MSP is "+str(valgcd))
        print("")

def effall(firstin,secondin):
        print(" ")
        start = time.clock()
        effGDCeuc(firstin,secondin)
        effGDCcic(firstin,secondin)
        effGDCmsp(firstin,secondin)
        elapsed = (time.clock()-start)
        print("The program took a time of "+str(elapsed)+ " to execute")
        print("")


while(True):

        if(i == 2):
                print("Too many incorrect tries, exiting...")
                exit()
        if(firstin <= 0):
                print("The first number must be positive and greater than 0")
                firstin = int(input("Re-enter the first digit: "))
                i += 1

        if(secondin <= 0):
                print("The second number must be positive and greater than 0")
                secondin = int(input("Re-enter the second digit: "))
                i += 1
        if(firstin>0 and secondin>0):
                i = 0
                effall(firstin,secondin)
                again=str(input("Test again?(y/n): "))
                if(again=='n'):
                    print('goodbye')
                    exit()
                else:
                    firstin= int(input("Enter the first digit: "))
                    secondin= int(input("Enter the second digit: "))

        continue

    
