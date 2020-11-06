while True:
    try:
        change = float(input("Change owed: "))
        if (change > 0):
            break
    except ValueError:
        print("Not a real number!")
        
counter = 0

while True:
    if change >= 0.25:
        change = round(change - 0.25, 2)
        counter += 1
        
    elif change >= 0.10:
        change = round(change - 0.10, 2)
        counter += 1
        
    elif change >= 0.05:
        change = round(change - 0.05, 2)
        counter += 1
        
    elif change >= 0.01:
        change = round(change - 0.01, 2)
        counter += 1
    else:
        break
print(f"{counter}")