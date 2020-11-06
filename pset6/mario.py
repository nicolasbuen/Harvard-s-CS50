while True:
    try:
        n = int(input("Height: "))
        if (n > 0 and n < 9):
            break
    except ValueError:
        print("Not a Number")
    

control = 1

for j in range(n):
    for i in range(n-control): #spaces at th
        print(" ", end="")
        
    for i in range(control):
        print("#", end="")
    
    print("  ", end="")
    
    for i in range(control):
        print("#", end="")
    
    print("")
    control += 1

