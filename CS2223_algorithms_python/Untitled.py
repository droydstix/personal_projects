

def createset():
    Ssetcodes=[]
    for x in range(1111,6667):
        Ssetcodes.append(x)
    print(Ssetcodes)

userval = input("What's your code? ")
print("Your guess is " + userval)
print("Lets see how many turns it takes me to solve")
createset()
    

